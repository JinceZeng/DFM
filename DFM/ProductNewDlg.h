#pragma once
#include "afxwin.h"
#include <vector>
using std::vector;

#include "ProductStep0Dlg.h"
#include "ProductStep1Dlg.h"
#include "ProductStep2Dlg.h"
#include "ProductStep3Dlg.h"
#include "ProductOutDlg.h"

// CProductNewDlg dialog

class CProductNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductNewDlg)

public:
	CProductNewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductNewDlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTNEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
public:
	vector<CDialogEx*> m_pPageList;   //记录各子对话框
	int m_nCurrentPage;               //当前显示页
	bool bInfoWrited;                 //产品信息是否已写入
	CRect m_rectPanel;                //子对话框的包围圈
	void ShowPage(UINT nPos);         //显示nPos页面从0开始索引
	void SetWizButton(UINT nPos);     //根据页面情况设置按钮状态
	void SetTextShow(UINT nPos);      //根据页面情况设置文本显示 
	afx_msg void OnBnClickedEvalpre();   //前一步
	afx_msg void OnBnClickedEvalnext();  //下一步
	afx_msg void OnBnClickedEvalin();    //进入评价
};
