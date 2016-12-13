// SetWeighDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "SetWeighDlg.h"
#include "afxdialogex.h"


// CSetWeighDlg dialog

IMPLEMENT_DYNAMIC(CSetWeighDlg, CDialogEx)

CSetWeighDlg::CSetWeighDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetWeighDlg::IDD, pParent)
{
}

CSetWeighDlg::~CSetWeighDlg()
{
	vector<CString>().swap(m_Lvl1TechNam);
	vector<vector<CString>>().swap(m_Lvl2TechNam);
	vector<CString>().swap(m_WeighCompareInfo);
}

void CSetWeighDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SETWEIGH, m_SetWeighList);
}


BEGIN_MESSAGE_MAP(CSetWeighDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetWeighDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetWeighDlg message handlers


BOOL CSetWeighDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//���б�ؼ��ȳ�ʼ��,�����ͷ
	CRect rect1;
	int width1;
	m_SetWeighList.GetClientRect(&rect1);
	width1=rect1.Width();

	m_SetWeighList.InsertColumn(0,CString("���"),LVCFMT_CENTER,width1/4);
	m_SetWeighList.InsertColumn(1,CString("�Ƚ�ָ��1"),LVCFMT_CENTER,width1/4);
	m_SetWeighList.InsertColumn(2,CString("�Ƚ�ָ��2"),LVCFMT_CENTER,width1/4);
	m_SetWeighList.InsertColumn(3,CString("���۽��"),LVCFMT_CENTER,width1/4);


	//���ò��ɱ༭��
	vector<int> nNoEdit;
	nNoEdit.push_back(0);               //�����в����Ա༭
	nNoEdit.push_back(1);  
	nNoEdit.push_back(2);  
	nNoEdit.push_back(3);  
	m_SetWeighList.SetnNoEditList(nNoEdit);
	vector<int>().swap(nNoEdit);        //�ͷ�vector

	vector<int> nComboLis;
	nComboLis.push_back(3);             //����������Ͽ����
	m_SetWeighList.SetnComboList(nComboLis);
	vector<int>().swap(nComboLis);//�ͷ�vector

	SetListItem(m_Lvl1TechNam,m_Lvl2TechNam);//����list��Ŀ

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//��ȡ������Ȩ�ص�һ������ָ��
void CSetWeighDlg::ReadTechChart(CProductInfo &m_ProductInfo)
{
	//��Ѱһ��ָ��
	m_Lvl1TechNam.clear();
	_RecordsetPtr m_pRs;
	vector<CString> m_Lvl1TechID; //��ʱ�洢һ��ָ��ID
	CString strUpID=CString("1"); 
	CString sql = CString("select * from CreateIndexTree where EvalModelID=")+m_ProductInfo.str_EvalType+CString("and TechEvalIndexUpID=")+strUpID;
	m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
	while (!m_pRs->adoEOF)
	{

		CString strID = (CString)(m_pRs->GetCollect("TechEvalIndexID"));
		m_Lvl1TechID.push_back(strID);

		//��ȡָ����
		_RecordsetPtr m_pRs0;
		CString sql0 = CString("select * from TechEvalIndex where TechEvalIndexID=")+strID;
		m_pRs0 = theApp.m_pConnect->Execute(_bstr_t(sql0), NULL, adCmdText);
		CString strTechNam=(CString)(m_pRs0->GetCollect("TechEvalIndexNam"));
        m_Lvl1TechNam.push_back(strTechNam);
		
		m_pRs->MoveNext();

	}

	//��Ѱ����ָ��
	m_Lvl2TechNam.clear();
	_RecordsetPtr m_pRs1;
	vector<CString> vTemp;
	for (int i=0;i<m_Lvl1TechID.size();++i)
	{
		CString sql1 = CString("select * from CreateIndexTree where EvalModelID=")+m_ProductInfo.str_EvalType+CString("and TechEvalIndexUpID=")+m_Lvl1TechID[i];
		m_pRs1 = theApp.m_pConnect->Execute(_bstr_t(sql1), NULL, adCmdText);
		while (!m_pRs1->adoEOF)
		{

			CString strID = (CString)(m_pRs1->GetCollect("TechEvalIndexID"));

			//��ȡָ����
			_RecordsetPtr m_pRs0;
			CString sql0 = CString("select * from TechEvalIndex where TechEvalIndexID=")+strID;
			m_pRs0 = theApp.m_pConnect->Execute(_bstr_t(sql0), NULL, adCmdText);
			CString strTechNam=(CString)(m_pRs0->GetCollect("TechEvalIndexNam"));
			vTemp.push_back(strTechNam);

			m_pRs1->MoveNext();
		}
		m_Lvl2TechNam.push_back(vTemp);
		vector<CString>().swap(vTemp);
		
	}
	vector<CString>().swap(m_Lvl1TechID);
	
}


void CSetWeighDlg::SetListItem(vector<CString>& m_Lvl1TechNam,vector<vector<CString>>& m_Lvl2TechNam)
{
	vector<CString> WeighComboStr;//��ʼ��combostr
	WeighComboStr.push_back(CString("ͬ����Ҫ"));
	WeighComboStr.push_back(CString("����Ҫ"));
	WeighComboStr.push_back(CString("������Ҫ"));
	WeighComboStr.push_back(CString("ǿ����Ҫ"));
	WeighComboStr.push_back(CString("������Ҫ"));
	WeighComboStr.push_back(CString("�Բ���Ҫ"));
	WeighComboStr.push_back(CString("���Բ���Ҫ"));
	WeighComboStr.push_back(CString("ǿ�Ҳ���Ҫ"));
	WeighComboStr.push_back(CString("���˲���Ҫ"));

	vector<CString> WeighInit; //��ʼ��list��Ȩ��ֵ
	WeighInit.push_back(CString("����Ҫ"));
	WeighInit.push_back(CString("�Բ���Ҫ"));
	WeighInit.push_back(CString("�Բ���Ҫ"));
	WeighInit.push_back(CString("�Բ���Ҫ"));
	WeighInit.push_back(CString("�Բ���Ҫ"));
	WeighInit.push_back(CString("����Ҫ"));
	WeighInit.push_back(CString("����Ҫ"));
	WeighInit.push_back(CString("ͬ����Ҫ"));
	WeighInit.push_back(CString("ͬ����Ҫ"));
	WeighInit.push_back(CString("�Բ���Ҫ"));
	WeighInit.push_back(CString("�Բ���Ҫ"));





	int n=0;//��¼list��Ŀ
	for (int i=0;i<m_Lvl1TechNam.size();++i)//����һ��ָ��Ȩ������
	{
		
		for(int j=i;j<m_Lvl1TechNam.size()-1;++j)
		{
			CString strItem1;
			strItem1.Format(CString("%d"),n+1);
			m_SetWeighList.InsertItem(n,strItem1);
			m_SetWeighList.SetItemText(n,1,m_Lvl1TechNam[i]);
			m_SetWeighList.SetItemText(n,2,m_Lvl1TechNam[j+1]);
			m_SetWeighList.SetItemText(n,3,WeighInit[n]);
			m_SetWeighList.SetComboString(WeighComboStr);
			++n;
		}
		for (int k=0;k<m_Lvl2TechNam[i].size();++k)
		{
			for(int l=k;l<m_Lvl2TechNam[i].size()-1;++l)
			{
				CString strItem2;
				strItem2.Format(CString("%d"),n+1);
				m_SetWeighList.InsertItem(n,strItem2);
				m_SetWeighList.SetItemText(n,1,m_Lvl2TechNam[i][k]);
				m_SetWeighList.SetItemText(n,2,m_Lvl2TechNam[i][l+1]);
				m_SetWeighList.SetItemText(n,3,WeighInit[n]);
				m_SetWeighList.SetComboString(WeighComboStr);
				++n;
			}
		}
     }
	vector<CString>().swap(WeighComboStr);
	vector<CString>().swap(WeighInit);

}

void CSetWeighDlg::OnBnClickedOk()
{
	if (m_SetWeighList.m_bEditing==TRUE)
	{
		AfxMessageBox(CString("����:�б�ؼ����ڱ༭״̬"));
		return;
	}
	m_WeighCompareInfo.clear(); //����ʱ���
	// TODO: Add your control notification handler code here
	for (int i=0;i<m_SetWeighList.GetItemCount();++i)
	{
		CString str=m_SetWeighList.GetItemText(i,3);
		if(str==CString(""))
		{
			AfxMessageBox(CString("������δ���"));
			return;
		}
		else m_WeighCompareInfo.push_back(str);
	}
	ConstructCompareMat(m_WeighCompareInfo);
	//double d1=0.0,d2=0.0;
	//d1=m_dA1.sum();             //�˴���ͺ��޷���ֵ
	//d2=m_dA2.sum();
	//TRACE(_T("Item=%f\n"), d1);
	//TRACE(_T("Item=%f\n"), d2);

	int nSum=0;
	for (int i=0;i<m_vnCoherence.size();++i)
	{
		nSum+=m_vnCoherence[i];
	}
	if(nSum!=m_vnCoherence.size())//һ���Լ�ⲻͨ��
	{
		AfxMessageBox(CString("һ���Լ��δͨ���������±Ƚ�ָ�꣡"));
		return;
	}

	CDialogEx::OnOK();
}



void CSetWeighDlg::ConstructCompareMat(vector<CString>& m_WeighCompareInfo)
{
	MatrixXd M_S1,M_S2;

	vector<double> m_WeighVal;
	double WeighVal;
	for (int i=0;i<m_WeighCompareInfo.size();++i)
	{
		if(m_WeighCompareInfo[i]==CString("ͬ����Ҫ"))
			WeighVal=1;
		else if(m_WeighCompareInfo[i]==CString("����Ҫ"))
			WeighVal=3;
		else if(m_WeighCompareInfo[i]==CString("������Ҫ"))
			WeighVal=5;
		else if(m_WeighCompareInfo[i]==CString("ǿ����Ҫ"))
			WeighVal=7;
		else if(m_WeighCompareInfo[i]==CString("������Ҫ"))
			WeighVal=9;
		else if(m_WeighCompareInfo[i]==CString("�Բ���Ҫ"))
			WeighVal=1.0/3;
		else if(m_WeighCompareInfo[i]==CString("���Բ���Ҫ"))
			WeighVal=1.0/5;
		else if(m_WeighCompareInfo[i]==CString("ǿ�Ҳ���Ҫ"))
			WeighVal=1.0/7;
		else /*if(m_WeighCompareInfo[i]==CString("���˲���Ҫ"))*/
			WeighVal=1.0/9;
		m_WeighVal.push_back(WeighVal);
	}
	int n1=m_Lvl1TechNam.size(),n2=m_Lvl2TechNam[0].size();
	int nn1=n1*(n1-1)/2,nn2=n2*(n2-1)/2;
	M_S1.resize(n1,n1);
	M_S2.resize(n2,n2);
	for (int i=0;i<n1;++i)   //һ��ָ��Ȩ���жϾ���ֵ
	{
		for (int j=0;j<n1;++j)
		{
			if(i==j)  M_S1(i,j)=1;
			else if(i<j) M_S1(i,j)=m_WeighVal[i];
			else M_S1(i,j)=1/M_S1(j,i);
		}
	}


	for (int i=0;i<n2;++i)  //����ָ��Ȩ���жϾ���ֵ
	{
		for (int j=0;j<n2;++j)
		{
			if(i==j)  M_S2(i,j)=1;
			else if(i<j) M_S2(i,j)=m_WeighVal[nn1++];
			else M_S2(i,j)=1/M_S2(j,i);
		}
	}

	ComputeWeigh(M_S1);
	ComputeWeigh(M_S2);

	m_dA1=m_dA[0];
	m_dA2=m_dA[1];
}




void CSetWeighDlg::ComputeWeigh(MatrixXd& M_S)
{
	EigenSolver<MatrixXd> es(M_S);
	complex<double> cdMax=0.0;
	int itemp=0;
	for (int i=0;i<es.eigenvalues().size();++i)
	{
		if(norm(es.eigenvalues()[i])>norm(cdMax)) 
		{
			cdMax=es.eigenvalues()[i];
			itemp=i;
		}
	}
	VectorXcd cdV = es.eigenvectors().col(itemp);

	//�������ֵΪʵ�����ɰ�����������Ϊʵ������
	double dMax=cdMax.real();
	//m_vdMaxA.push_back(dMax);
	VectorXd dV(cdV.size());
	for (int i=0;i<cdV.size();++i)
	{
		dV[i]=cdV[i].real();
	}

	//�ж�һ��m_dA1
	int n=dV.size();
	double dRI[15]={0,0,0.52,0.89,1.12,1.26,1.36,1.41,1.46,1.49,1.52,1.54,1.56,1.58,1.59};
	double dCI=(dMax-n)/(n-1);
	double dCR=dCI/dRI[n-1];
	if(dCR<0.1||n<3)
	{
		//VectorXd tempdV(m_dA1.size());//release��dV���¸�ֵ��������ڴ�������⣬����ȡ��ʱ�����ݴ�
		dV/=dV.sum();
		m_vnCoherence.push_back(1);
	}
	else
		m_vnCoherence.push_back(0);
	m_dA.push_back(dV);
}

