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

/////////////////////////////////////���ǰҳ(����һҳ����һҳת����ҳ�������)
//����ֻ��һ���ṹ��Ϣ������CListCtl�Ļ�����Ա�����Ϣ�������Լ�����CListCtrl
DWORD CProductOutDlg::OnWizardActive()
{
	//������Ϣ���룬��ɳ�ʼ������

	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////ǰ����һҳ
//���Լ��鲢���浱ǰ����,����-1���л�������0�л�
DWORD CProductOutDlg::OnWizardNext()
{

	ShowWindow(SW_HIDE);     //��ʱ����д�����ڼӼ����ж�
	return 0;

}

/////////////////////////////////////////ǰ����һҳ
//���Լ�����һ���������ñ���
DWORD CProductOutDlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);        //��ʱ����д�����ڼӼ����ж�
	return 0;
}