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
//����ִ�г�ʼ������
DWORD CProductStep1Dlg::OnWizardActive()
{
	//���������Ϣ,�������һЩ��ʼ������

	ShowWindow(SW_SHOW);
	return 0;
}

//���Լ��鲢���浱ǰ����
DWORD CProductStep1Dlg::OnWizardNext()
{
	//���浱ǰ������������Ϣ


	ShowWindow(SW_HIDE);
	return 0;
}

//���Լ�����һ�����������ᱻ���ã�
DWORD CProductStep1Dlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);
	return 0;
}
