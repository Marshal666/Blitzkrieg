#if !defined(__INPUT_3DTAB_WINDOW__)
#define __INPUT_3DTAB_WINDOW__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <olbar.h>
#include "tabwnd.h"
#include "tabwnd3.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IDC_INPUT_3DTAB_WINDOW_00 ( 61850 )

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CInput3DTabWindow : public SEC3DTabWnd
{
protected:
	//{{AFX_MSG(CInput3DTabWindow)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	std::vector<CWnd*> inputTabWindows;

	~CInput3DTabWindow()
	{
		for ( int nInputTabWindowIndex = 0; nInputTabWindowIndex < inputTabWindows.size(); ++nInputTabWindowIndex )
		{
			if ( inputTabWindows[nInputTabWindowIndex] )
			{
				delete ( inputTabWindows[nInputTabWindowIndex] );
				inputTabWindows[nInputTabWindowIndex] = 0;
			}
		}
	}

	template<class TINPUTTABWINDOW>
	TINPUTTABWINDOW* AddInputTabWindow( TINPUTTABWINDOW* pDummyInputTabWindow ) 
	{
		TINPUTTABWINDOW *pNewInputTabWindow = pDummyInputTabWindow;
		if ( !pNewInputTabWindow )
		{
			pNewInputTabWindow = new TINPUTTABWINDOW();
		}
		inputTabWindows.push_back( pNewInputTabWindow );
		return pNewInputTabWindow;
	}

	//{{AFX_VIRTUAL(CInput3DTabWindow)
	//}}AFX_VIRTUAL
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__INPUT_3DTAB_WINDOW__)
