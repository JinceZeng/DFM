// IndexValChartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "IndexValChartDlg.h"
#include "afxdialogex.h"


// CIndexValChartDlg dialog

IMPLEMENT_DYNAMIC(CIndexValChartDlg, CDialogEx)

CIndexValChartDlg::CIndexValChartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIndexValChartDlg::IDD, pParent)
{

}

CIndexValChartDlg::~CIndexValChartDlg()
{
	vector<CIndexValItem>().swap(m_IndexVal);
}

void CIndexValChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INDEXVAL, m_IndexValList);
}


BEGIN_MESSAGE_MAP(CIndexValChartDlg, CDialogEx)
END_MESSAGE_MAP()


// CIndexValChartDlg message handlers


BOOL CIndexValChartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//将列表控件先初始化,插入表头
	CRect rect1;
	int width1;
	m_IndexValList.GetClientRect(&rect1);
	width1=rect1.Width();

	m_IndexValList.InsertColumn(0,CString("序号"),LVCFMT_CENTER,width1/3);
	m_IndexValList.InsertColumn(1,CString("指标名"),LVCFMT_CENTER,width1/3);
	m_IndexValList.InsertColumn(2,CString("评分值"),LVCFMT_CENTER,width1/3);

	SetListItem(m_IndexVal);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CIndexValChartDlg::GetInfo(vector<CIndexValItem>& m_IndexVal)
{
	this->m_IndexVal=m_IndexVal;
}

void CIndexValChartDlg::SetListItem(vector<CIndexValItem>& m_IndexVal)
{
	m_IndexValList.DeleteAllItems();
	for (int i=0;i<m_IndexVal.size();++i)
	{
		m_IndexValList.InsertItem(i,m_IndexVal[i].m_Item);
		m_IndexValList.SetItemText(i,1,m_IndexVal[i].m_IndexNam);
		m_IndexValList.SetItemText(i,2,m_IndexVal[i].m_IndexVal);
	}
}
