#if !defined(__InputState__)
#define __InputState__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTemplateEditorFrame;
interface IInputState
{
	virtual void STDCALL	Enter()	{}
	virtual void STDCALL	Leave()	{}
	virtual void STDCALL	Update() {}

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
	
	virtual void STDCALL	Draw( CTemplateEditorFrame* pFrame ) {}

	virtual ~IInputState() {}
};

class CInputStateParameter
{
public:
	static const int INVALID_STATE;

	enum INPUT_STATE_EVENT
	{
		ISE_MOUSEMOVE			= 0,
		ISE_LBUTTONDOWN		= 1,
		ISE_LBUTTONUP			= 2,
		ISE_LBUTTONDBLCLK	= 3,
		ISE_RBUTTONDOWN		= 4,
		ISE_RBUTTONUP			= 5,
		ISE_RBUTTONDBLCLK	= 6,
		ISE_MBUTTONDOWN		= 7,
		ISE_MBUTTONUP			= 8,
		ISE_MBUTTONDBLCLK	= 9,
		ISE_KEYDOWN				= 10,
		ISE_COUNT					= 11,
	};

	struct SMouseEvent
	{
		CTPoint<int> point;
		CVec3 vPos;
		bool isValid;

		SMouseEvent() : point( 0, 0 ), vPos( VNULL3 ), isValid( false ) {}
	};

	SMouseEvent mouseEvents[ISE_COUNT];
	CVec3 vLastPos;
	CTPoint<int> lastPoint;

	CInputStateParameter() : vLastPos( VNULL3 ) {}
	bool Update( INPUT_STATE_EVENT nType, const CTPoint<int> &rPoint, CTemplateEditorFrame* pFrame, bool bSetZToZero = false );
	void UpdateSatusBar( bool bValid );
	bool LastPointInTerrain();
};

#endif // !defined(__InputState__)
