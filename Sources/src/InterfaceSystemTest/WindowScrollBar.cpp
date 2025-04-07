// WindowScrollBar.cpp: implementation of the CWindowScrollBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WindowScrollBar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CWindowScrollBar::operator&( IDataTree &ss )
{
}
//////////////////////////////////////////////////////////////////////
void CWindowScrollBar::Reposition( const CTRect<float> &parentRect )
{
	//
	pSlider = dynamic_cast<CWindowSlider*>( GetChild( "Slider" ) );
	NI_ASSERT_T( pSlider != 0, "scrollbar must have slider" );

	pButtonDown = dynamic_cast<CWindowMSButton*>( GetChild( "ButtonDown" ) );
	NI_ASSERT_T( pButtonDown != 0, "scrollbar must have button down" );

	pButtonUp = dynamic_cast<CWindowMSButton*>( GetChild( "ButtonUp" ) );
	NI_ASSERT_T( pButtonUp != 0, "scrollbar must have button Up" );

	if ( pSlider->IsHorisontal() )
	{
		
	}
}
//////////////////////////////////////////////////////////////////////
void CWindowScrollBar::SetNotifySink( interface ISliderNotify *_pNotifySink ) 
{ 
	pSlider->SetNotifySink( _pNotifySink ); 
}
