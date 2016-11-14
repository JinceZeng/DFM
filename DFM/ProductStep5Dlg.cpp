// ProductStep5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep5Dlg.h"
#include "afxdialogex.h"


// CProductStep5Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep5Dlg, CDialogEx)

CProductStep5Dlg::CProductStep5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep5Dlg::IDD, pParent)
{
	m_ListCtrlItem.clear();
	m_Lvl3TechID.clear();
	m_IndexValInfo.clear();
}

CProductStep5Dlg::~CProductStep5Dlg()
{
	vector<CString>().swap(m_Lvl3TechID);
	vector<CTechChartItem>().swap(m_ListCtrlItem);
	vector<vector<CString>>().swap(m_IndexValInfo);
}

void CProductStep5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ECONOMY, m_EconomyList);
}


BEGIN_MESSAGE_MAP(CProductStep5Dlg, CDialogEx)
	ON_MESSAGE(WM_SETINDEXVAL,&CProductStep5Dlg::OnSetIndexVal)
END_MESSAGE_MAP()


// CProductStep5Dlg message handlers
/////////////////////////////////////���ǰҳ(����һҳ����һҳת����ҳ�������)
//����ֻ��һ���ṹ��Ϣ������CListCtl�Ļ�����Ա�����Ϣ�������Լ�����CListCtrl
DWORD CProductStep5Dlg::OnWizardActive()
{
	//������Ϣ���룬��ɳ�ʼ������

	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////ǰ����һҳ
//���Լ��鲢���浱ǰ����,����-1���л�������0�л�
DWORD CProductStep5Dlg::OnWizardNext()
{

	ShowWindow(SW_HIDE);     //��ʱ����д�����ڼӼ����ж�
	return 0;

}

/////////////////////////////////////////ǰ����һҳ
//���Լ�����һ���������ñ���
DWORD CProductStep5Dlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);        //��ʱ����д�����ڼӼ����ж�
	return 0;
}

BOOL CProductStep5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect1;
	int width1;
	m_EconomyList.GetClientRect(&rect1);
	width1=rect1.Width();

	m_EconomyList.InsertColumn(0,CString("���"),LVCFMT_CENTER,width1/10);
	m_EconomyList.InsertColumn(1,CString("���"),LVCFMT_CENTER,width1/10);
	m_EconomyList.InsertColumn(2,CString("������"),LVCFMT_CENTER,width1*3/10);
	m_EconomyList.InsertColumn(3,CString("����������"),LVCFMT_CENTER,width1*2/5);
	m_EconomyList.InsertColumn(4,CString("����ֵ"),LVCFMT_CENTER,width1/10);


	//���ò��ɱ༭��
	vector<int> nNoEdit;
	nNoEdit.push_back(0);               //�����в����Ա༭
	nNoEdit.push_back(1);  
	nNoEdit.push_back(2); 
	nNoEdit.push_back(3); 
	m_EconomyList.SetnNoEditList(nNoEdit);
	vector<int>().swap(nNoEdit);//�ͷ�vector

	vector<int> nComboLis;
	nComboLis.push_back(3);            //����������Ͽ����
    m_EconomyList.SetnComboList(nComboLis);
	vector<int>().swap(nComboLis);//�ͷ�vector
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CProductStep5Dlg::ReadTechChart(CProductInfo& m_ProductInfo)
{
	_RecordsetPtr m_pRs0;
	m_Lvl3TechID.clear();
	int UpID=15;             //��Ѱ����ָ�ָ꣨��IDΪ15�����쾭���ԣ�������
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
}



void CProductStep5Dlg::ShowListCtrl()
{
	_RecordsetPtr m_pRs,m_pRs2;
	m_ListCtrlItem.clear();
	m_IndexValInfo.clear();

	CTechChartItem m_OneItem;//ÿ��list����Ϣ
	int nItem=1;             //���
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
			//CString strIndexInfo=(CString)(m_pRs->GetCollect("TechEvalIndexInfo"));

			//m_IndexInfo.push_back(strIndexInfo);

			vector<CString> m_ValComboStr;  //���ڴ洢����combo�ַ�
			vector<CString> vTemp;          //�����洢������Ͷ�Ӧ��ֵ
			CString sql2 = CString("select * from EvalIndexVal where TechEvalIndexID=")+m_Lvl3TechID[i];
			m_pRs2 = theApp.m_pConnect->Execute(_bstr_t(sql2), NULL, adCmdText);
			while(!m_pRs2->adoEOF)
			{
				CString strValInfo=(CString)(m_pRs2->GetCollect("TechEvalIndexValInfo"));
				CString strVal=(CString)(m_pRs2->GetCollect("TechDeductVal"));
				m_ValComboStr.push_back(strValInfo);   //����combo��ʼ��

				CString str=strValInfo+CString(":")+strVal;//Ϊ��������άvector������������ʾ
				vTemp.push_back(str);

				m_pRs2->MoveNext();
			}

			m_IndexValInfo.push_back(vTemp);
			vector<CString>().swap(vTemp);//�ͷ���ʱvector


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
	SetListItem(m_ListCtrlItem);
}



void CProductStep5Dlg::SetListItem(vector<CTechChartItem>& m_ListCtrlItem)
{
	m_EconomyList.DeleteAllItems();
	for (int i=0;i<m_ListCtrlItem.size();i++)
	{
		m_EconomyList.InsertItem(i,m_ListCtrlItem[i].nItem);
		m_EconomyList.SetItemText(i,1,m_ListCtrlItem[i].m_Classify);
		m_EconomyList.SetItemText(i,2,m_ListCtrlItem[i].m_TechEvalIndex);
		m_EconomyList.SetComboString(m_ListCtrlItem[i].m_ValComboStr);   //��combo�ַ�����listctrl��չ���е�m_strlisCombo����combo��ʼ��
	}
}


LRESULT CProductStep5Dlg::OnSetIndexVal(WPARAM wParam,LPARAM lParam)
{
	//��Ӧ��ֵ������
	CString strValInfo=m_EconomyList.GetItemText(wParam,3);

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
	m_EconomyList.SetItemText(wParam,4,strDeductVal);                    //���÷�ֵ

	m_ListCtrlItem[wParam].m_IndexScore=strDeductVal;                    //�洢��ֵ�����ں���ģ���ۺϷ���

	return 0;
}