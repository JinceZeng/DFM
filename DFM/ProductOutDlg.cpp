// ProductOutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductOutDlg.h"
#include "afxdialogex.h"


// CProductOutDlg dialog

IMPLEMENT_DYNAMIC(CProductOutDlg, CDialogEx)

CProductOutDlg::CProductOutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductOutDlg::IDD, pParent)
{

}

CProductOutDlg::~CProductOutDlg()
{
}

void CProductOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductOutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProductOutDlg message handlers

/////////////////////////////////////激活当前页(从上一页或下一页转到本页都会调用)
//由于只有一个结构信息，利用CListCtl的缓存可以保存信息，不用自己更新CListCtrl
DWORD CProductOutDlg::OnWizardActive()
{
	//接受信息输入，完成初始化工作

	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////前往下一页
//可以检验并保存当前工作,返回-1不切换，返回0切换
DWORD CProductOutDlg::OnWizardNext()
{

	ShowWindow(SW_HIDE);     //暂时这样写，后期加检验判断
	return 0;

}

/////////////////////////////////////////前往上一页
//可以检验上一步工作不用保存
DWORD CProductOutDlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);        //暂时这样写，后期加检验判断
	return 0;
}