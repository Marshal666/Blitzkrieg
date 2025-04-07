// WindowScrollBar.h: interface for the CWindowScrollBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWSCROLLBAR_H__46D0E093_95AF_4D78_9A5B_BB754D40FC3A__INCLUDED_)
#define AFX_WINDOWSCROLLBAR_H__46D0E093_95AF_4D78_9A5B_BB754D40FC3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Window.h"
#include "Interface.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CWindowMSButton;
class CWindowSlider;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// contains 1 slider and 2 buttons (up & down)
class CWindowScrollBar : 	public CWindow, public ISlider
//CRAP{ FOR TEST
, public ISliderNotify
//CRAP}
{
	OBJECT_COMPLETE_METHODS(CWindowSlider)
	DECLARE_SERIALIZE
	DECLARE_CLONABLE_CLASS 

	CNCPtr<CWindowMSButton> pButtonUp;
	CNCPtr<CWindowMSButton> pButtonDown;

	CNCPtr<CWindowSlider> pSlider;
	
public:

	virtual int STDCALL operator&( IDataTree &ss );
	virtual void STDCALL Reposition( const CTRect<float> &parentRect );

	//CRAP{ FOR TEST
	virtual void STDCALL SliderPosition( const float fPosition ) 
	{
		
	}
	//CRAP}

	virtual void STDCALL SetNotifySink( interface ISliderNotify *_pNotifySink );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_WINDOWSCROLLBAR_H__46D0E093_95AF_4D78_9A5B_BB754D40FC3A__INCLUDED_)
