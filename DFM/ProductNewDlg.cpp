// ProductNewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductNewDlg.h"
#include "afxdialogex.h"


// CProductNewDlg dialog

IMPLEMENT_DYNAMIC(CProductNewDlg, CDialogEx)

CProductNewDlg::CProductNewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductNewDlg::IDD, pParent)
{
	m_pPageList.clear();            //��¼���ӶԻ���
	m_nCurrentPage=0;               //��ǰ��ʾҳ
	m_rectPanel=CRect(0,0,0,0);     //�ӶԻ���İ�ΧȦ
	bInfoWrited=FALSE;

}

CProductNewDlg::~CProductNewDlg()
{
	int n=m_pPageList.size();

	for(int i=0;i<n;i++)
	{
		delete m_pPageList[i];      //�ͷ��ڴ棬�������ͷ��ڴ���ΪҪ������Ϣ����ȥ
	}

	m_pPageList.clear();            //��¼���ӶԻ���
}

void CProductNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductNewDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_EVALPRE, &CProductNewDlg::OnBnClickedEvalpre)
	ON_BN_CLICKED(IDC_EVALNEXT, &CProductNewDlg::OnBnClickedEvalnext)
	ON_BN_CLICKED(IDC_EVALIN, &CProductNewDlg::OnBnClickedEvalin)
END_MESSAGE_MAP()


// CProductNewDlg message handlers


BOOL CProductNewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	//��ȡ�ӶԻ���İ��ݾ���
	GetDlgItem(IDC_STATIC_PLANE)->GetWindowRect(&m_rectPanel);
	ScreenToClient(&m_rectPanel);

	//�����ĸ�����ҳ

	//////////////////////////////////////////////ҳ��0
	CProductStep0Dlg *pStep0=new CProductStep0Dlg();
	if(pStep0==NULL)
	{
		MessageBox(_T("ҳ��0����ʧ��"));
		AfxAbort();
	}

	pStep0->Create(IDD_PRODUCTSTEP0_DLG,this);

	if(bInfoWrited)//������ݿ����Ѿ�д�룬ֱ�ӽ��г�ʼ��
	{
		_RecordsetPtr m_pRs;
		CString sql = CString("select * from ProductInfo where ProductID=") + strProductID ;
		m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		CString str1 = (CString)m_pRs->GetCollect("ProductNam");
		CString str2 = (CString)m_pRs->GetCollect("ProductNum");
		CString str3 = (CString)(m_pRs->GetCollect("ProductSub")); 

		CString str44 =  m_pRs->GetCollect("EvalModelID");
		int int4 = _ttoi(str44)-1; //combo���㿪ʼ-1

		CString str5 = (CString)(m_pRs->GetCollect("EvalTypeIntro")); 
	    pStep0->m_ProductName=str1;
	    pStep0->m_ProductNum=str2;
		pStep0->m_ProductSub=str3;
		pStep0->str_EvalType=str44;
		pStep0->m_EvalTypeVal=int4;
		pStep0->m_TypeInfo=str5;

		pStep0->SaveProductInfo();//�����Ʒ����
		::SendMessage(pStep0->m_hWnd,WM_UPDATEDATA,FALSE,FALSE);//���¿ؼ���Ϣ
	}
	//��ʾ
	pStep0->MoveWindow(m_rectPanel);
	pStep0->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep0);

	//////////////////////////////////////////////ҳ��1
	CProductStep1Dlg *pStep1=new CProductStep1Dlg();
	if(pStep1==NULL)
	{
		MessageBox(_T("ҳ��1����ʧ��"));
		AfxAbort();
	}

	pStep1->Create(IDD_PRODUCTSTEP1_DLG,this);

	//��ʾ
	pStep1->MoveWindow(m_rectPanel);
	pStep1->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep1);

	///////////////////////////////////////////ҳ��2
	CProductStep2Dlg *pStep2=new CProductStep2Dlg();
	if(pStep2==NULL)
	{
		MessageBox(_T("ҳ��2����ʧ��"));
		AfxAbort();
	}

	pStep2->Create(IDD_PRODUCTSTEP2_DLG,this);

	//��ʾ
	pStep2->MoveWindow(m_rectPanel);
	pStep2->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep2);

	////////////////////////////////////////ҳ��3
	CProductStep3Dlg *pStep3=new CProductStep3Dlg();
	if(pStep3==NULL)
	{
		MessageBox(_T("ҳ��3����ʧ��"));
		AfxAbort();
	}

	pStep3->Create(IDD_PRODUCTSTEP3_DLG,this);

	//��ʾ
	pStep3->MoveWindow(m_rectPanel);
	pStep3->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep3);

	///////////////////////////////////////�����Ϣûд����ʾ��һҳ������ʾ�ڶ�ҳ
	/*if(!bInfoWrited)*/ ShowPage(0);
	/*else             {ShowPage(1);m_nCurrentPage+=1;}*/
	UpdateWindow();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}










HBRUSH CProductNewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_STATIC)  
	{
		//if(pWnd->GetDlgCtrlID()!=IDC_STATIC_PLANE)
		//	return (HBRUSH)::GetStockObject(NULL_BRUSH);   //����͸����ˢ
		CFont font;
		font.CreatePointFont(125,_T("����"));    //�������屳��
		pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CProductNewDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	int n=m_pPageList.size();

	for(int i=0;i<n;i++)
	{
		m_pPageList[i]->DestroyWindow();  //���ٴ�����Դ
	}
}


