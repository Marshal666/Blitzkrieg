#ifndef __DATATREEXML_H__
#define __DATATREEXML_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#import "msxml.dll"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace MSXML;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// эти две структурки специально созданы для того, чтобы, чтобы можно было сбрасывать com_ptr объекты в STL контейнеры
// горбуха, конечно, но такова природа com_ptr - косяк полный
template <class TYPE>
struct SCOMPtr
{
	TYPE data;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SNodeslList
{
	SCOMPtr<IXMLDOMNodeListPtr> nodes;
	int nCurrElement;
	//
	SNodeslList() : nCurrElement( -1 ) {  }
};
class CDataTreeXML : public IDataTree
{
	OBJECT_MINIMAL_METHODS( CDataTreeXML );
	//
	CPtr<IDataStream> pStream;						// stream, this table was open with
	IXMLDOMDocumentPtr xmlDocument;				// открытый документ
	//
	std::list< SCOMPtr<IXMLDOMNodePtr> > nodes;	// стек нодов по иерархии углублени
	std::list< SNodeslList > nodelists;					// стек списков нодов по иерархии углублени
	IXMLDOMNodePtr xmlCurrNode;						// текущий node
	//
	std::list< SCOMPtr<IXMLDOMElementPtr> > elements;	// стек элементов по иерархии углублени
	std::list< SCOMPtr<IXMLDOMElementPtr> > arrbases; // стек элементов сонований массивов по иерархии углублени
	IXMLDOMElementPtr xmlCurrElement;			// текущий элемент в блочной структуре при записи
	//
	IDataTree::EAccessMode eMode;
	//
	// получить из текущего node атрибут по имени.
	IXMLDOMNodePtr GetAttribute( DTChunkID idChunk )
	{
		NI_ASSERT_TF( xmlCurrNode != 0, "can't get attribute - no current node set", return 0 );
		return xmlCurrNode->attributes->getNamedItem( idChunk );
	}
	// получить текстовый node по имени. Это либо атрибут текущего node, либо single node из текущего.
	IXMLDOMNodePtr GetTextNode( DTChunkID idChunk )
	{
		NI_ASSERT_TF( xmlCurrNode != 0, "can't get node - no current node set", return 0 );
		IXMLDOMNodePtr xmlNode = xmlCurrNode->attributes->getNamedItem( idChunk );
		if ( xmlNode == 0 )
			xmlNode = xmlCurrNode->selectSingleNode( idChunk );
		return xmlNode;
	}
public:
	CDataTreeXML( IDataTree::EAccessMode eMode );
	virtual ~CDataTreeXML();
	//
	bool Open( IDataStream *pStream, DTChunkID idBaseNode );
	// is opened in the READ mode?
	virtual bool STDCALL IsReading() const { return eMode == IDataTree::READ; }
	// start new complex chunk
	virtual int STDCALL StartChunk( DTChunkID idChunk );
	// finish complex chunk
	virtual void STDCALL FinishChunk();
	// simply data chunk: text, integer, fp
	virtual int STDCALL GetChunkSize();
	virtual bool STDCALL RawData( void *pData, int nSize );
	virtual bool STDCALL StringData( char *pData );
	virtual bool STDCALL StringData( WORD *pData );
	virtual bool STDCALL DataChunk( DTChunkID idChunk, int *pData );
	virtual bool STDCALL DataChunk( DTChunkID idChunk, double *pData );
	// array data serialization (special case)
	virtual int STDCALL CountChunks( DTChunkID idChunk );
	virtual bool STDCALL SetChunkCounter( int nCount );
	virtual int STDCALL StartContainerChunk( DTChunkID idChunk );
	virtual void STDCALL FinishContainerChunk();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitCOM();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __DATATREEXML_H__
