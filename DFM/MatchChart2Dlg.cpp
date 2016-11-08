// MatchChart2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "MatchChart2Dlg.h"
#include "afxdialogex.h"


// CMatchChart2Dlg dialog

IMPLEMENT_DYNAMIC(CMatchChart2Dlg, CDialogEx)

CMatchChart2Dlg::CMatchChart2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMatchChart2Dlg::IDD, pParent)
	, m_dWireD(0)
	,isMatch(false)
{

}

CMatchChart2Dlg::~CMatchChart2Dlg()
{
}

void CMatchChart2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TMSTYPE, m_cmbTMSType);
	DDX_Text(pDX, IDC_EDIT_WIRED, m_dWireD);
}


BEGIN_MESSAGE_MAP(CMatchChart2Dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMatchChart2Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMatchChart2Dlg message handlers


BOOL CMatchChart2Dlg::OnInitDialog()
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
		CString str = (CString)(m_pRs->GetCollect("TMSType")); 
		m_cmbTMSType.InsertString(i,str);
		i++;
		m_pRs->MoveNext();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CMatchChart2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strType;
	m_cmbTMSType.GetLBText(m_cmbTMSType.GetCurSel(),strType);
	_RecordsetPtr m_pRs;
	CString sql = CString("select * from TMSMatching where TMSType= '")+strType+CString("'");
	m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);

	//获取线径上下限要求
	CString strDia=(CString)(m_pRs->GetCollect("WireDiameter"));
	CString strDiaLower=strDia.Left(strDia.Find('-'));
	CString strDiaTop=strDia.Right(strDia.GetLength()-strDia.Find('-')-1);
	double intDiaLower=_tstof(strDiaLower);  //cstring转double
	double intDiaTop=_tstof(strDiaTop);  

	if (m_dWireD>intDiaLower&&m_dWireD<intDiaTop)
		isMatch=true;
	else isMatch=false;
	CDialogEx::OnOK();
}
