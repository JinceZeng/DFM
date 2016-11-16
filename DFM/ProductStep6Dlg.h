#pragma once
#include "goldata.h"
#include "afxcmn.h"
#include "TechValListCtrl.h"
// CProductStep6Dlg dialog

class CProductStep6Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep6Dlg)

public:
	CProductStep6Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep6Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP6_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//////////////////////////上一页到下一页的操作
	DWORD OnWizardActive();     //激活执行初始化操作

	////////////////////////当前页进入下一页
	DWORD OnWizardNext();       //可以检验并保存当前工作

	///////////////////////当前页进入上一页（由CListCtrl能自动保存信息，所以只需在 OnWizardNext保存信息传递到下一页）
	DWORD OnWizardPrevious();   //可以检验上一步工作不用保存
	virtual BOOL OnInitDialog();
	CTechValListCtrl m_TechMaturyList;
	vector<vector<CString>> m_TechMaturityInfo; //存储工艺成熟度所有信息   
	vector<CString> m_TechType;                 //存储表中工艺类型，用于combo初始化
	vector<CMaturyChartItem> m_ListCtrlItem;    //存储List条目

	afx_msg LRESULT OnDeleteIndexItem(WPARAM wParam,LPARAM lParam); //删除某条评价指标
	afx_msg LRESULT OnAddIndexItem(WPARAM wParam,LPARAM lParam);//添加某条评价指标
	afx_msg LRESULT OnSetIndexVal(WPARAM wParam,LPARAM lParam);//设置指标得分

	void ReadTechChart();              //读取工艺成熟表
};
