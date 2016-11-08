#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TechValListCtrl.h"
#include "goldata.h"
#include "IndexInfo1Dlg.h"


// CProductStep3Dlg dialog

class CProductStep3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep3Dlg)

public:
	CProductStep3Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep3Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP3_DLG };

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

	CEdit m_IndexInfoTxt;                      //编辑框控制变量，显示评分细节
	CFont m_editFont;                          //字体
	CTechValListCtrl m_ImpactVibValList;       //listctrl控制变量
	vector<CString> m_Lvl3TechID;              //第三层工艺指标ID
	vector<vector<CString>> m_IndexValInfo;    //存储指标评分的评分项和对应分值，用于之后匹配（依次访问数据库会引起堆栈崩溃） 
	vector<CTechChartItem> m_ListCtrlItem;     //存储List条目
	vector<CString> m_IndexInfo;               //存储指标评价说明
	CIndexInfo1Dlg *pDlg;                      //用于创建非模态对话框               

	void ReadTechChart(CProductInfo &m_ProductInfo);              //读取工艺表
	void ShowListCtrl();                                          //显示评分表
	void SetListItem(vector<CTechChartItem> &m_ListCtrlItem);     //设置list条目

	afx_msg LRESULT OnSetIndexInfo(WPARAM wParam,LPARAM lParam);  //设置指标评分说明
	//afx_msg LRESULT OnDeletepDlg(WPARAM wParam,LPARAM lParam);    //释放pDlg成员指针(不知道怎么获取父窗口句柄没用)
	afx_msg LRESULT OnSetIndexVal(WPARAM wParam,LPARAM lParam);//设置指标得分
};
