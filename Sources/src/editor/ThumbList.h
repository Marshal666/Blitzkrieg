#if !defined(AFX_THUMBLIST_H__5F1FB4A5_8A47_46CC_891C_DCA8A658B640__INCLUDED_)
#define AFX_THUMBLIST_H__5F1FB4A5_8A47_46CC_891C_DCA8A658B640__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThumbList.h : header file
//

#define IDC_LIST_THUMB_CONTROL 1015
const UINT WM_THUMB_LIST_SELECT	= WM_USER + 25;		// ��������� ���������� item � Thumb List control, ���������� ��������
const UINT WM_THUMB_LIST_DBLCLK = WM_USER + 26;		// double click on the Thumb List control, ���������� ��������
const UINT WM_THUMB_LIST_DELETE = WM_USER + 27;		// ������������ ����� delete � �������� Thumb List

const int THUMBNAIL_WIDTH  = 100;
const int THUMBNAIL_HEIGHT = 100;
const int THUMBNAIL_SPACE_X  = 10;
const int THUMBNAIL_SPACE_Y  = 20;


using namespace std;
struct SThumbData
{
	int nImageId;							//������ item � image list
	DWORD dwData;							//����� ����� ��������� ���������������� ������, lParam
	string szThumbName;				//��� item

	SThumbData() : nImageId(-1), dwData(0), szThumbName("") {}
};
typedef list<SThumbData> CListOfThumbData;

struct SThumbItems
{
	CListOfThumbData thumbDataList;			// vector holding the image data
	int nSelectedItem;

	SThumbItems();
};

/////////////////////////////////////////////////////////////////////////////
// CThumbList window

class CThumbList : public CWnd
{
// Construction
public:
	CThumbList( bool bHorz = false );
	virtual ~CThumbList();
	
// Attributes
private:
	CListCtrl	m_ListThumbnail;
	SThumbItems *m_pActiveThumbItems;
	bool bHorizontal;
	bool bValidIML;

// Operations
public:
	//������������� ������� ThumbItems � ����������� �������� ThumbList
//	void ChangeActiveImageList( CImageList *pIML );
	void SetActiveThumbItems( SThumbItems *pNewActiveThumbs, CImageList *pIML );
	//��������� ��� images .tga �� ������ ���������� � pThumbItems
	void LoadAllImagesFromDir( SThumbItems *pThumbItems, CImageList *pIML, const char *szDir, bool bShowAlpha = false );
	//��������� ���� ���� � image list � ���������� ������ ���������� item
	int LoadImageToImageList( CImageList *pIML, char *szFileName, const char *szDir, bool bShowAlpha = false );

/*
	//��������� images � ������� �� ������ ���� ������ pThumbItems �� ������ ���������� � pThumbItems
	void LoadImagesFromFileNameList( SThumbItems *pThumbItems, const char *szDir );
*/

	//������� �� �������� ������ � ������� image index ��� ���� ��������� � ���� ������, ��������� ������������� ���� � ������� � � pAllItems
	void LoadImageIndexFromThumbs( SThumbItems *pAllItems, CImageList *pIML );


	//��������� ����� item � ����� ThumbList
	int InsertItemToEnd( const char *szItemName, int nImageIndex );

	//��������� ����� item ����� �������� ����������� �������� ThumbList
//	int InsertItemAfterSelection( char *szFileName, const char *szDir );

	bool HasValidImageList() { return bValidIML; }
	//���������� ������� ImageList
	CImageList *GetCurrentImageList() { return m_ListThumbnail.GetImageList(LVSIL_NORMAL); }
	//������� ����� ThumbItems item � ��������� ����������������� �������, ���������� index ���� �����, ����� -1
	int GetItemIndexWithUserData( DWORD dwData );
	//���������� index ����������� item
	int GetSelectedItemIndex();
	//���������� ��� item
	string GetItemName( int nIndex );
	//���������� image index ������� item
	int GetItemImageIndex( int nIndex );
	//�������� item � nIndex
	void SelectItem( int nIndex );
	//������� item � ������ index
	void DeleteItem( int nIndex );
	
	void  SetUserDataForItem( int nItemIndex, DWORD dwData );
	DWORD GetUserDataForItem( int nItemIndex );
	
	int GetThumbsCount() { return m_ListThumbnail.GetItemCount(); }

	void TestInsertSomeItems();
	//������ ������ list control
//	CListCtrl *GetListCtrl() { return &m_ListThumbnail; }

protected:
	void CreateListElements();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbList)
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CThumbList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickListThumb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClickListThumb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListThumb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemStateChanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBLIST_H__5F1FB4A5_8A47_46CC_891C_DCA8A658B640__INCLUDED_)
