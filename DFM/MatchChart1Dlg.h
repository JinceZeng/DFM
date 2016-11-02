#pragma once
#include "afxwin.h"


// CMatchChart1Dlg dialog

class CMatchChart1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMatchChart1Dlg)

public:
	CMatchChart1Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMatchChart1Dlg();

// Dialog Data
	enum { IDD = IDD_MATCHCHART1_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbAdapterType;//转接器型号选择
	double m_dAdapterArea;//导线截面积范围
	int m_nWireNum; //单端最大导线根数
	bool isMatch;   //是否满足匹配规则
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
