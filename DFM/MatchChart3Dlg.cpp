// MatchChart3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "MatchChart3Dlg.h"
#include "afxdialogex.h"


// CMatchChart3Dlg dialog

IMPLEMENT_DYNAMIC(CMatchChart3Dlg, CDialogEx)

CMatchChart3Dlg::CMatchChart3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMatchChart3Dlg::IDD, pParent)
	,isMatch(false)
{

}

CMatchChart3Dlg::~CMatchChart3Dlg()
{
}

void CMatchChart3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TMSTYPE, m_cmbTMSType);
	DDX_Control(pDX, IDC_COMBO_KTType, m_cmbKTType);
}


BEGIN_MESSAGE_MAP(CMatchChart3Dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMatchChart3Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMatchChart3Dlg message handlers


BOOL CMatchChart3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//初始化下拉菜单
	_RecordsetPtr m_pRs;
	CString sql = CString("select * from TMSMatching");
	m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
	int i=0;
	while (!m_pRs->adoEOF)
	{
		CString str1 = (CString)(m_pRs->GetCollect("TMSType")); 
		CString str2 = (CString)(m_pRs->GetCollect("KTType"));
		m_cmbTMSType.InsertString(i,str1);
		m_cmbKTType.InsertString(i,str2);
		i++;
		m_pRs->MoveNext();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CMatchChart3Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_cmbTMSType.GetCurSel()==m_cmbKTType.GetCurSel())
		isMatch=true;
	else isMatch=false;
	CDialogEx::OnOK();
}
