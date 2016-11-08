#pragma once
#include "afxwin.h"


// CMatchChart3Dlg dialog

class CMatchChart3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMatchChart3Dlg)

public:
	CMatchChart3Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMatchChart3Dlg();

// Dialog Data
	enum { IDD = IDD_MATCHCHART3_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbTMSType;//TMS����
	CComboBox m_cmbKTType; //KT����
	bool isMatch;          //�Ƿ�����ƥ�����
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
