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
/////////////////////////////////////���ǰҳ(����һҳ����һҳת����ҳ�������)
//����ֻ��һ���ṹ��Ϣ������CListCtl�Ļ�����Ա�����Ϣ�������Լ�����CListCtrl
DWORD CProductStep3Dlg::OnWizardActive()
{
	//������Ϣ���룬��ɳ�ʼ������

	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////ǰ����һҳ
//���Լ��鲢���浱ǰ����,����-1���л�������0�л�
DWORD CProductStep3Dlg::OnWizardNext()
{

	ShowWindow(SW_HIDE);     //��ʱ����д�����ڼӼ����ж�
	return 0;

}

/////////////////////////////////////////ǰ����һҳ
//���Լ�����һ���������ñ���
DWORD CProductStep3Dlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);        //��ʱ����д�����ڼӼ����ж�
	return 0;
}
