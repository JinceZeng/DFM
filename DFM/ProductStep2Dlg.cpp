// ProductStep2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep2Dlg.h"
#include "afxdialogex.h"


// CProductStep2Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep2Dlg, CDialogEx)

CProductStep2Dlg::CProductStep2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep2Dlg::IDD, pParent)
{

}

CProductStep2Dlg::~CProductStep2Dlg()
{
}

void CProductStep2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductStep2Dlg, CDialogEx)
END_MESSAGE_MAP()


// CProductStep2Dlg message handlers


/////////////////////////////////////���ǰҳ(����һҳ����һҳת����ҳ�������)
//����ֻ��һ���ṹ��Ϣ������CListCtl�Ļ�����Ա�����Ϣ�������Լ�����CListCtrl
DWORD CProductStep2Dlg::OnWizardActive()
{
	//������Ϣ���룬��ɳ�ʼ������

	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////ǰ����һҳ
//���Լ��鲢���浱ǰ����,����-1���л�������0�л�
DWORD CProductStep2Dlg::OnWizardNext()
{

	ShowWindow(SW_HIDE);     //��ʱ����д�����ڼӼ����ж�
	return 0;

}

/////////////////////////////////////////ǰ����һҳ
//���Լ�����һ���������ñ���
DWORD CProductStep2Dlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);        //��ʱ����д�����ڼӼ����ж�
	return 0;
}
