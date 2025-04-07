// ExcelExporter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <afxdb.h>
#include <odbcinst.h>
#include <iostream>
#include <set>

#include "ExcelExporter.h"
#include "XmlReader.h"
#include "..\misc\strproc.h"

const int STRING_SIZE = 65536;

CString CExcelExporter::GetExcelDriverName()
{
	char szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	char *pszBuf = szBuf;
	CString szDriver;
	
	// Get the names of the installed drivers ("odbcinst.h" has to be included )
	if(!SQLGetInstalledDrivers(szBuf,cbBufMax,& cbBufOut))
		return "";
	
	// Search for the driver...
	do
	{
		if( strstr( pszBuf, "Excel" ) != 0 )
		{
			// Found !
			szDriver = CString( pszBuf );
			break;
		}
		pszBuf = strchr( pszBuf, '\0' ) + 1;
	}
	while( pszBuf[1] != '\0' );
	
	return szDriver;
}

class CSpaceSeparator
{
public:
		bool operator() ( const char cSymbol ) const { return isspace( cSymbol ); }
};

void CExcelExporter::ConvertFilesToExcel( const vector<string> &files, const char *pszExcelFileName, const char *pszCrapFile, const char *pszNodeName, bool bIgnoreFields )
{
	if ( files.empty() )
		return;
	
	//считываем поля из crap файла
	std::vector< std::string > crapFields;
	if ( strlen(pszCrapFile) > 0 )
	{
		FILE *pFile = fopen( pszCrapFile, "r" );
		if ( pFile != 0 )
		{
			char szString[STRING_SIZE];
			while ( fgets( szString, STRING_SIZE, pFile ) != 0 )
			{
				int nLen = strlen( szString );
				if ( szString[nLen-1] == '\n' )
					szString[ nLen - 1 ] = '\0';
				NStr::CStringIterator<CSpaceSeparator> it( szString, CSpaceSeparator() );
				if ( it.IsEnd() )
					continue;
				
				crapFields.push_back( *it );
				++it;
			}
		}
	}
	
	if ( !bIgnoreFields && crapFields.empty() )
		bIgnoreFields = true;

	//считываем RPG информацию сразу из всех файлов
	vector<CXMLReadVector> filesValuesVector( files.size() );
	for ( int i=0; i<files.size(); i++ )
	{
		CXMLReader xmlReader;
		xmlReader.ReadRPGInformationFromFile( files[i].c_str(), filesValuesVector[i], crapFields, bIgnoreFields, pszNodeName );
	}

	// Create table structure
	std::set<SXMLValue> mySet;
	for ( int i=0; i<filesValuesVector.size(); i++ )
	{
		for ( int k=0; k<filesValuesVector[i].size(); k++ )
		{
/*
			vector<string>::iterator findIt = find( crapFields.begin(), crapFields.end(), filesValuesVector[i][k].szName );
			if ( findIt == crapFields.end() )
			{
				mySet.insert( filesValuesVector[i][k] );
			}
*/

			mySet.insert( filesValuesVector[i][k] );
		}
	}

	std::string szStrToSave = "FileName\t";
	for ( std::set<SXMLValue>::iterator it=mySet.begin(); it!=mySet.end(); ++it )
	{
		szStrToSave += it->szName;
		szStrToSave += "\t";
	}

	if ( szStrToSave.size() == 0 )
	{
		return;
	}

	szStrToSave = szStrToSave.substr( 0, szStrToSave.size() - 1 );
	szStrToSave += "\n";
	CPtr<IDataStream> pStream = OpenFileStream( pszExcelFileName, STREAM_ACCESS_WRITE );
	NI_ASSERT( pStream != 0 );
	if ( pStream == 0 )
	{
		std::string szErr = NStr::Format( "Error: The file %s can not be opened", pszExcelFileName );
		AfxMessageBox( szErr.c_str() );
		return;
	}

	pStream->Write( szStrToSave.c_str(), szStrToSave.size() );


	//formatting output
	for ( int i=0; i<filesValuesVector.size(); i++ )
	{
		std::cout << files[i].c_str() << std::flush;

		szStrToSave = "";
		CXMLReadVector cur;
		for ( std::set<SXMLValue>::iterator it=mySet.begin(); it!=mySet.end(); ++it )
		{
			int k = 0;
			for ( ; k<filesValuesVector[i].size(); k++ )
			{
				if ( filesValuesVector[i][k].szName == it->szName )
					break;
			}
			
			if ( k == filesValuesVector[i].size() )
			{
				if ( it->bString )
				{
					SXMLValue val;
					val.bString = true;
					val.szName = it->szName;
					val.szVal = "";
					cur.push_back( val );
				}
				else
				{
					SXMLValue val;
					val.bString = false;
					val.szName = it->szName;
					val.szVal = "";
					cur.push_back( val );
				}
			}
			else
			{
				cur.push_back( filesValuesVector[i][k] );
			}
		}
		
		{
			// Insert data
			szStrToSave += files[i];
			szStrToSave += "\t";
			
			for ( int k=0; k<cur.size(); k++ )
			{
				szStrToSave += cur[k].szVal;
				szStrToSave += "\t";
			}
			if ( szStrToSave.size() > 0 )
				szStrToSave = szStrToSave.substr( 0, szStrToSave.size() - 1 );
			szStrToSave += "\n";
			pStream->Write( szStrToSave.c_str(), szStrToSave.size() );
		}
		
		std::cout << "     -done" << endl;
	}
}

