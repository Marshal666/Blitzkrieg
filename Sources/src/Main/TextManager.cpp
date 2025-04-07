#include "StdAfx.h"
#include "TextManager.h"
#include "TextObject.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** text manager
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTextManager::Init()
{
	shareString.Init();
	shareDialog.Init();
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SCRLFTabRemoveFunctional
{
	bool operator()( const wchar_t chr ) const { return (chr == L'\n') || (chr == L'\r') || (chr == L'\t'); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ExtractKeyAndValue( const std::wstring &szInput, std::string *pKey, std::wstring *pValue )
{
	std::wstring szString = szInput;
	szString.erase( std::remove_if(szString.begin(), szString.end(), SCRLFTabRemoveFunctional()), szString.end() );
	if ( szString.size() < 3 ) 
		return false;												// eject too short (read wrong) strings
	//
	const int nPos = szString.find( L'#' );
	if ( nPos == std::wstring::npos ) 
		return false;												// string w/o separator (#) we'll treat as wrong... ejecting
	// key
	*pKey = NStr::ToAscii( szString.substr(0, nPos) );
	NStr::TrimBoth( *pKey );
	NStr::ToLower( *pKey );
	// extract value
	*pValue = szString.substr( nPos + 1, std::wstring::npos );
	// trim value left
	pValue->erase( 0, pValue->find_first_not_of(L' ') );
	// trim value right
	{
		const int nPos = pValue->find_last_not_of( L' ' );
		if ( nPos == std::wstring::npos )
		{
			if ( pValue->find_first_of( L' ' ) == 0 )
				pValue->clear();
		}
		else
			pValue->erase( nPos + 1, std::wstring::npos );
	}
	//
	return !pKey->empty() && !pValue->empty();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTextManager::AddTextFile( const char *pszFileName )
{
	IDataStorage *pStorage = GetSingleton<IDataStorage>();
	CPtr<IDataStream> pStream = pStorage->OpenStream( pszFileName, STREAM_ACCESS_READ );
	if ( pStream == 0 )
		return false;
	// read and check UNICODE signature (0xfffe)
	WORD wSignature = 0;
	pStream->Read( &wSignature, 2 );
	NI_ASSERT_TF( wSignature == 0xfeff, NStr::Format("Text set \"%s\" is not a UNICODE text!", pszFileName), return false );
	// skip 0xfeff at the begining
	const int nSize = pStream->GetSize() - 2;
	NI_ASSERT_TF( !(nSize & 0x01), "The file size is incorrect, the size of UNICODE file should be even", return false );	
	//
	std::wstring szString;
	szString.resize( nSize / 2 );
	const int nCheck = pStream->Read( &(szString[0]), nSize );
	NI_ASSERT_SLOW_TF( nCheck == nSize, "Readed size doesn't match requested", return false );
	//
	const wchar_t wSeparator = L'\n';
	int nPos = 0, nLastPos = 0;
	//
	do
	{
		nPos = szString.find( wSeparator, nLastPos );
		//
		std::string szKey;
		std::wstring wszValue;
		if ( ExtractKeyAndValue(szString.substr(nLastPos, nPos - nLastPos), &szKey, &wszValue) == true )
		{
			// �������� ����� �������� � share
			CPtr<CTextString> pTextString = new CTextString;
			pTextString->SetText( wszValue.c_str() );
			shareString.AddPair( szKey, pTextString );
		}
		//
		nLastPos = nPos + 1;
		//
	} while( nPos != std::wstring::npos );

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTextManager::Clear( const ISharedManager::EClearMode eMode, const int nUsage, const int nAmount ) 
{ 
	if ( eMode == ISharedManager::CLEAR_ALL ) 
		shareDialog.Clear(); 
	else
		shareDialog.ClearUnreferencedResources(); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IText* CTextManager::GetString( const char *pszKey ) 
{ 
	if ( shareString.HasData(pszKey) ) 
		return shareString.Get( pszKey );
	else
	{
		// CRAP{ to be compatible with old strings-based system
		if ( IText *pText = GetDialog(NStr::Format("textes\\strings\\%s", pszKey)) )
			return pText;
		else if ( IText *pText = GetDialog(NStr::Format("textes\\tooltips\\%s", pszKey)) )
			return pText;
		else if ( IText *pText = GetDialog(NStr::Format("textes\\acks\\%s", pszKey)) )
			return pText;
		else if ( IText *pText = GetDialog(pszKey) )
			return pText;
		else
			return 0;
		// CRAP}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CTextManager::operator&( IStructureSaver &ss )
{
	shareString.Serialize( &ss );
	shareDialog.Serialize( &ss );
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
