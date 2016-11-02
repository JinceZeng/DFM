// ProductStep1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep1Dlg.h"
#include "afxdialogex.h"
#include "goldata.h"

// CProductStep1Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep1Dlg, CDialogEx)

CProductStep1Dlg::CProductStep1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep1Dlg::IDD, pParent)
{
	m_Lvl3TechID.clear();
	//m_Lvl4TechID.clear();
	//m_Lvl4TechWeight.clear();
	m_ListCtrlItem.clear();
	m_bLegal=FALSE;

}

CProductStep1Dlg::~CProductStep1Dlg()
{
	m_Lvl3TechID.clear();   //vector��������ʱδ�뵽�ð취
	//m_Lvl4TechID.clear();
	//m_Lvl4TechWeight.clear();
	m_ListCtrlItem.clear();

}

void CProductStep1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TECHVAL, m_TechValList);
}


BEGIN_MESSAGE_MAP(CProductStep1Dlg, CDialogEx)
END_MESSAGE_MAP()


// CProductStep1Dlg message handlers


BOOL CProductStep1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	//���б�ؼ��ȳ�ʼ��,�����ͷ
	CRect rect1;
	int width1;
	m_TechValList.GetClientRect(&rect1);
	width1=rect1.Width();

	m_TechValList.InsertColumn(0,CString("���"),LVCFMT_CENTER,width1/10);
	m_TechValList.InsertColumn(1,CString("���"),LVCFMT_CENTER,width1/10);
	m_TechValList.InsertColumn(2,CString("������"),LVCFMT_CENTER,width1*3/10);
	m_TechValList.InsertColumn(3,CString("����������"),LVCFMT_CENTER,width1*2/5);
	m_TechValList.InsertColumn(4,CString("����ֵ"),LVCFMT_CENTER,width1/10);


	//���ò��ɱ༭��
	vector<int> nNoEdit;
	nNoEdit.push_back(0);               //�����в����Ա༭
	nNoEdit.push_back(1);  
	nNoEdit.push_back(2);  
	nNoEdit.push_back(3);  
	m_TechValList.SetnNoEditList(nNoEdit);


	vector<int> nComboLis;
	nComboLis.push_back(3);            //����������Ͽ����
	m_TechValList.SetnComboList(nComboLis);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}





//����ִ�г�ʼ������
DWORD CProductStep1Dlg::OnWizardActive()
{
	//���������Ϣ,�������һЩ��ʼ������

	//ReadTechChart();
	//ShowListCtrl(m_Lvl4TechID);
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
	if(m_TechValList.m_bEditing==TRUE)
	{
		MessageBox(_T("����:�б�ؼ����ڱ༭״̬"));
		return -1;
	}
	else
	{
		m_bLegal=FALSE;
		ShowWindow(SW_HIDE);
		return 0;
	}
}


void CProductStep1Dlg::ReadTechChart(CProductInfo& m_ProductInfo)
{
	_RecordsetPtr m_pRs0;
	m_Lvl3TechID.clear();
	//m_Lvl4TechID.clear();
	int UpID=11;             //��Ѱ����ָ�ָ꣨��IDΪ11��������
	CString strUpID=(CString)(char *)(_bstr_t)(UpID);

	CString sql0 = CString("select * from CreateIndexTree where EvalModelID=")+m_ProductInfo.str_EvalType+CString("and TechEvalIndexUpID=")+strUpID;
	try
	{
	m_pRs0 = theApp.m_pConnect->Execute(_bstr_t(sql0), NULL, adCmdText);
	}
	catch(_com_error e)
	{
		CString temp;
		temp.Format(e.Description());
		AfxMessageBox(temp);
	}
	while (!m_pRs0->adoEOF)
	{
		
		CString str = (CString)(m_pRs0->GetCollect("TechEvalIndexID"));
		m_Lvl3TechID.push_back(str);
		m_pRs0->MoveNext();

	}
	//m_Lvl4TechID.push_back(m_Lvl3TechID);//����ָ��Ҳ���ȥ
	//for(int i=0;i<m_Lvl3TechID.size();i++)
	//{
	//	CString sql1 = CString("select * from CreateIndexTree where EvalModelID=")+m_ProductInfo.str_EvalType+CString("and TechEvalIndexUpID=")+m_Lvl3TechID[i];
	//	m_pRs1 = theApp.m_pConnect->Execute(_bstr_t(sql1), NULL, adCmdText);
	//	vector<CString> vtemp1,vtemp2;
	//	while (!m_pRs1->adoEOF)
	//	{

	//		CString str1 = (CString)(m_pRs1->GetCollect("TechEvalIndexID"));
	//		CString str2 = (CString)(m_pRs1->GetCollect("EvalWeight"));
	//		vtemp1.push_back(str1);
	//		vtemp2.push_back(str2);
	//		m_pRs1->MoveNext();

	//	}
	//	m_Lvl4TechID.push_back(vtemp1);
	//	m_Lvl4TechWeight.push_back(vtemp2);
	//}
}



