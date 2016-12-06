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

	//m_pPageList.clear();            //��¼���ӶԻ���
	vector<CDialogEx*>().swap(m_pPageList);//�����������С����������

	//delete m_csCaption;             //�ͷ�cstaticָ���ڴ�
	vector<CString>().swap(m_ItemVal);
	vector<CString>().swap(m_Lvl1TechNam);
	vector<vector<CString>>().swap(m_Lvl2TechNam);
	vector<CLowValItem>().swap(m_LowValItem);
	vector<CIndexValItem>().swap(m_IndexVal);

}

void CProductNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CHART0, m_btnChart0);
	DDX_Control(pDX, IDC_BUTTON_CHART1, m_btnChart1);
	DDX_Control(pDX, IDC_BUTTON_CHART2, m_btnChart2);
	DDX_Control(pDX, IDC_BUTTON_CHART3, m_btnChart3);
	DDX_Control(pDX, IDC_BUTTON_CHART4, m_btnChart4);
	DDX_Control(pDX, IDC_BUTTON_CHART5, m_btnChart5);
	DDX_Control(pDX, IDC_BUTTON_CHART6, m_btnChart6);
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

	//����ĸ�����ҳ

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

	////////////////////////////////////////ҳ��4
	CProductStep4Dlg *pStep4=new CProductStep4Dlg();
	if(pStep4==NULL)
	{
		MessageBox(_T("ҳ��4����ʧ��"));
		AfxAbort();
	}

	pStep4->Create(IDD_PRODUCTSTEP4_DLG,this);

	//��ʾ
	pStep4->MoveWindow(m_rectPanel);
	pStep4->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep4);

	////////////////////////////////////////ҳ��5
	CProductStep5Dlg *pStep5=new CProductStep5Dlg();
	if(pStep5==NULL)
	{
		MessageBox(_T("ҳ��5����ʧ��"));
		AfxAbort();
	}

	pStep5->Create(IDD_PRODUCTSTEP5_DLG,this);

	//��ʾ
	pStep5->MoveWindow(m_rectPanel);
	pStep5->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep5);

	////////////////////////////////////////ҳ��6
	CProductStep6Dlg *pStep6=new CProductStep6Dlg();
	if(pStep6==NULL)
	{
		MessageBox(_T("ҳ��6����ʧ��"));
		AfxAbort();
	}

	pStep6->Create(IDD_PRODUCTSTEP6_DLG,this);

	//��ʾ
	pStep6->MoveWindow(m_rectPanel);
	pStep6->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep6);


	///////////////////////////////////////��ʾ��һҳ
	ShowPage(0);
	UpdateWindow();



	//////////////////////////////////////״̬��ʾ��ʼ��
	//m_csCaption=new CStatic();
	m_csCaption.Create(CString("������������"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,30,130,50),this);

	short	shBtnColor = 30;
	m_btnChart0.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnChart1.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnChart2.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnChart3.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnChart4.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnChart5.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnChart6.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);

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
		pDC->SetTextColor(RGB(0,0,0));
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
	if(((CProductStep6Dlg*)m_pPageList[6])->m_ListCtrlItem.size()==0)
	{
		AfxMessageBox(CString("�����ʹ�ù���"));
		return;
	}
	else
	{
		((CProductStep6Dlg*)m_pPageList[6])->SaveLowValItem();//�ȱ����6�ͷ���

		CSetWeighDlg dlg;
		dlg.ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);//�ȶ�ȡ����Ϣ
		if(dlg.DoModal()==IDOK)
		{
			GetIndexVal(dlg.m_dA1,dlg.m_dA2);
			m_Lvl1TechNam=dlg.m_Lvl1TechNam;     //���ݸ���ָ����
			m_Lvl2TechNam=dlg.m_Lvl2TechNam;

			//������
			SaveResultInfo(m_LowValItem,m_IndexVal);    //��m_LowValItem��m_IndexVal��ֵ
			CProductOutDlg dlg1;
			dlg1.GetItemInfo(SetResultVal(m_ItemVal));
			dlg1.GetResultInfo(m_LowValItem,m_IndexVal);
			dlg1.DoModal();
		}
	}


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
	case 3://�м䲽
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 4://�м䲽
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 5://�м䲽
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 6: //���һ��
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
			//((CProductStep1Dlg*)m_pPageList[nPos])->m_TechValList.DeleteAllItems();
			((CProductStep1Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);
			((CProductStep1Dlg*)m_pPageList[nPos])->ShowListCtrl();

			((CProductStep1Dlg*)m_pPageList[nPos])->m_LowValItem.clear();  //��һ��ʱ�������һҳ��ĵͷ���Ϣ����
			((CProductStep1Dlg*)m_pPageList[nPos])->m_LowValItemNum=0;

			((CProductStep1Dlg*)m_pPageList[nPos])->OnWizardActive();

			break;
		case 1:
			if(((CProductStep1Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			((CProductStep2Dlg*)m_pPageList[nPos])->m_MatInfoList.DeleteAllItems();
			((CProductStep2Dlg*)m_pPageList[nPos])->m_LowValItem.clear();  //��һ��ʱ�������һҳ��ĵͷ���Ϣ����
			((CProductStep2Dlg*)m_pPageList[nPos])->m_LowValItemNum=0;

			((CProductStep2Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 2:
			if(((CProductStep2Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			//((CProductStep3Dlg*)m_pPageList[nPos])->m_ImpactVibValList.DeleteAllItems();
			((CProductStep3Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);
			((CProductStep3Dlg*)m_pPageList[nPos])->ShowListCtrl();

			((CProductStep3Dlg*)m_pPageList[nPos])->m_LowValItem.clear();  //��һ��ʱ�������һҳ��ĵͷ���Ϣ����
			((CProductStep3Dlg*)m_pPageList[nPos])->m_LowValItemNum=0;
			((CProductStep3Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 3:
			if(((CProductStep3Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			//((CProductStep4Dlg*)m_pPageList[nPos])->m_ThreeProValList.DeleteAllItems();
			((CProductStep4Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);
			((CProductStep4Dlg*)m_pPageList[nPos])->ShowListCtrl();

			((CProductStep4Dlg*)m_pPageList[nPos])->m_LowValItem.clear();  //��һ��ʱ�������һҳ��ĵͷ���Ϣ����
			((CProductStep4Dlg*)m_pPageList[nPos])->m_LowValItemNum=0;
			((CProductStep4Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 4:
			if(((CProductStep4Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			//((CProductStep5Dlg*)m_pPageList[nPos])->m_EconomyList.DeleteAllItems();
			((CProductStep5Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);
			((CProductStep5Dlg*)m_pPageList[nPos])->ShowListCtrl();

			((CProductStep5Dlg*)m_pPageList[nPos])->m_LowValItem.clear();  //��һ��ʱ�������һҳ��ĵͷ���Ϣ����
			((CProductStep5Dlg*)m_pPageList[nPos])->m_LowValItemNum=0;
			((CProductStep5Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 5:
			if(((CProductStep5Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			((CProductStep6Dlg*)m_pPageList[nPos])->m_TechMaturyList.DeleteAllItems();
			((CProductStep6Dlg*)m_pPageList[nPos])->ReadTechChart();

			((CProductStep6Dlg*)m_pPageList[nPos])->m_ListCtrlItem.clear();
			((CProductStep6Dlg*)m_pPageList[nPos])->m_LowValItem.clear();  //��һ��ʱ�������һҳ��ĵͷ���Ϣ����
			((CProductStep6Dlg*)m_pPageList[nPos])->m_LowValItemNum=0;


			((CProductStep6Dlg*)m_pPageList[nPos])->OnWizardActive();
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
		case 4:
			if(((CProductStep4Dlg*)m_pPageList[m_nCurrentPage])->OnWizardPrevious()==-1)
				return;
			((CProductStep3Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 5:
			if(((CProductStep5Dlg*)m_pPageList[m_nCurrentPage])->OnWizardPrevious()==-1)
				return;
			((CProductStep4Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 6:
			if(((CProductStep6Dlg*)m_pPageList[m_nCurrentPage])->OnWizardPrevious()==-1)
				return;
			((CProductStep5Dlg*)m_pPageList[nPos])->OnWizardActive();
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

//�����ı�״̬��ʾ�仯
void CProductNewDlg::SetTextShow(UINT nPos)
{

	switch(nPos)
	{
	case 0:
		m_btnChart0.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 0, 0));
		m_btnChart1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart3.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart4.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart5.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart6.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		break;
	case 1:
		m_btnChart0.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 0, 0));
		m_btnChart2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart3.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart4.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart5.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart6.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		break;
	case 2:
		m_btnChart0.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 0, 0));
		m_btnChart3.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart4.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart5.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart6.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		break;
	case 3:
		m_btnChart0.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart3.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 0, 0));
		m_btnChart4.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart5.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart6.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		break;
	case 4:
		m_btnChart0.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart3.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart4.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 0, 0));
		m_btnChart5.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart6.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		break;
	case 5:
		m_btnChart0.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart3.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart4.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart5.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 0, 0));
		m_btnChart6.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		break;
	case 6:
		m_btnChart0.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart3.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart4.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart5.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart6.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 0, 0));
		break;
	default:
		m_btnChart0.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart3.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart4.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart5.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		m_btnChart6.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
		break;
	}
}




///////////////////////////////////////////////////////////////////ģ����η������������
void CProductNewDlg::GetIndexVal(VectorXd& dA1,VectorXd& dA2)
{
	/////////////�����ֱ��л�ȡ��cstring����ֵת��Ϊdouble
	int n1,n2,n3,n4,n5,n6;
	n1=((CProductStep1Dlg*)m_pPageList[1])->m_ListCtrlItem.size();
	n2=((CProductStep2Dlg*)m_pPageList[2])->m_ListCtrlItem.size();
	n3=((CProductStep3Dlg*)m_pPageList[3])->m_ListCtrlItem.size();
	n4=((CProductStep4Dlg*)m_pPageList[4])->m_ListCtrlItem.size();
	n5=((CProductStep5Dlg*)m_pPageList[5])->m_ListCtrlItem.size();
	n6=((CProductStep6Dlg*)m_pPageList[6])->m_ListCtrlItem.size();
	vector<double> TechIndexVal,MatInfoVal,ImpactVibVal,ThreeProVal,EconomyVal,TechMaturyVal;

	for(int i=0;i<n1;++i)
	{
		TechIndexVal.push_back(_ttol(((CProductStep1Dlg*)m_pPageList[1])->m_ListCtrlItem[i].m_IndexScore));     //cstringתdouble

	}
	for(int i=0;i<n2;++i)
	{
		MatInfoVal.push_back(_ttol(((CProductStep2Dlg*)m_pPageList[2])->m_ListCtrlItem[i].m_MatScore));     //cstringתdouble

	}
	for(int i=0;i<n3;++i)
	{
		ImpactVibVal.push_back(_ttol(((CProductStep3Dlg*)m_pPageList[3])->m_ListCtrlItem[i].m_IndexScore));     //cstringתdouble

	}
	for(int i=0;i<n4;++i)
	{
		ThreeProVal.push_back(_ttol(((CProductStep4Dlg*)m_pPageList[4])->m_ListCtrlItem[i].m_IndexScore));     //cstringתdouble

	}
	for(int i=0;i<n5;++i)
	{
		EconomyVal.push_back(_ttol(((CProductStep5Dlg*)m_pPageList[5])->m_ListCtrlItem[i].m_IndexScore));     //cstringתdouble

	}
	for(int i=0;i<n6;++i)
	{
		TechMaturyVal.push_back(_ttol(((CProductStep6Dlg*)m_pPageList[6])->m_ListCtrlItem[i].m_TechMaturyVal));     //cstringתdouble

	}
	double c1,c2,c3,c4,c5,c6;
	c1=MinVal(TechMaturyVal);    //�����ֱ�����֣�����ѡ����Ϳ۷���������
	c2=3+MinVal(TechIndexVal);
	c3=3+MinVal(ThreeProVal);
	c4=3+MinVal(ImpactVibVal);
	c5=3+MinVal(MatInfoVal);
	c6=3+MinVal(EconomyVal);

	vector<double>().swap(TechMaturyVal);//�ͷ�vector
	vector<double>().swap(TechIndexVal);
	vector<double>().swap(ThreeProVal);
	vector<double>().swap(ImpactVibVal);
	vector<double>().swap(MatInfoVal);
	vector<double>().swap(EconomyVal);


	//�������ָ������
	VectorXd vTemp1(6);
	vTemp1<<c1,c2,c3,c4,c5,c6;
	m_dC2=vTemp1;

	VectorXd dC2(5);      //���ڹ���ģ������
	dC2<<c1,c2,c3,c4,c5;

	///////////////////////////////////////ͨ�����ְ�0-1�͵�������������ģ������
	MatrixXd dR2(dC2.size(),4); //���ۼ���Ϊ�ĸ�����0��1��2��3
	VectorXd dV(4);
	dV<<0,1,2,3;
	for(int i=0;i<dR2.rows();++i)
	{
		for (int j=0;j<dR2.cols();++j)
		{
			if(dC2[i]==dV[j]) dR2(i,j)=1;
			else dR2(i,j)=0;
		}
	}
	m_dB2=dA2.transpose()*dR2;//����ָ������ۼ���������
	double cc1=m_dB2*dV;//����ָ�����������
	double cc2=c6;      //��Ϊ����ָ��ֻ��һ����ָ�꣬������ֱ��Ϊ��ָ������

	//����һ��ָ������
	VectorXd vTemp2(2);
	vTemp2<<cc1,cc2;
	m_dC1=vTemp2;


	//�����ϼ�ģ������
	MatrixXd dR1(2,4);
	for (int i=0;i<dR1.rows();++i)
	{
		for (int j=0;j<dR1.cols();++j)
		{
			if(i==0) dR1(i,j)=m_dB2[j];
			else if(cc2==dV[j]) dR1(i,j)=1;
			else dR1(i,j)=0;
		}
	}
	m_dB1=dA1.transpose()*dR1; //������������ۼ���������
	m_W=m_dB1*dV;  //��������ֵ
}



double CProductNewDlg::MinVal(vector<double>& IndexVal)
{
	double dMin=3.0;
	for (int i=0;i<IndexVal.size();++i)
	{
		if (IndexVal[i]<dMin)
			dMin=IndexVal[i];
		
	}
	return dMin;
}



/////////////////////////���������
vector<CString>& CProductNewDlg::SetResultVal(vector<CString>& m_ItemVal)
{
	//�������տ�������
	m_ItemVal.clear();

	CString strEvalResult;
	if (m_W>=0&&m_W<1.5)
		strEvalResult=CString("�������Բ�");
	else if(m_W>=1.5&&m_W<2.5)
		strEvalResult=CString("��������һ��");
	else 
		strEvalResult=CString("�������Ժ�");

	m_ItemVal.push_back(((CProductStep0Dlg*)m_pPageList[0])->m_ProductName);  //��Ʒ����
	m_ItemVal.push_back(((CProductStep0Dlg*)m_pPageList[0])->m_ProductNum);   //��Ʒ���
	m_ItemVal.push_back(strEvalResult);   //�ۺ����۽��
	m_ItemVal.push_back(CString("˫����ʾ��ϸ��Ϣ"));   //�ͷ���Ľ���ʾ
	m_ItemVal.push_back(CString("˫����ʾ��ϸ��Ϣ"));   //ָ��÷�ֵ��ʾ

	return m_ItemVal;
}




//��m_LowValItem��m_IndexVal��ֵ,���ڽ����ʾ
void CProductNewDlg::SaveResultInfo(vector<CLowValItem>& m_LowValItem,vector<CIndexValItem>& m_IndexVal)
{
	//�ۺϱ���ͷ���
	m_LowValItem.clear();
	m_IndexVal.clear();

	int nLowValItemNum=1; 
	for (int i=0;i<((CProductStep1Dlg*)m_pPageList[1])->m_LowValItem.size();++i)
	{
		CString str;
		str.Format(CString("%d"),nLowValItemNum);
		CLowValItem OneItem;
		OneItem=((CProductStep1Dlg*)m_pPageList[1])->m_LowValItem[i];
		OneItem.m_Item=str;  //������¸�ֵ
		m_LowValItem.push_back(OneItem);
		++nLowValItemNum;
	}
	for (int i=0;i<((CProductStep2Dlg*)m_pPageList[2])->m_LowValItem.size();++i)
	{
		CString str;
		str.Format(CString("%d"),nLowValItemNum);
		CLowValItem OneItem;
		OneItem=((CProductStep2Dlg*)m_pPageList[2])->m_LowValItem[i];
		OneItem.m_Item=str;  //������¸�ֵ
		m_LowValItem.push_back(OneItem);
		++nLowValItemNum;
	}
	for (int i=0;i<((CProductStep3Dlg*)m_pPageList[3])->m_LowValItem.size();++i)
	{
		CString str;
		str.Format(CString("%d"),nLowValItemNum);
		CLowValItem OneItem;
		OneItem=((CProductStep3Dlg*)m_pPageList[3])->m_LowValItem[i];
		OneItem.m_Item=str;  //������¸�ֵ
		m_LowValItem.push_back(OneItem);
		++nLowValItemNum;
	}
	for (int i=0;i<((CProductStep4Dlg*)m_pPageList[4])->m_LowValItem.size();++i)
	{
		CString str;
		str.Format(CString("%d"),nLowValItemNum);
		CLowValItem OneItem;
		OneItem=((CProductStep4Dlg*)m_pPageList[4])->m_LowValItem[i];
		OneItem.m_Item=str;  //������¸�ֵ
		m_LowValItem.push_back(OneItem);
		++nLowValItemNum;
	}
	for (int i=0;i<((CProductStep5Dlg*)m_pPageList[5])->m_LowValItem.size();++i)
	{
		CString str;
		str.Format(CString("%d"),nLowValItemNum);
		CLowValItem OneItem;
		OneItem=((CProductStep5Dlg*)m_pPageList[5])->m_LowValItem[i];
		OneItem.m_Item=str;  //������¸�ֵ
		m_LowValItem.push_back(OneItem);
		++nLowValItemNum;
	}
	for (int i=0;i<((CProductStep6Dlg*)m_pPageList[6])->m_LowValItem.size();++i)
	{
		CString str;
		str.Format(CString("%d"),nLowValItemNum);
		CLowValItem OneItem;
		OneItem=((CProductStep6Dlg*)m_pPageList[6])->m_LowValItem[i];
		OneItem.m_Item=str;  //������¸�ֵ
		m_LowValItem.push_back(OneItem);
		++nLowValItemNum;
	}

	//����һ����ָ������
	int nIndexValItemNum=1;
	for (int i=0;i<m_Lvl1TechNam.size();++i)
	{
		CString strIndexVal,strIndexValItemNum;
		strIndexValItemNum.Format(CString("%d"),nIndexValItemNum);
		strIndexVal.Format(CString("%.2f"),m_dC1[i]);

		CIndexValItem OneItem;
		OneItem.m_Item=strIndexValItemNum;
		OneItem.m_IndexNam=m_Lvl1TechNam[i];
		OneItem.m_IndexVal=strIndexVal;

		m_IndexVal.push_back(OneItem);
		++nIndexValItemNum;
	}


	int k=0;//��¼��ֵ����
	for (int i=0;i<m_Lvl2TechNam.size();++i)
	{
		for (int j=0;j<m_Lvl2TechNam[i].size();++j)
		{
			CString strIndexVal,strIndexValItemNum;
			strIndexValItemNum.Format(CString("%d"),nIndexValItemNum);
			strIndexVal.Format(CString("%.2f"),m_dC2[k]);

			CIndexValItem OneItem;
			OneItem.m_Item=strIndexValItemNum;
			OneItem.m_IndexNam=m_Lvl2TechNam[i][j];
			OneItem.m_IndexVal=strIndexVal;

			m_IndexVal.push_back(OneItem);
			++nIndexValItemNum,++k;
		}
	}
}