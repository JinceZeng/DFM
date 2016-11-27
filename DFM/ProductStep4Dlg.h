#pragma once
#include "afxcmn.h"
#include "TechValListCtrl.h"
#include "goldata.h"

// CProductStep4Dlg dialog

class CProductStep4Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep4Dlg)

public:
	CProductStep4Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep4Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP4_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//////////////////////////上一页到下一页的操作
	DWORD OnWizardActive();     //激活执行初始化操作

	////////////////////////当前页进入下一页
	DWORD OnWizardNext();       //可以检验并保存当前工作

	///////////////////////当前页进入上一页（由CListCtrl能自动保存信息，所以只需在 OnWizardNext保存信息传递到下一页）
	DWORD OnWizardPrevious();   //可以检验上一步工作不用保存

	CTechValListCtrl m_ThreeProValList;//list控制变量
	vector<CString> m_Lvl3TechID;              //第三层工艺指标ID
	vector<vector<CString>> m_IndexValInfo;    //存储指标评分的评分项和对应分值，用于之后匹配（依次访问数据库会引起堆栈崩溃） 
	vector<CTechChartItem> m_ListCtrlItem;     //存储List条目

	vector<CLowValItem> m_LowValItem;          //存储低分项
	int m_LowValItemNum;                     //记录低分项条目数
	void SaveLowValItem(vector<CTechChartItem>& m_ListCtrlItem);   //保存低分项


	void ReadTechChart(CProductInfo &m_ProductInfo);              //读取工艺表
	void ShowListCtrl();                                          //显示评分表
	void SetListItem(vector<CTechChartItem> &m_ListCtrlItem);     //设置list条目

	afx_msg LRESULT OnSetIndexVal(WPARAM wParam,LPARAM lParam);//设置指标得分
};
