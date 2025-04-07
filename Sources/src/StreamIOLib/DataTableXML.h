#ifndef __DATATABLEXML_H__
#define __DATATABLEXML_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#import "msxml.dll"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace MSXML;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CDataTableXML : public IDataTable
{
	OBJECT_MINIMAL_METHODS( CDataTableXML );
	//
	CPtr<IDataStream> pStream;						// stream, this table was open with
	IXMLDOMDocumentPtr xmlDocument;				// открытый документ
	IXMLDOMNodePtr xmlRootNode;						// root node
	//
	bool bModified;
	// получить текстовый node по имени. Это либо атрибут текущего node, либо single node из текущего.
	IXMLDOMNodePtr GetTextNode( const char *pszRow, const char *pszEntry )
	{
		IXMLDOMNodePtr xmlCurrNode = xmlRootNode->selectSingleNode( pszRow );
		if ( xmlCurrNode == 0 )
			return 0;
		IXMLDOMNodePtr xmlNode = xmlCurrNode->attributes->getNamedItem( pszEntry );
		if ( xmlNode == 0 )
			xmlNode = xmlCurrNode->selectSingleNode( pszEntry );
		return xmlNode;
	}
	//
	inline void SetModified() { bModified = true; }
	//
	template <class TYPE>
		inline void SetValue( const char *pszRow, const char *pszEntry, const TYPE &val )
	{
		if ( IXMLDOMElementPtr pElement = xmlRootNode->selectSingleNode( pszRow ) )
			pElement->setAttribute( pszEntry, val );
		else
		{
			IXMLDOMElementPtr pElement = xmlDocument->createElement( pszRow );
			xmlRootNode->appendChild( pElement );
			pElement->setAttribute( pszEntry, val );
		}
	}
	//
	IXMLDOMNodePtr GetNode( const std::string &szName );
	const std::string MakeName( const char *pszRow, const char *pszEntry )
	{
		std::string szName = std::string( pszRow ) + "." + std::string( pszEntry );
		std::replace_if( szName.begin(), szName.end(), std::bind2nd( std::equal_to<char>(), '.' ), '/' );
		return szName;
	}
public:
	CDataTableXML();
	virtual ~CDataTableXML();
	//
	bool Open( IDataStream *pStream, const char *pszBaseNode );
	// получить имена строк таблицы. каждое имя заканчивается на '\0', с строка в целом на '\0\0'
	virtual int STDCALL GetRowNames( char *pszBuffer, int nBufferSize );
	// получить имена колонок таблицы в данной строке. каждое имя заканчивается на '\0', с строка в целом на '\0\0'
	virtual int STDCALL GetEntryNames( const char *pszRow, char *pszBuffer, int nBufferSize );
	// очистка секции
	virtual void STDCALL ClearRow( const char *pszRowName ) {  }
	// complete element access
	// get
	virtual int STDCALL GetInt( const char *pszRow, const char *pszEntry, int defval );
	virtual double STDCALL GetDouble( const char *pszRow, const char *pszEntry, double defval );
	virtual const char* STDCALL GetString( const char *pszRow, const char *pszEntry, const char *defval, char *pszBuffer, int nBufferSize );
	virtual int STDCALL GetRawData( const char *pszRow, const char *pszEntry, void *pBuffer, int nBufferSize );
	// set
	virtual void STDCALL SetInt( const char *pszRow, const char *pszEntry, int val );
	virtual void STDCALL SetDouble( const char *pszRow, const char *pszEntry, double val );
	virtual void STDCALL SetString( const char *pszRow, const char *pszEntry, const char *val );
	virtual void STDCALL SetRawData( const char *pszRow, const char *pszEntry, const void *pBuffer, int nBufferSize );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __DATATABLEXML_H__
