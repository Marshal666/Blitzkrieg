#if !defined(__BaseState__)
#define __BaseState__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTemplateEditorFrame;
interface IState
{
	virtual void STDCALL	OnMouseMove			( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}

	virtual void STDCALL  OnLButtonDown		( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}
	virtual void STDCALL  OnLButtonUp			( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}
	virtual void STDCALL  OnLButtonDblClk	( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}

	virtual void STDCALL  OnRButtonDown		( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}
	virtual void STDCALL  OnRButtonUp			( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}
	virtual void STDCALL  OnRButtonDblClk	( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}

	virtual void STDCALL  OnMButtonDown		( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}
	virtual void STDCALL  OnMButtonUp			( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}
	virtual void STDCALL  OnMButtonDblClk	( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame )	{}

	virtual void STDCALL  OnKeyDown				( UINT nChar, UINT nRepCnt, UINT nFlags, CTemplateEditorFrame* pFrame )	{}
	virtual void STDCALL  OnObjectPaste		( CTemplateEditorFrame*	pFrame )	{}
};

class CStateParameter
{
public:
	enum STATE_EVENT
	{
		SE_MOUSEMOVE			= 0,
		SE_LBUTTONDOWN		= 1,
		SE_LBUTTONUP			= 2,
		SE_LBUTTONDBLCLK	= 3,
		SE_RBUTTONDOWN		= 4,
		SE_RBUTTONUP			= 5,
		SE_RBUTTONDBLCLK	= 6,
		SE_MBUTTONDOWN		= 7,
		SE_MBUTTONUP			= 8,
		SE_MBUTTONDBLCLK	= 9,
		SE_KEYDOWN				= 10,
		SE_DIMENSION			= 11,
	};

	struct SMouseEvent
	{
		CVec3 vPos;
		bool isValid;

		SMouseEvent() : vPos( VNULL3 ), isValid( false ) {}
	};

	SMouseEvent mouseEvents[SE_DIMENSION];
	CVec3 vLastPos;

	CStateParameter() : vLastPos( VNULL3 ) {}
	bool Update( STATE_EVENT nType, const CTPoint<int> &rPoint, CTemplateEditorFrame* pFrame );
};

#endif // !defined(__BaseState__)
