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
		AfxMessageBox(CString("请输入旧密码"));
		m_Pwd = "";
		m_Pwd1 = "";
		return;
	}
	if (m_Pwd.IsEmpty()){
		AfxMessageBox(CString("密码不能为空"));
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
		AfxMessageBox(CString("请输入以字母开头长度在8-18的字母、数字、下划线组合"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);   //成员变量值赋给控件
		return;
	}
	if (m_Pwd1.IsEmpty()){
		AfxMessageBox(CString("请重复输入密码"));
		return;
	}
	if (m_Pwd != m_Pwd1){
		AfxMessageBox(CString("密码不一致!"));
		m_Pwd = "";
		m_Pwd1 = "";
		UpdateData(false);
		return;
	}
	if (m_Old != theApp.pwd){
		AfxMessageBox(CString("请输入正确的旧密码!"));
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
	AfxMessageBox(CString("密码修改成功!"));	
}


void CChangePwdDlg::OnBnClickedButtonReset()
{
	// TODO: Add your control notification handler code here
	m_Old = "";
	m_Pwd = "";
	m_Pwd1 = "";
	UpdateData(false);
}
