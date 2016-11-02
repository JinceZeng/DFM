#pragma once
#include "TechValListCtrl.h"
#include "goldata.h"

// CProductStep1Dlg dialog

class CProductStep1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep1Dlg)

public:
	CProductStep1Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep1Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP1_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//响应主对话框几个按钮的消息
	DWORD OnWizardActive();     //激活执行初始化操作
	DWORD OnWizardNext();       //可以检验并保存当前工作
	DWORD OnWizardPrevious();   //可以检验上一步工作，不用保存
public:
	virtual BOOL OnInitDialog();
	CTechValListCtrl m_TechValList;            //listctrl控制变量
	vector<CString> m_Lvl3TechID;              //第三层工艺指标ID
	//vector<vector<CString>> m_Lvl4TechID;      //第三层指标对应的第四层指标ID
	//vector<vector<CString>> m_Lvl4TechWeight;  //第四层指标权重
	vector<CTechChartItem> m_ListCtrlItem;     //存储List条目
	void ReadTechChart(CProductInfo &m_ProductInfo);                      //读取工艺表
	void ShowListCtrl();                         //显示评分表
	void SetListItem(vector<CTechChartItem> &m_ListCtrlItem);     //设置list条目

	BOOL m_bLegal;                                    //检测合理性问题
	//void DeleteStructInfo();      //当上一页结构发生更改时，要删除原结构,会被重复使用
};

