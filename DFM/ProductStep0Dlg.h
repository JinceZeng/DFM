#pragma once
#include "afxwin.h"



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
	CString m_ProductName;
	CString m_ProductNum;
	CString m_ProductSub;
	CComboBox m_cmbEvalType;
	int m_EvalTypeVal;
	CString m_TypeInfo;
	int m_isEval;
	virtual BOOL OnInitDialog();
public:
	//响应主对话框几个按钮的消息
	DWORD OnWizardActive();     //激活执行初始化操作
	DWORD OnWizardNext();       //可以检验并保存当前工作
	DWORD OnWizardPrevious();   //可以检验上一步工作，不用保存
};
