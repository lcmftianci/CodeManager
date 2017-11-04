
// CodeManagerDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CCodeManagerDlg dialog
class CCodeManagerDlg : public CDialogEx
{
// Construction
public:
	CCodeManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODEMANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CMenu m_MainMenu;									//	主菜单

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListFile;
	CTreeCtrl m_TreeFile;

	CEdit m_edit;			//listctrl编辑时用到的空间

	TCHAR m_Drive[256];
	int m_nDriveNum;

	int m_row;	
	int m_col;		//当前选中的行和列

	void InsertListFile();
	void InsertTreeFile();

     afx_msg void OnNMClickListfile(NMHDR *pNMHDR, LRESULT *pResult);
	 CEdit m_editList;
	 afx_msg void OnEnKillfocusEditlist();
};
