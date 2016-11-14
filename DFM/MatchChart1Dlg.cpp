// MatchChart1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "MatchChart1Dlg.h"
#include "afxdialogex.h"


// CMatchChart1Dlg dialog

IMPLEMENT_DYNAMIC(CMatchChart1Dlg, CDialogEx)

CMatchChart1Dlg::CMatchChart1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMatchChart1Dlg::IDD, pParent)
	, m_dAdapterArea(0)
	, m_nWireNum(0)
	,isMatch(false)
{

}

CMatchChart1Dlg::~CMatchChart1Dlg()
{
}

void CMatchChart1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ADAPTER, m_cmbAdapterType);
	DDX_Text(pDX, IDC_EDIT_ADAPTERAREA, m_dAdapterArea);
	DDX_Text(pDX, IDC_EDIT_WIRENUM, m_nWireNum);
}


BEGIN_MESSAGE_MAP(CMatchChart1Dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMatchChart1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMatchChart1Dlg message handlers


BOOL CMatchChart1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//初始化下拉菜单
	_RecordsetPtr m_pRs;
	CString sql = CString("select * from Adapter_WireMatching");
	m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
	int i=0;
	while (!m_pRs->adoEOF)
	{
		CString str = (CString)(m_pRs->GetCollect("AdapterType")); 
		m_cmbAdapterType.InsertString(i,str);
		i++;
		m_pRs->MoveNext();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CMatchChart1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strType;
	m_cmbAdapterType.GetLBText(m_cmbAdapterType.GetCurSel(),strType);//获取当前下拉单选择的值
	_RecordsetPtr m_pRs;
	CString sql = CString("select * from Adapter_WireMatching where AdapterType= '")+strType+CString("'");
	m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);

	//获取面积上下限要求
	CString strArea=(CString)(m_pRs->GetCollect("AdapterArea"));
	CString strAreaLower=strArea.Left(strArea.Find('-'));
	CString strAreaTop=strArea.Right(strArea.GetLength()-strArea.Find('-')-1);
	double intAreaLower=_tstof(strAreaLower);  //cstring转double
	double intAreaTop=_tstof(strAreaTop);  

	//获取线数要求 
	CString strNum=(CString)(m_pRs->GetCollect("WireNum"));
	int intNum = _ttoi(strNum);                //cstring转int 

	if (m_dAdapterArea>intAreaLower&&m_dAdapterArea<intAreaTop&&m_nWireNum==intNum)
		isMatch=true;
	else isMatch=false;
	CDialogEx::OnOK();
}
