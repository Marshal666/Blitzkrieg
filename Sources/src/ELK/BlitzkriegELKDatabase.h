#if !defined(AFX_BLITZKRIEGELKDATABASE_H__CE89F423_7A2A_4413_9CBF_EBA307365C54__INCLUDED_)
#define AFX_BLITZKRIEGELKDATABASE_H__CE89F423_7A2A_4413_9CBF_EBA307365C54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlitzkriegELKDatabase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlitzkriegELKRecordset recordset

class CBlitzkriegELKRecordset : public CRecordset
{
public:
	CBlitzkriegELKRecordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBlitzkriegELKRecordset)

// Field/Param Data
	//{{AFX_FIELD(CBlitzkriegELKRecordset, CRecordset)
	CString	m_Path;
	CString	m_Original;
	CString	m_Translation;
	CString	m_State;
	CString	m_Description;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlitzkriegELKRecordset)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLITZKRIEGELKDATABASE_H__CE89F423_7A2A_4413_9CBF_EBA307365C54__INCLUDED_)