void CExcelExporter::ConvertExcelToXMLFiles( const char *pszExcelFileName, const char *pszNodeName )
{
	FILE *pFile = fopen( pszExcelFileName, "r" );
	NI_ASSERT( pFile != 0 );

	std::vector< std::string > headers;
	char szCur[STRING_SIZE];
	if ( fgets( szCur, STRING_SIZE, pFile ) == 0 )
	{
		NI_ASSERT_T( 0, "The file is empty?" );
		return;
	}
	szCur[ strlen( szCur ) - 1 ] = '\0';

	std::string szBaseNodeName = pszNodeName;		//"RPG"
	{
		NStr::CStringIterator<> it( szCur, NStr::CCharSeparator('\t') );
		for ( ; !it.IsEnd(); ++it )
		{
			std::string szCur = *it;
			int nBegin = szCur.find( '\"' );
			if ( nBegin != std::string::npos )
			{
				szCur = szCur.substr( nBegin+1, szCur.size()-2 );
			}
			headers.push_back( szCur );
		}
	}
	
	while ( fgets( szCur, STRING_SIZE, pFile ) != 0 )
	{
		szCur[ strlen( szCur ) - 1 ] = '\0';
		NStr::CStringIterator<> it( szCur, NStr::CCharSeparator('\t') );
		NI_ASSERT_T( !it.IsEnd(), "The line is empty?" );
		//read the file name
		std::string szFileName = *it;

		//узнаем имя ноды с информацией. По умолчанию - "RPG"
		{
			std::string szExtension = szFileName.substr( szFileName.rfind( '.' ) );
			for ( int i=0; i<extensions.size(); i++ )
			{
				if ( !strcmpi( extensions[i].szExtension.c_str()+1, szExtension.c_str() ) )
				{
					szBaseNodeName = extensions[i].szBaseNode;
					break;
				}
			}
		}

		++it;
		if ( it.IsEnd() )
			continue;
		
		CXMLValuesVector valuesVector;
		NI_ASSERT_T( !it.IsEnd(), "The line is empty?" );
		CXMLValue val;
		int i = 1;
		
		for ( ; !it.IsEnd(); ++it )
		{
			val.first = headers[i];
			std::string szCur = *it;
			int nBegin = szCur.find( '\"' );
			if ( nBegin != std::string::npos )
			{
				szCur = szCur.substr( nBegin+1, szCur.rfind('\"') );
			}
			val.second = szCur;
			valuesVector.push_back( val );
			i++;
		}

		CXMLWriter xmlWriter;
		if ( xmlWriter.SaveRPGInformationToXML( szFileName.c_str(), valuesVector, szBaseNodeName.c_str() ) )
			cout << (const char *) szFileName.c_str() << "    -done" << endl;
		else
			cout << (const char *) szFileName.c_str() << "    -FAILED" << endl;
	}

/*
	while ( pStream->)
	
		vector<CString> fieldNames;
		for ( int i=0; i<nCount; i++ )
		{
			CODBCFieldInfo fieldinfo;
			recset.GetODBCFieldInfo( i, fieldinfo );
			if ( fieldinfo.m_strName != "FileName" )
				fieldNames.push_back( fieldinfo.m_strName );
		}
		
		// Browse the result
		while( !recset.IsEOF() )
		{
			CString szFileName;
			recset.GetFieldValue( "FileName", szFileName );
			CXMLValuesVector valuesVector;

			for ( int i=0; i<fieldNames.size(); i++ )
			{
				CXMLValue val;
				CString szString;
				recset.GetFieldValue( fieldNames[i], szString );
				val.first = fieldNames[i];
				val.second = szString;
				if ( szString != '_' )				//CRAP ибо строчки в excel пишутся херово
					valuesVector.push_back( val );
			}

			CXMLWriter xmlWriter;
			if ( xmlWriter.SaveRPGInformationToXML( szFileName, valuesVector ) )
				cout << (const char *) szFileName << "    -done" << endl;
			else
				cout << (const char *) szFileName << "    -FAILED" << endl;

			// Skip to the next resultline
			recset.MoveNext();
		}
		
		// Close the database
		database.Close();
		
	}
	CATCH(CDBException, e)
	{
		// A database exception occured. Pop out the details...
		AfxMessageBox("Database error: "+e->m_strError);
	}
	END_CATCH;
*/
}


