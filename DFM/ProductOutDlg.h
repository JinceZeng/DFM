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
	CTechValListCtrl m_ValueResultList;     //list���Ʊ���

	vector<CResultChartItem> m_ListCtrlItem;     //�洢List��Ŀ
	vector<CLowValItem> m_LowValItem; //����ͷ���Ľ����
	vector<CIndexValItem> m_IndexVal;   //����ָ��÷�

	void GetItemInfo(vector<CString>& ItemVal);   //��ȡ��Ŀ��Ϣ
	void SetListItem(vector<CResultChartItem> &m_ListCtrlItem); //����list��Ŀ
	void GetResultInfo(vector<CLowValItem>& m_LowValItem,vector<CIndexValItem>& m_IndexVal);//��m_LowValItem��m_IndexVal��ֵ


	afx_msg LRESULT OnIndexMatch(WPARAM wParam,LPARAM lParam); //˫�������Ի���


};
