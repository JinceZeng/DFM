#pragma once


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
};

