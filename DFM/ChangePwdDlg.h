#pragma once


// CChangePwdDlg dialog

class CChangePwdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePwdDlg)

public:
	CChangePwdDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChangePwdDlg();

// Dialog Data
	enum { IDD = IDD_CHANGEPWD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int i_limint;
	_RecordsetPtr m_pRs;
	CString m_Old;
	CString m_Pwd;
	CString m_Pwd1;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonReset();
};
