// LowValChartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "LowValChartDlg.h"
#include "afxdialogex.h"


// CLowValChartDlg dialog

IMPLEMENT_DYNAMIC(CLowValChartDlg, CDialogEx)

CLowValChartDlg::CLowValChartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLowValChartDlg::IDD, pParent)
{

}

CLowValChartDlg::~CLowValChartDlg()
{
	vector<CLowValItem>().swap(m_LowValItem);
}

void CLowValChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOWVAL, m_LowValList);
}


BEGIN_MESSAGE_MAP(CLowValChartDlg, CDialogEx)
END_MESSAGE_MAP()


// CLowValChartDlg message handlers


BOOL CLowValChartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//将列表控件先初始化,插入表头
	CRect rect1;
	int width1;
	m_LowValList.GetClientRect(&rect1);
	width1=rect1.Width();

	m_LowValList.InsertColumn(0,CString("序号"),LVCFMT_CENTER,width1/12);
	m_LowValList.InsertColumn(1,CString("所属表"),LVCFMT_CENTER,width1/6);
	m_LowValList.InsertColumn(2,CString("类别"),LVCFMT_CENTER,width1/6);
	m_LowValList.InsertColumn(3,CString("指标名"),LVCFMT_CENTER,width1/6);
	m_LowValList.InsertColumn(4,CString("扣分值"),LVCFMT_CENTER,width1/12);
	m_LowValList.InsertColumn(5,CString("建议"),LVCFMT_CENTER,width1/3);


	SetListItem(m_LowValItem);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLowValChartDlg::GetInfo(vector<CLowValItem>& m_LowValItem)
{
	this->m_LowValItem=m_LowValItem;
}

void CLowValChartDlg::SetListItem(vector<CLowValItem>& m_LowValItem)
{
	//list信息写入
	m_LowValList.DeleteAllItems();
	for (int i=0;i<m_LowValItem.size();++i)
	{
		m_LowValList.InsertItem(i,m_LowValItem[i].m_Item);
		m_LowValList.SetItemText(i,1,m_LowValItem[i].m_ChartNam);
		m_LowValList.SetItemText(i,2,m_LowValItem[i].m_Classify);
		m_LowValList.SetItemText(i,3,m_LowValItem[i].m_TechEvalIndex);
		m_LowValList.SetItemText(i,4,m_LowValItem[i].m_IndexScore);
		m_LowValList.SetItemText(i,5,m_LowValItem[i].m_LowValAdvice);
	}
}
