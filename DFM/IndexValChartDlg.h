#pragma once
#include "afxcmn.h"
#include "goldata.h"

// CIndexValChartDlg dialog

class CIndexValChartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIndexValChartDlg)

public:
	CIndexValChartDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIndexValChartDlg();

// Dialog Data
	enum { IDD = IDD_INDEXVALCHART_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_IndexValList;
	vector<CIndexValItem> m_IndexVal;
	virtual BOOL OnInitDialog();
	void GetInfo(vector<CIndexValItem>& m_IndexVal); //获取m_IndexVal值
	void SetListItem(vector<CIndexValItem>& m_IndexVal);     //设置list条目
};
