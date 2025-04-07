#ifndef __PROPERTY_DOCK_H__
#define __PROPERTY_DOCK_H__

#include "MTree ctrl\FrameTree.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyDockBar window

class CPropertyDockBar : public SECControlBar
{
	std::map< std::string, HTREEITEM > m_insertedNodes;
	// Construction
public:
	CPropertyDockBar();
	virtual ~CPropertyDockBar();
	
	// Attributes
public:
	
	// Operations
public:
	void AddObjectWithProp( IManipulator *ptr );
	void ClearVariables();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyDockBar)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
//	void SetPropertyDialogTreeItem( CKeyFrameTreeItem *pItem );
	
private:
	CFrameTree m_tree;
	CPtr<IManipulator> m_pCurrentObject;
	

	std::map<std::string, HTREEITEM> m_varHandles;
	int		GetVariable( std::string &name );
	void	AddRootVariable( std::string &str, int variable );
	void	AddManipulatorVariable( std::string &str, IManipulator *ptr ); // добавляет пустые промежуточные nod'ы + конечный( редактируемый ) node
	
	HTREEITEM	AddEmptyNode( std::string &str, HTREEITEM hPARoot = TVI_ROOT ); // node который не содержит данных
	HTREEITEM	AddPropertieNode( std::string &str, std::string &propName,IManipulator *ptr, HTREEITEM hPARoot = TVI_ROOT ); 
	
	
	// Generated message map functions
protected:
	
	//{{AFX_MSG(CPropertyDockBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyframeDeleteNode();
	afx_msg void OnKeyframeResetAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif	//__PROPERTY_DOCK_H__
