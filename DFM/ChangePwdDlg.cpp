// ChangePwdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ChangePwdDlg.h"
#include "afxdialogex.h"
#include "DFMDlg.h"
#include <regex>
using namespace std;

// CChangePwdDlg dialog

IMPLEMENT_DYNAMIC(CChangePwdDlg, CDialogEx)

CChangePwdDlg::CChangePwdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangePwdDlg::IDD, pParent)
	, m_Old(_T(""))
	, m_Pwd(_T(""))
	, m_Pwd1(_T(""))
	,i_limint(0)
{

}

CChangePwdDlg::~CChangePwdDlg()
{
}

void CChangePwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OLD, m_Old);
	DDX_Text(pDX, IDC_EDIT_PWD, m_Pwd);
	DDX_Text(pDX, IDC_EDIT_REPWD, m_Pwd1);
}


BEGIN_MESSAGE_MAP(CChangePwdDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CChangePwdDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CChangePwdDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CChangePwdDlg message handlers


void CChangePwdDlg::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_Old.IsEmpty())
	{
		AfxMessageBox(CString("�����������"));
		m_Pwd = "";
		m_Pwd1 = "";
		return;
	}
	if (m_Pwd.IsEmpty()){
		AfxMessageBox(CString("���벻��Ϊ��"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		return;
	}
	smatch p_results;
	string str_pwd = (char*)(_bstr_t)(m_Pwd);
	string str_1 = "^[A-Za-z]\\w{7,17}$";
	regex reg(str_1);
	if (!regex_search(str_pwd, p_results, reg)){
		AfxMessageBox(CString("����������ĸ��ͷ������8-18����ĸ�����֡��»������"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);   //��Ա����ֵ�����ؼ�
		return;
	}
	if (m_Pwd1.IsEmpty()){
		AfxMessageBox(CString("���ظ���������"));
		return;
	}
	if (m_Pwd != m_Pwd1){
		AfxMessageBox(CString("���벻һ��!"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		return;
	}
	if (m_Old != theApp.pwd){
		AfxMessageBox(CString("��������ȷ�ľ�����!"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		++i_limint;
		if (i_limint>=3){
			CDialogEx::OnCancel();
		}
		return;
	}
	theApp.m_pConnect->Execute((_bstr_t)(CString("update Login set Upasswd='") + m_Pwd + "' where Uname='" + theApp.name + "'"), NULL, adCmdText);
	m_Old = "";
	m_Pwd = "";
	m_Pwd1 = "";
	UpdateData(false);
	AfxMessageBox(CString("�����޸ĳɹ�!"));	
}


void CChangePwdDlg::OnBnClickedButtonReset()
{
	// TODO: Add your control notification handler code here
	m_Old = "";
	m_Pwd = "";
	m_Pwd1 = "";
	UpdateData(false);
}
