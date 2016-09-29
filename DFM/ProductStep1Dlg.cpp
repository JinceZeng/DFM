// ProductStep1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep1Dlg.h"
#include "afxdialogex.h"


// CProductStep1Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep1Dlg, CDialogEx)

CProductStep1Dlg::CProductStep1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep1Dlg::IDD, pParent)
{

}

CProductStep1Dlg::~CProductStep1Dlg()
{
}

void CProductStep1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductStep1Dlg, CDialogEx)
END_MESSAGE_MAP()


// CProductStep1Dlg message handlers
//激活执行初始化操作
DWORD CProductStep1Dlg::OnWizardActive()
{
	//接收外界信息,可以完成一些初始化工作

	ShowWindow(SW_SHOW);
	return 0;
}

//可以检验并保存当前工作
DWORD CProductStep1Dlg::OnWizardNext()
{
	//保存当前工作，传递信息


	ShowWindow(SW_HIDE);
	return 0;
}

//可以检验上一步工作（不会被调用）
DWORD CProductStep1Dlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);
	return 0;
}
