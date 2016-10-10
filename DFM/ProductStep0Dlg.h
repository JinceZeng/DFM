#pragma once
#include "afxwin.h"
#include "goldata.h"

#define WM_UPDATEDATA WM_USER+1    //更新对话框控件

// CProductStep0Dlg dialog

class CProductStep0Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep0Dlg)

public:
	CProductStep0Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep0Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP0_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRs;
	CString m_ProductName;  //产品名
	CString m_ProductNum;   //产品编号
	CString m_ProductSub;   //产品隶属组件
	CComboBox m_cmbEvalType;//combo控制变量
	int m_EvalTypeVal;      //combo控制变量
	CString str_EvalType;   //评价类型ID
	CString m_TypeInfo;     //评价类型介绍
	int m_isEval;           //是否已经评价
	CProductInfo m_ProductInfo;//结构体保存产品信息
	virtual BOOL OnInitDialog();
public:
	//响应主对话框几个按钮的消息
	DWORD OnWizardActive();     //激活执行初始化操作
	DWORD OnWizardNext();       //可以检验并保存当前工作
	DWORD OnWizardPrevious();   //可以检验上一步工作，不用保存

	afx_msg LRESULT OnUpdateData(WPARAM wParam,LPARAM lParam);//自定义消息更新控件信息
	void SaveProductInfo();    //保存产品信息
};
