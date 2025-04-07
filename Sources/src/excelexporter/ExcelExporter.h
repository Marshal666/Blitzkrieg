#ifndef __EXCEL_EXPORTER_H__
#define __EXCEL_EXPORTER_H__

struct SExtension {
	std::string szExtension;
	std::string szBaseNode;
	
	SExtension( const char *pszE, const char *pszN ) : szExtension( pszE ), szBaseNode( pszN ) {}
};
extern std::vector<SExtension> extensions;

class CExcelExporter
{
protected:
	CString GetExcelDriverName();					// Get the name of the Excel-ODBC driver
	bool ConvertSingleFile( const char *pszFileName );

public:
	void ConvertFilesToExcel( const vector<string> &files, const char *pszExcelFileName, const char *pszCrapFile, const char *pszNodeName, bool bIgnoreFields );
	void ConvertExcelToXMLFiles( const char *pszExcelFileName, const char *pszNodeName );
};

#endif		//__EXCEL_EXPORTER_H__
