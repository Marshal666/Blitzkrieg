#ifndef __XML_READER_H__
#define __XML_READER_H__

#import "msxml.dll"
using namespace MSXML;

typedef pair<string, string> CXMLValue;
typedef vector< CXMLValue > CXMLValuesVector;

struct SXMLValue
{
	bool bString;			//если 0 то number если 1 то string
	string szName;
	string szVal;
	
	SXMLValue() : bString( true ) {}
};

inline bool operator < ( const SXMLValue &a, const SXMLValue &b ) { return a.szName < b.szName; }

typedef vector< SXMLValue > CXMLReadVector;

class CXMLReader
{
	IXMLDOMDocumentPtr xmlDocument;

protected:
	IXMLDOMNodePtr FindRPGNode( IXMLDOMNodePtr startNode, const char *pszNodeName );
	void ReadInformation( IXMLDOMNodePtr node, const string &szPrefix, CXMLReadVector &result, vector<string> &crapFields, bool bIgnoreFields );
	bool IsCrappedValue( const std::string &szValName, const vector<string> &crapFields, bool bIgnoreFields, bool bCompareOnlyFirstSymbols );

public:
	CXMLReader() : xmlDocument( "Microsoft.XMLDOM" ) {}
	~CXMLReader() {}

	bool ReadRPGInformationFromFile( const char *pszFileName, CXMLReadVector &result, vector<string> &crapFields, bool bIgnoreFields, const char *pszNodeName );
};

class CXMLWriter
{
	IXMLDOMDocumentPtr xmlDocument;

protected:
	IXMLDOMNodePtr FindRPGNode( IXMLDOMNodePtr startNode, const char *pszNodeName );
	void FindNodeAndSetAttribute( IXMLDOMNodePtr startNode, const string &szName, const string &szAttributeValue );
	void WriteInformation( CXMLValuesVector &valuesVector, IXMLDOMNodePtr startNode );

public:
	CXMLWriter() : xmlDocument( "Microsoft.XMLDOM" ) {}
	~CXMLWriter() {}
	
	bool SaveRPGInformationToXML( const char *pszFileName, const CXMLValuesVector &valuesVector, const char *pszNodeName );
};

#endif		//__XML_READER_H__
