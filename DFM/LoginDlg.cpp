// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "DFMDlg.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_Uname(_T(""))
	, m_Upassword(_T(""))
	,i(0)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UNAME, m_Uname);
	DDX_Text(pDX, IDC_EDIT_UPSW, m_Upassword);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg message handlers


void CLoginDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!m_Uname.IsEmpty() && !m_Upassword.IsEmpty()){
		CString sql = CString("select * from Login where Uname='") + m_Uname + "' and Upasswd='" + m_Upassword + "'";
		//CString str = CString("select Upasswd from Login");
		//m_pRs = theApp.m_pCon->Execute(_bstr_t(str), NULL, adCmdText);
		//CString str_pwd;
		//str_pwd = m_pRs->GetCollect("Upasswd");
		try{					
			//m_pRs.CreateInstance("ADODB.Recordset");
			//m_pRs->Open((_variant_t)sql, theApp.m_pCon.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);

			if (m_pRs->adoEOF){				
				m_Uname = "";
				m_Upassword = "";
				UpdateData(false);
				++i;
				if (i >= 3){
					AfxMessageBox(CString("错误次数太多！"));
					OnBnClickedCancel();	
					return;
				}
				AfxMessageBox(CString("用户名或密码错误"));
				return;
			}
			else{
				theApp.name = m_Uname;
				theApp.pwd = m_Upassword;
				CDialogEx::OnOK();
				return;
			}										

		}
		catch(_com_error e){
			CString temp;
			temp.Format(CString("连接数据库错误:%s"), e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
	}
	else{
		AfxMessageBox(CString("用户名密码不能为空"));
		m_Upassword = "";
		UpdateData(false);
		return;
	}	
	CDialogEx::OnOK();
}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_LOGIN)), TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