void CProductStep1Dlg::ShowListCtrl()
{
	_RecordsetPtr m_pRs,m_pRs2;
	m_ListCtrlItem.clear();
	//vector<CString> m_Lvl3TechNam;    //�洢����ָ����
	CTechChartItem m_OneItem;//ÿ��list����Ϣ
	int nItem=1;             //���
	//vector<vector<CString>> m_Lvl4TechNam;
	for (int i=0;i<m_Lvl3TechID.size();i++)
	{
		CString strItem;
		strItem.Format(CString("%d"),nItem);
		CString sql = CString("select * from TechEvalIndex where TechEvalIndexID=")+m_Lvl3TechID[i];
		try
		{
		m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		CString strTechNam=(CString)(m_pRs->GetCollect("TechEvalIndexNam"));
		CString strClassify=(CString)(m_pRs->GetCollect("TechClassify"));

		vector<CString> m_ValComboStr;  //���ڴ洢����combo�ַ�


		CString sql2 = CString("select * from EvalIndexVal where TechEvalIndexID=")+m_Lvl3TechID[i];
		m_pRs2 = theApp.m_pConnect->Execute(_bstr_t(sql2), NULL, adCmdText);


		while(!m_pRs2->adoEOF)
		{
			CString strValInfo=(CString)(m_pRs2->GetCollect("TechEvalIndexValInfo"));
			m_ValComboStr.push_back(strValInfo);
			m_pRs2->MoveNext();
		}
        //ÿ��list��Ϣ
		m_OneItem.nItem=strItem;
		m_OneItem.m_Classify=strClassify;
		m_OneItem.m_TechEvalIndex=strTechNam;
		m_OneItem.m_ValComboStr=m_ValComboStr;

		nItem++;

		m_ListCtrlItem.push_back(m_OneItem);
		}
		catch(_com_error e)
		{
			CString temp;
			temp.Format(e.Description());
			AfxMessageBox(temp);
		}
	}

	//
	//for (int j=1;j<=m_Lvl4TechID[0].size();j++)
	//{
	//	for (int k=0;k<m_Lvl4TechID[j].size();k++)
	//	{
	//		CString strItem;
	//		strItem.Format(CString("%d"),nItem);

	//		CString sql1 = CString("select * from TechEvalIndex where TechEvalIndexID=")+m_Lvl4TechID[j][k];
	//		m_pRs1 = theApp.m_pConnect->Execute(_bstr_t(sql1), NULL, adCmdText);
	//		CString strTechNam=(CString)(m_pRs1->GetCollect("TechEvalIndexNam"));

	//		CString str1=(CString)(m_pRs1->GetCollect("ReqClassify"));
	//		int nReqclass=_ttoi(str1);
	//		CString strReqClassify;
	//		if(nReqclass==1) strReqClassify=CString("����Ҫ��");
	//		else             strReqClassify=CString("����Ҫ��");

	//	    vector<CString> m_ValComboStr;  //���ڴ洢����combo�ַ�
	//		CString sql2 = CString("select * from EvalIndexVal where TechEvalIndexID=")+m_Lvl4TechID[j][k];
	//		m_pRs2 = theApp.m_pConnect->Execute(_bstr_t(sql2), NULL, adCmdText);
	//		while(!m_pRs2->adoEOF)
	//		{
	//			CString strValInfo=(CString)(m_pRs2->GetCollect("TechEvalIndexValInfo"));
	//			m_ValComboStr.push_back(strValInfo);
	//			m_pRs2->MoveNext();
	//		}
	//		
	//		//ÿ��list��Ϣ
	//		m_OneItem.nItem=strItem;
	//		m_OneItem.m_ChooseTech=m_Lvl3TechNam[j-1];
	//		m_OneItem.m_ReqClassify=strReqClassify;
	//		m_OneItem.m_TechEvalIndex=strTechNam;
	//		m_OneItem.m_ValComboStr=m_ValComboStr;
	//		m_OneItem.m_IndexWeigh=m_Lvl4TechWeight[j-1][k];

	//		nItem++;

	//		m_ListCtrlItem.push_back(m_OneItem);
	//	}
	//	
	//}
	SetListItem(m_ListCtrlItem);
}



void CProductStep1Dlg::SetListItem(vector<CTechChartItem>& m_ListCtrlItem)
{
	m_TechValList.DeleteAllItems();
	for (int i=0;i<m_ListCtrlItem.size();i++)
	{
		m_TechValList.InsertItem(i,m_ListCtrlItem[i].nItem);
		m_TechValList.SetItemText(i,1,m_ListCtrlItem[i].m_Classify);
		m_TechValList.SetItemText(i,2,m_ListCtrlItem[i].m_TechEvalIndex);
		m_TechValList.SetComboString(m_ListCtrlItem[i].m_ValComboStr);   //��combo�ַ�����listctrl��չ���е�m_strlisCombo����combo��ʼ��
		//m_TechValList.SetItemText(i,5,m_ListCtrlItem[i].m_IndexWeigh);
	}
}


//void CProductStep1Dlg::DeleteStructInfo()
//{
//	for(int i=0;i<m_Lvl4TechID.size();i++)
//	{
//		int m=m_Lvl4TechID[i].size();
//		for(int j=1;j<m;j++)
//		{
//			delete m_Lvl4TechID[i][j];    //�˲��ᱨ����
//		}
//	}
//
//	if(m_Lvl4TechID.size()>0)
//		delete m_Lvl4TechID[0][0]; 
//
//	m_Lvl4TechID.clear();
//}