#pragma once


// CProductOutDlg dialog

class CProductOutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductOutDlg)

public:
	CProductOutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductOutDlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTOUT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
