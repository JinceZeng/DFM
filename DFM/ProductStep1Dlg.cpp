// ProductStep1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep1Dlg.h"
#include "afxdialogex.h"
#include "goldata.h"
#include "MatchChart1Dlg.h"
#include "MatchChart2Dlg.h"
#include "MatchChart3Dlg.h"

// CProductStep1Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep1Dlg, CDialogEx)

CProductStep1Dlg::CProductStep1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep1Dlg::IDD, pParent)
{
	m_Lvl3TechID.clear();
	//m_Lvl4TechID.clear();
	//m_Lvl4TechWeight.clear();
	m_IndexValInfo.clear();
	m_ListCtrlItem.clear();
	m_bLegal=FALSE;

}

CProductStep1Dlg::~CProductStep1Dlg()
{

	vector<CString>().swap(m_Lvl3TechID);
	vector<CTechChartItem>().swap(m_ListCtrlItem);
	vector<vector<CString>>().swap(m_IndexValInfo);

}

void CProductStep1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TECHVAL, m_TechValList);
}


BEGIN_MESSAGE_MAP(CProductStep1Dlg, CDialogEx)
	ON_MESSAGE(WM_SETINDEXVAL,&CProductStep1Dlg::OnSetIndexVal)
	ON_MESSAGE(WM_INDEXMATCH,&CProductStep1Dlg::OnIndexMatch)
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
	vector<int>().swap(nNoEdit);//�ͷ�vector

	vector<int> nComboLis;
	nComboLis.push_back(3);            //����������Ͽ����
	m_TechValList.SetnComboList(nComboLis);
	vector<int>().swap(nComboLis);//�ͷ�vector

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
	//for (int i=0;i<m_ListCtrlItem.size();++i)
	//{
	//	CString str=m_TechValList.GetItemText(i,3);
	//	if(str==CString(""))
	//	{
	//		AfxMessageBox(CString("������δ���"));
	//		return -1;
	//	}
	//}

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
	m_IndexValInfo.clear();
	//vector<CString> m_Lvl3TechNam;    //�洢����ָ����
	CTechChartItem m_OneItem;//ÿ��list����Ϣ
	int nItem=1;             //���
	//vector<vector<CString>> m_Lvl4TechNam;
	for (int i=0;i<m_Lvl3TechID.size();i++)    //���η�������ָ�����ȡָ�������Ϣ
	{
		CString strItem;
		strItem.Format(CString("%d"),nItem);
		CString sql = CString("select * from TechEvalIndex where TechEvalIndexID=")+m_Lvl3TechID[i];
		try
		{
		m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		CString strTechNam=(CString)(m_pRs->GetCollect("TechEvalIndexNam"));
		CString strClassify=(CString)(m_pRs->GetCollect("TechClassify"));

		//����ָ�����ֱ���ȡ��������Ϣ
		CString sql2 = CString("select * from EvalIndexVal where TechEvalIndexID=")+m_Lvl3TechID[i];
		m_pRs2 = theApp.m_pConnect->Execute(_bstr_t(sql2), NULL, adCmdText);

		vector<CString> m_ValComboStr;  //���ڴ洢����combo�ַ�
		vector<CString> vTemp;          //��ʱ�洢ĳһָ���Ӧ��������Ϣ
		while(!m_pRs2->adoEOF)
		{
			CString strValInfo=(CString)(m_pRs2->GetCollect("TechEvalIndexValInfo"));
			CString strVal=(CString)(m_pRs2->GetCollect("TechDeductVal"));
			m_ValComboStr.push_back(strValInfo);   //����combo��ʼ��

			CString str=strValInfo+CString(":")+strVal;//Ϊ��������άvector������������ʾ
			vTemp.push_back(str);

			m_pRs2->MoveNext();
		}

		m_IndexValInfo.push_back(vTemp);//�洢����ָ���������Ϣ
		vector<CString>().swap(vTemp);//�ͷ�vector

        //ÿ��list��Ϣ
		m_OneItem.nItem=strItem;
		m_OneItem.m_Classify=strClassify;
		m_OneItem.m_TechEvalIndex=strTechNam;
		m_OneItem.m_ValComboStr=m_ValComboStr;

		vector<CString>().swap(m_ValComboStr);//�ͷ�vector
		nItem++;
		
		m_ListCtrlItem.push_back(m_OneItem);//���δ���list��ÿ����Ϣ
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
	}
}



