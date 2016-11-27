#pragma once
#include "afxcmn.h"
#include "TechValListCtrl.h"
#include "goldata.h"

#include "IndexValChartDlg.h"
#include "LowValChartDlg.h"
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
public:
	virtual BOOL OnInitDialog();
	CTechValListCtrl m_ValueResultList;     //list控制变量

	vector<CResultChartItem> m_ListCtrlItem;     //存储List条目
	vector<CLowValItem> m_LowValItem; //保存低分项及改进意见
	vector<CIndexValItem> m_IndexVal;   //保存指标得分

	void GetItemInfo(vector<CString>& ItemVal);   //获取条目信息
	void SetListItem(vector<CResultChartItem> &m_ListCtrlItem); //设置list条目
	void GetResultInfo(vector<CLowValItem>& m_LowValItem,vector<CIndexValItem>& m_IndexVal);//给m_LowValItem、m_IndexVal赋值


	afx_msg LRESULT OnIndexMatch(WPARAM wParam,LPARAM lParam); //双击弹出对话框


};