void CProductNewDlg::OnBnClickedEvalpre()
{
	// TODO: Add your control notification handler code here
	int nPrePage=m_nCurrentPage-1;      //ȷ��ǰһҳ������λ��
	ShowPage(nPrePage);
	UpdateWindow();
}


void CProductNewDlg::OnBnClickedEvalnext()
{
	// TODO: Add your control notification handler code here
	int nNextPage=m_nCurrentPage+1;
	ShowPage(nNextPage);
	UpdateWindow();
}


void CProductNewDlg::OnBnClickedEvalin()
{
	// TODO: Add your control notification handler code here
}


//����ҳ��������ð�ť״̬
void CProductNewDlg::SetWizButton(UINT nPos)
{
	GetDlgItem(IDC_EVALPRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EVALNEXT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EVALIN)->EnableWindow(TRUE);

	switch(nPos)
	{
	case 0: //��һ��(��һ��ʧЧ)
		GetDlgItem(IDC_EVALPRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 1: //�м䲽
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 2://�м䲽
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 3: //���һ��
		GetDlgItem(IDC_EVALNEXT)->EnableWindow(FALSE);
		break;
	}
}



//��ʾnPosҳ��
void CProductNewDlg::ShowPage(UINT nPos) 
{
	//��ʾ��һҳ,���ص�ǰҳ��������һҳ
	if(nPos==m_nCurrentPage)
	{
		((CProductStep0Dlg*)m_pPageList[0])->OnWizardActive();
		SetWizButton(0);
		SetTextShow(0);
	}
	else if(nPos>(UINT)m_nCurrentPage)
	{
		//ִ�е�����һ���Ĳ���,
		switch(m_nCurrentPage)
		{
		case 0:
			if(((CProductStep0Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)  //���浱ǰ�������ɹ�������ǰҳ
				return;
			//((CProductStep1Dlg*)m_pPageList[nPos])->m_ProductInfo=((CProductStep0Dlg*)m_pPageList[m_nCurrentPage])->m_ProductInfo;
			((CProductStep1Dlg*)m_pPageList[nPos])->m_TechValList.DeleteAllItems();
			((CProductStep1Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[m_nCurrentPage])->m_ProductInfo);
			((CProductStep1Dlg*)m_pPageList[nPos])->ShowListCtrl(((CProductStep1Dlg*)m_pPageList[nPos])->m_Lvl4TechID);
			((CProductStep1Dlg*)m_pPageList[nPos])->OnWizardActive();

			break;
		case 1:
			if(((CProductStep1Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			//((CDlgStep2*)m_pPageList[nPos])->GetInfoFromPrevPage(((CDlgStep1*)m_pPageList[m_nCurrentPage])->m_AsistStore);  //������Ϣ
			((CProductStep2Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 2:
			if(((CProductStep2Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			//((CDlgStep3*)m_pPageList[nPos])->GetExternInfo(((CDlgStep2*)m_pPageList[m_nCurrentPage])->m_NodNamList);   //���ݽڵ���Ϣ
			((CProductStep3Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		default:
			AfxMessageBox(_T("û����һҳ,��һ����������"));
			break;
		}

		m_nCurrentPage=nPos;
		SetWizButton(nPos);
		SetTextShow(nPos);
	}
	else
	{
		//ִ����һ�����������ص�ǰҳ������ǰһҳ,��ǰ���ô�����Ϣ
		switch(m_nCurrentPage)
		{
		case 1:
			if(((CProductStep1Dlg*)m_pPageList[m_nCurrentPage])->OnWizardPrevious()==-1)
				return;
			((CProductStep0Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 2:
			if(((CProductStep2Dlg*)m_pPageList[m_nCurrentPage])->OnWizardPrevious()==-1)
				return;
			((CProductStep1Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 3:
			if(((CProductStep3Dlg*)m_pPageList[m_nCurrentPage])->OnWizardPrevious()==-1)
				return;
			((CProductStep2Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		default:
			AfxMessageBox(_T("û����һҳ,��һ����������"));
			break;
		}
		m_nCurrentPage=nPos;
		SetWizButton(nPos);
		SetTextShow(nPos);
	}

}

//�����ı�״̬��ʾ
void CProductNewDlg::SetTextShow(UINT nPos)
{
	CStatic *cs1,*cs2;
	cs1=new CStatic();
	cs2=new CStatic();
	switch(nPos)
	{
	case 0:
		cs1->Create(CString("������������"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,30,130,50),this);
		cs2->Create(CString("��Ʒ��Ϣ¼��"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,150,130,170),this);
		break;
	case 1:
		//cs2->Invalidate();
		cs2->Create(CString("���������ֱ�"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,150,130,170),this);
		break;
	case 2:
		//cs2->Invalidate();
		cs2->Create(CString("���ճ���ȱ�"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,150,130,170),this);
		break;
	case 3:
		//cs2->Invalidate();
		cs2->Create(CString("������Ӧ�Ա�"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,150,130,170),this);
	}
	//delete cs1,cs2;
}