LRESULT CProductStep1Dlg::OnSetIndexVal(WPARAM wParam,LPARAM lParam)
{
	//��Ӧ��ֵ������
	//CString strIndexNam=m_TechValList.GetItemText(wParam,2);
	CString strValInfo=m_TechValList.GetItemText(wParam,3);
	///*CString sql = CString("select * from TechEvalIndex where TechEvalIndexNam= '")+strIndexNam+CString("'");*/
	//CString sql_tabnam;	
	//sql_tabnam.Format(_T("select * from TechEvalIndex where TechEvalIndexNam='%s'"),strIndexNam);
	//_bstr_t bstrsql_tabnam=(_bstr_t)sql_tabnam;

	//_RecordsetPtr m_pRecordset_tab;
	//m_pRecordset_tab=theApp.m_pConnect->Execute(bstrsql_tabnam, NULL, adCmdText);
	///*m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);*/
	//CString strIndexID=(CString)(m_pRecordset_tab->GetCollect("TechEvalIndexID"));  //��ѯָ��ID
	//m_pRecordset_tab.Release();

	//CString sql1= CString("select * from EvalIndexVal where TechEvalIndexID= ")+strIndexID+CString("and TechEvalIndexValInfo = '")+strValInfo+CString("'");

	//m_pRecordset_tab= theApp.m_pConnect->Execute(_bstr_t(sql1), NULL, adCmdText);
	//CString strDeductVal=(CString)(m_pRecordset_tab->GetCollect("TechDeductVal"));  //��ѯ��ֵ

	CStringArray strArray;
	//��ȡָ���������
	for (int i=0;i<m_IndexValInfo[wParam].size();++i)
	{
		strArray.Add(m_IndexValInfo[wParam][i].Left(m_IndexValInfo[wParam][i].Find(':')));
	}

	//����ƥ��ѡȡ��Ӧ����
	int j=0;
	for (;j<strArray.GetCount();++j)
	{
		if(strArray[j]==strValInfo) break;
	}
	CString strDeductVal=m_IndexValInfo[wParam][j].Right(m_IndexValInfo[wParam][j].GetLength()-m_IndexValInfo[wParam][j].Find(':')-1);//��ȡ����
	m_TechValList.SetItemText(wParam,4,strDeductVal);                    //���÷�ֵ

	m_ListCtrlItem[wParam].m_ComboStrChoose=strValInfo;                  //�洢��ѡ��������
	m_ListCtrlItem[wParam].m_IndexScore=strDeductVal;                    //�洢��ֵ�����ں���ģ���ۺϷ���

	return 0;
}


//ָ��ƥ������
LRESULT CProductStep1Dlg::OnIndexMatch(WPARAM wParam,LPARAM lParam)
{
	CString strIndexName=m_TechValList.GetItemText(wParam,2);
	//ƥ���1
	if(strIndexName==CString("ת�����ͺ��뵼��ƥ��"))
	{
		CMatchChart1Dlg dlg;
		if(dlg.DoModal()==IDOK)
		{
			if(dlg.isMatch)
			{
				m_TechValList.SetItemText(wParam,3,CString("ƥ��"));
				m_TechValList.SetItemText(wParam,4,CString("0"));

				m_ListCtrlItem[wParam].m_ComboStrChoose=CString("ƥ��");             //�洢��ѡ��������
				m_ListCtrlItem[wParam].m_IndexScore=CString("0");                    //�洢��ֵ�����ں���ģ���ۺϷ���
			}
			else
			{
				m_TechValList.SetItemText(wParam,3,CString("��ƥ��"));
				m_TechValList.SetItemText(wParam,4,CString("-3"));

				m_ListCtrlItem[wParam].m_ComboStrChoose=CString("��ƥ��");             //�洢��ѡ��������
				m_ListCtrlItem[wParam].m_IndexScore=CString("-3");                     //�洢��ֵ�����ں���ģ���ۺϷ���
			}
		}
	}
	//ƥ���2
	else if(strIndexName==CString("TMS���������߾�ƥ��"))
	{
		CMatchChart2Dlg dlg;
		if(dlg.DoModal()==IDOK)
		{
			if(dlg.isMatch)
			{
				m_TechValList.SetItemText(wParam,3,CString("ƥ��"));
				m_TechValList.SetItemText(wParam,4,CString("0"));

				m_ListCtrlItem[wParam].m_ComboStrChoose=CString("ƥ��");              //�洢��ѡ��������
				m_ListCtrlItem[wParam].m_IndexScore=CString("0");                     //�洢��ֵ�����ں���ģ���ۺϷ���
			}
			else
			{
				m_TechValList.SetItemText(wParam,3,CString("��ƥ��"));
				m_TechValList.SetItemText(wParam,4,CString("-3"));

				m_ListCtrlItem[wParam].m_ComboStrChoose=CString("��ƥ��");             //�洢��ѡ��������
				m_ListCtrlItem[wParam].m_IndexScore=CString("-3");                     //�洢��ֵ�����ں���ģ���ۺϷ���
			}
		}
	}
	//ƥ���3
	else if(strIndexName==CString("KT͸����������TMSƥ��"))
	{
		CMatchChart3Dlg dlg;
		if(dlg.DoModal()==IDOK)
		{
			if(dlg.isMatch)
			{
				m_TechValList.SetItemText(wParam,3,CString("ƥ��"));
				m_TechValList.SetItemText(wParam,4,CString("0"));

				m_ListCtrlItem[wParam].m_ComboStrChoose=CString("ƥ��");             //�洢��ѡ��������
				m_ListCtrlItem[wParam].m_IndexScore=CString("0");                     //�洢��ֵ�����ں���ģ���ۺϷ���
			}
			else
			{
				m_TechValList.SetItemText(wParam,3,CString("��ƥ��"));
				m_TechValList.SetItemText(wParam,4,CString("-3"));

				m_ListCtrlItem[wParam].m_ComboStrChoose=CString("��ƥ��");             //�洢��ѡ��������
				m_ListCtrlItem[wParam].m_IndexScore=CString("-3");                     //�洢��ֵ�����ں���ģ���ۺϷ���
			}
		}
	}
	return 0;
}