#pragma once
#include "afxcmn.h"
#include "goldata.h"

// CLowValChartDlg dialog

class CLowValChartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLowValChartDlg)

public:
	CLowValChartDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLowValChartDlg();

// Dialog Data
	enum { IDD = IDD_LOWVALCHART_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_LowValList;
	vector<CLowValItem> m_LowValItem;
	virtual BOOL OnInitDialog();
	void GetInfo(vector<CLowValItem>& m_LowValItem);  //获取m_LowValItem值
	void SetListItem(vector<CLowValItem>& m_LowValItem);     //设置list条目

};
