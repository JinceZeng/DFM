// ProductStep4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep4Dlg.h"
#include "afxdialogex.h"


// CProductStep4Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep4Dlg, CDialogEx)

CProductStep4Dlg::CProductStep4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep4Dlg::IDD, pParent)
{

}

CProductStep4Dlg::~CProductStep4Dlg()
{
}

void CProductStep4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductStep4Dlg, CDialogEx)
END_MESSAGE_MAP()


// CProductStep4Dlg message handlers
/////////////////////////////////////���ǰҳ(����һҳ����һҳת����ҳ�������)
//����ֻ��һ���ṹ��Ϣ������CListCtl�Ļ�����Ա�����Ϣ�������Լ�����CListCtrl
DWORD CProductStep4Dlg::OnWizardActive()
{
	//������Ϣ���룬��ɳ�ʼ������

	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////ǰ����һҳ
//���Լ��鲢���浱ǰ����,����-1���л�������0�л�
DWORD CProductStep4Dlg::OnWizardNext()
{

	ShowWindow(SW_HIDE);     //��ʱ����д�����ڼӼ����ж�
	return 0;

}

/////////////////////////////////////////ǰ����һҳ
//���Լ�����һ���������ñ���
DWORD CProductStep4Dlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);        //��ʱ����д�����ڼӼ����ж�
	return 0;
}
