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
	CComboBox m_cmbAdapterType;//ת�����ͺ�ѡ��
	double m_dAdapterArea;//���߽������Χ
	int m_nWireNum; //��������߸���
	bool isMatch;   //�Ƿ�����ƥ�����
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
