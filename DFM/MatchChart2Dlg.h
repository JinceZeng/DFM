#pragma once
#include "afxwin.h"


// CMatchChart2Dlg dialog

class CMatchChart2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMatchChart2Dlg)

public:
	CMatchChart2Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMatchChart2Dlg();

// Dialog Data
	enum { IDD = IDD_MATCHCHART2_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbTMSType;//TMS类型
	double m_dWireD;//线径
	bool isMatch;   //是否满足匹配规则
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
