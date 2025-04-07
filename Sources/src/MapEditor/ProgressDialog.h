#if !defined(__PROGRESS_DIALOG__)
#define __PROGRESS_DIALOG__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CProgressDialog : public CDialog
{
public:
	CProgressDialog( CWnd* pParent = NULL );

	//{{AFX_DATA(CProgressDialog)
	enum { IDD = IDD_PROGRESS };
	CStatic	m_ProgressLabel;
	CProgressCtrl	m_ProgressBar;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CProgressDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	static const DWORD START_TIMER_ID;
	static const DWORD START_TIMER_INTERVAL;

  DWORD dwStartTimer;

  void SetStartTimer();
  void KillStartTimer();
  void OnStartTimer();
	
	//{{AFX_MSG(CProgressDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetProgressMessage( const std::string &rszProgressMessage );
	void SetProgressRange( int nStart, int nFinish );
	void SetProgressPosition( int nPosition );
	void IterateProgressPosition();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif // !defined(__PROGRESS_DIALOG__)

