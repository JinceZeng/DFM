// ProductOutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductOutDlg.h"
#include "afxdialogex.h"


// CProductOutDlg dialog

IMPLEMENT_DYNAMIC(CProductOutDlg, CDialogEx)

CProductOutDlg::CProductOutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductOutDlg::IDD, pParent)
{

}

CProductOutDlg::~CProductOutDlg()
{
	vector<CResultChartItem>().swap(m_ListCtrlItem);
}

void CProductOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RESULT, m_ValueResultList);
}


BEGIN_MESSAGE_MAP(CProductOutDlg, CDialogEx)
	ON_MESSAGE(WM_INDEXMATCH,&CProductOutDlg::OnIndexMatch)
END_MESSAGE_MAP()


// CProductOutDlg message handlers


BOOL CProductOutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//将列表控件先初始化,插入表头
	CRect rect1;
	int width1;
	m_ValueResultList.GetClientRect(&rect1);
	width1=rect1.Width();

	m_ValueResultList.InsertColumn(0,CString("序号"),LVCFMT_CENTER,width1/4);
	m_ValueResultList.InsertColumn(1,CString("项目"),LVCFMT_CENTER,width1/4);
	m_ValueResultList.InsertColumn(2,CString("目标值"),LVCFMT_CENTER,width1/2);


	//设置不可编辑列
	vector<int> nNoEdit;
	nNoEdit.push_back(0);               //第零列不可以编辑
	nNoEdit.push_back(1);  
	nNoEdit.push_back(2);  
	m_ValueResultList.SetnNoEditList(nNoEdit);
	vector<int>().swap(nNoEdit);        //释放vector

	SetListItem(m_ListCtrlItem);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CProductOutDlg::GetItemInfo(vector<CString>& ItemVal)
{
	int nItem=1;
	vector<CString> strItemNam;
	strItemNam.push_back(CString("产品名称"));
	strItemNam.push_back(CString("产品编号"));
	strItemNam.push_back(CString("综合评价结果"));
	strItemNam.push_back(CString("低分项及改进建议"));
	strItemNam.push_back(CString("指标得分值"));

	for (int i=0;i<strItemNam.size();++i,++nItem)
	{
		CString strItem;
		strItem.Format(CString("%d"),nItem);

		CResultChartItem tempItem;
		tempItem.nItem=strItem;
		tempItem.m_ItemNam=strItemNam[i];
		tempItem.m_ItemVal=ItemVal[i];

		m_ListCtrlItem.push_back(tempItem);
	}
	vector<CString>().swap(strItemNam);

}


void CProductOutDlg::SetListItem(vector<CResultChartItem> &m_ListCtrlItem)
{
	//list信息写入
	m_ValueResultList.DeleteAllItems();
	for (int i=0;i<m_ListCtrlItem.size();++i)
	{
		m_ValueResultList.InsertItem(i,m_ListCtrlItem[i].nItem);
		m_ValueResultList.SetItemText(i,1,m_ListCtrlItem[i].m_ItemNam);
		m_ValueResultList.SetItemText(i,2,m_ListCtrlItem[i].m_ItemVal);
	}
}

//获取CProductNewDlg类的信息，给m_LowValItem、m_IndexVal赋值
void  CProductOutDlg::GetResultInfo(vector<CLowValItem>& m_LowValItem,vector<CIndexValItem>& m_IndexVal)
{
	this->m_LowValItem=m_LowValItem;
	this->m_IndexVal=m_IndexVal;
}

LRESULT CProductOutDlg::OnIndexMatch(WPARAM wParam,LPARAM lParam)
{
	CString strItemName=m_ValueResultList.GetItemText(wParam,1);
	if(strItemName==CString("低分项及改进建议"))
	{
		CLowValChartDlg dlg;
		dlg.GetInfo(m_LowValItem);
		dlg.DoModal();
	}
	else if (strItemName==CString("指标得分值"))
	{
		CIndexValChartDlg dlg;
		dlg.GetInfo(m_IndexVal);
		dlg.DoModal();
	}
	return 0;
}