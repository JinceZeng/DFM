#pragma once


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
	//////////////////////////上一页到下一页的操作
	DWORD OnWizardActive();     //激活执行初始化操作

	////////////////////////当前页进入下一页
	DWORD OnWizardNext();       //可以检验并保存当前工作

	///////////////////////当前页进入上一页（由CListCtrl能自动保存信息，所以只需在 OnWizardNext保存信息传递到下一页）
	DWORD OnWizardPrevious();   //可以检验上一步工作不用保存
};
