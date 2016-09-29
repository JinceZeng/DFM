// ProductStep3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep3Dlg.h"
#include "afxdialogex.h"


// CProductStep3Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep3Dlg, CDialogEx)

CProductStep3Dlg::CProductStep3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep3Dlg::IDD, pParent)
{

}

CProductStep3Dlg::~CProductStep3Dlg()
{
}

void CProductStep3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductStep3Dlg, CDialogEx)
END_MESSAGE_MAP()


// CProductStep3Dlg message handlers
/////////////////////////////////////激活当前页(从上一页或下一页转到本页都会调用)
//由于只有一个结构信息，利用CListCtl的缓存可以保存信息，不用自己更新CListCtrl
DWORD CProductStep3Dlg::OnWizardActive()
{
	//接受信息输入，完成初始化工作

	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////前往下一页
//可以检验并保存当前工作,返回-1不切换，返回0切换
DWORD CProductStep3Dlg::OnWizardNext()
{

	ShowWindow(SW_HIDE);     //暂时这样写，后期加检验判断
	return 0;

}

/////////////////////////////////////////前往上一页
//可以检验上一步工作不用保存
DWORD CProductStep3Dlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);        //暂时这样写，后期加检验判断
	return 0;
}
