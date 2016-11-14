#pragma once
#include "afxwin.h"


// CChoosePathDlg dialog

class CChoosePathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChoosePathDlg)

public:
	CChoosePathDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChoosePathDlg();

// Dialog Data
	enum { IDD = IDD_CHOOSEPATH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editPath;
	CString m_editPathTxt;
	afx_msg void OnBnClickedButtonView();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
