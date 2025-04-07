#if !defined(__AUTO_RUN_MAIN_DIALOG__)
#define __AUTO_RUN_MAIN_DIALOG__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AR_Types.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAutoRunDialog : public CDialog
{
	friend class CARMenuSelector;
public:
	CAutoRunDialog( CWnd* pParent = NULL );
	bool Load();
	//{{AFX_DATA(CAutoRunDialog)
	enum { IDD = IDD_AUTORUN_DIALOG };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAutoRunDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL

protected:
	static const DWORD FINISH_TIMER_ID;
	static const DWORD FINISH_TIMER_INTERVAL;
	static const DWORD FINISH_TIMER_MAX_COUNT;
	
	HICON m_hIcon;
	CToolTipCtrl tooltips;
	CARMenuSelector menuSelector;
	CPoint lastMousePoint;
	int lastMouseFlags;
	bool bMoveWindow;

  DWORD dwFinishTimer;
	DWORD dwFinishTimerCount;

  void SetFinishTimer();
  void KillFinishTimer();
  void OnFinishTimer();
	
	bool CheckGameApp( LPCSTR pszMainClass, LPCSTR pszMainTitle );
	bool CheckPreviousApp( LPCSTR pszMainClass, LPCSTR pszMainTitle );
	
	//{{AFX_MSG(CAutoRunDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#endif // !defined(__AUTO_RUN_MAIN_DIALOG__)