#ifdef OLD
void ReadExcelFile( const char *pszFileName )
{
	CDatabase database;
	CString szSql;
	CString szItem1, szItem2;
	CString szDriver;
	CString szDsn;
	
	// Retrieve the name of the Excel driver. This is 
	// necessary because Microsoft tends to use language
	// specific names like "Microsoft Excel Driver (*.xls)" versus
	// "Microsoft Excel Treiber (*.xls)"
	szDriver = GetExcelDriver();
	if( szDriver.IsEmpty() )
	{
		// Blast! We didnґt find that driver!
		AfxMessageBox("No Excel ODBC driver found");
		return;
	}
	
	// Create a pseudo DSN including the name of the Driver and the Excel file
	// so we donґt have to have an explicit DSN installed in our ODBC admin
	szDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s",szDriver,pszFileName);
	
	TRY
	{
		// Open the database using the former created pseudo DSN
		database.Open(NULL,false,false,szDsn);
		
		// Allocate the recordset
		CRecordset recset( &database );
		
		
		// Build the SQL string
		// Remember to name a section of data in the Excel sheet using "Insert->Names" to be
		// able to work with the data like you would with a table in a "real" database. There
		// may be more than one table contained in a worksheet.
		szSql = "SELECT * "
			"FROM demo ";
		
		// Execute that query (implicitly by opening the recordset)
		recset.Open(CRecordset::forwardOnly,szSql,CRecordset::readOnly);
		CString szTableName = recset.GetTableName();
		int nCount = recset.GetODBCFieldCount();
		int nRecCount = recset.GetRecordCount();
		vector<CString> strings;
		for ( int i=0; i<nCount; i++ )
		{
			CODBCFieldInfo fieldinfo;
			recset.GetODBCFieldInfo( i, fieldinfo );
			strings.push_back( fieldinfo.m_strName );
		}
		
		// Browse the result
		while( !recset.IsEOF() )
		{
			for ( int i=0; i<strings.size(); i++ )
			{
				recset.GetFieldValue(strings[i], szItem1);
			}
/*
			// Read the result line
			recset.GetFieldValue("field_1",szItem1);
			recset.GetFieldValue("field_2",szItem2);
*/		
			// Insert result into the list
//			m_ctrlList.AddString( szItem1 + " --> "+szItem2 );
			
			// Skip to the next resultline
			recset.MoveNext();
		}
		
		// Close the database
		database.Close();
		
	}
	CATCH(CDBException, e)
	{
		// A database exception occured. Pop out the details...
		AfxMessageBox("Database error: "+e->m_strError);
	}
	END_CATCH;
}

void SaveExcelFile()
{
	void CReadExcelDlg::OnButton2() 
	{
		CDatabase database;
		CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; // exactly the same name as in the ODBC-Manager
		CString sExcelFile = "c:\\demo.xls";                // Filename and path for the file to be created
		CString sSql;
		
		TRY
		{
			// Build the creation string for access without DSN
			
			sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s", sDriver,sExcelFile,sExcelFile);
			
			// Create the database (i.e. Excel sheet)
			if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
			{
				// Create table structure
				sSql = "CREATE TABLE demo (Name TEXT,Age NUMBER)";
				database.ExecuteSQL(sSql);
				
				// Insert data
				sSql = "INSERT INTO demo (Name,Age) VALUES ('Bruno Brutalinsky',45)";
				database.ExecuteSQL(sSql);
				
				sSql = "INSERT INTO demo (Name,Age) VALUES ('Fritz Pappenheimer',30)";
				database.ExecuteSQL(sSql);
				
				sSql = "INSERT INTO demo (Name,Age) VALUES ('Hella Wahnsinn',28)";
				database.ExecuteSQL(sSql);
			}
			
			// Close database
			database.Close();
		}
		CATCH_ALL(e)
		{
			TRACE1("Driver not installed: %s",sDriver);
		}
		END_CATCH_ALL;
	}
}

#endif		//OLD
