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
	m_pPageList.clear();            //记录各子对话框
	m_nCurrentPage=0;               //当前显示页
	m_rectPanel=CRect(0,0,0,0);     //子对话框的包围圈
	bInfoWrited=FALSE;

}

CProductNewDlg::~CProductNewDlg()
{
	int n=m_pPageList.size();

	for(int i=0;i<n;i++)
	{
		delete m_pPageList[i];      //释放内存，在这里释放内存因为要把树信息传出去
	}

	//m_pPageList.clear();            //记录各子对话框
	vector<CDialogEx*>().swap(m_pPageList);//清除容器并最小化它的容量

	//delete m_csCaption;             //释放cstatic指针内存
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
	
	//获取子对话框的包容矩形
	GetDlgItem(IDC_STATIC_PLANE)->GetWindowRect(&m_rectPanel);
	ScreenToClient(&m_rectPanel);

	//添加四个属性页

	//////////////////////////////////////////////页面0
	CProductStep0Dlg *pStep0=new CProductStep0Dlg();
	if(pStep0==NULL)
	{
		MessageBox(_T("页面0创建失败"));
		AfxAbort();
	}

	pStep0->Create(IDD_PRODUCTSTEP0_DLG,this);

	if(bInfoWrited)//如果数据库中已经写入，直接进行初始化
	{
		_RecordsetPtr m_pRs;
		CString sql = CString("select * from ProductInfo where ProductID=") + strProductID ;
		m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		CString str1 = (CString)m_pRs->GetCollect("ProductNam");
		CString str2 = (CString)m_pRs->GetCollect("ProductNum");
		CString str3 = (CString)(m_pRs->GetCollect("ProductSub")); 

		CString str44 =  m_pRs->GetCollect("EvalModelID");
		int int4 = _ttoi(str44)-1; //combo从零开始-1

		CString str5 = (CString)(m_pRs->GetCollect("EvalTypeIntro")); 
	    pStep0->m_ProductName=str1;
	    pStep0->m_ProductNum=str2;
		pStep0->m_ProductSub=str3;
		pStep0->str_EvalType=str44;
		pStep0->m_EvalTypeVal=int4;
		pStep0->m_TypeInfo=str5;

		pStep0->SaveProductInfo();//保存产品数据
		::SendMessage(pStep0->m_hWnd,WM_UPDATEDATA,FALSE,FALSE);//更新控件信息
	}
	//显示
	pStep0->MoveWindow(m_rectPanel);
	pStep0->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep0);

	//////////////////////////////////////////////页面1
	CProductStep1Dlg *pStep1=new CProductStep1Dlg();
	if(pStep1==NULL)
	{
		MessageBox(_T("页面1创建失败"));
		AfxAbort();
	}

	pStep1->Create(IDD_PRODUCTSTEP1_DLG,this);

	//显示
	pStep1->MoveWindow(m_rectPanel);
	pStep1->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep1);

	///////////////////////////////////////////页面2
	CProductStep2Dlg *pStep2=new CProductStep2Dlg();
	if(pStep2==NULL)
	{
		MessageBox(_T("页面2创建失败"));
		AfxAbort();
	}

	pStep2->Create(IDD_PRODUCTSTEP2_DLG,this);

	//显示
	pStep2->MoveWindow(m_rectPanel);
	pStep2->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep2);

	////////////////////////////////////////页面3
	CProductStep3Dlg *pStep3=new CProductStep3Dlg();
	if(pStep3==NULL)
	{
		MessageBox(_T("页面3创建失败"));
		AfxAbort();
	}

	pStep3->Create(IDD_PRODUCTSTEP3_DLG,this);

	//显示
	pStep3->MoveWindow(m_rectPanel);
	pStep3->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep3);

	////////////////////////////////////////页面4
	CProductStep4Dlg *pStep4=new CProductStep4Dlg();
	if(pStep4==NULL)
	{
		MessageBox(_T("页面4创建失败"));
		AfxAbort();
	}

	pStep4->Create(IDD_PRODUCTSTEP4_DLG,this);

	//显示
	pStep4->MoveWindow(m_rectPanel);
	pStep4->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep4);

	////////////////////////////////////////页面5
	CProductStep5Dlg *pStep5=new CProductStep5Dlg();
	if(pStep5==NULL)
	{
		MessageBox(_T("页面5创建失败"));
		AfxAbort();
	}

	pStep5->Create(IDD_PRODUCTSTEP5_DLG,this);

	//显示
	pStep5->MoveWindow(m_rectPanel);
	pStep5->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep5);

	////////////////////////////////////////页面6
	CProductStep6Dlg *pStep6=new CProductStep6Dlg();
	if(pStep6==NULL)
	{
		MessageBox(_T("页面6创建失败"));
		AfxAbort();
	}

	pStep6->Create(IDD_PRODUCTSTEP6_DLG,this);

	//显示
	pStep6->MoveWindow(m_rectPanel);
	pStep6->ShowWindow(SW_HIDE);
	m_pPageList.push_back(pStep6);


	///////////////////////////////////////显示第一页
	ShowPage(0);
	UpdateWindow();



	//////////////////////////////////////状态显示初始化
	//m_csCaption=new CStatic();
	m_csCaption.Create(CString("可制造性评价"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,30,130,50),this);

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
		//	return (HBRUSH)::GetStockObject(NULL_BRUSH);   //设置透明画刷
		CFont font;
		font.CreatePointFont(125,_T("隶书"));    //设置字体背景
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
		m_pPageList[i]->DestroyWindow();  //销毁窗口资源
	}
}


void CProductNewDlg::OnBnClickedEvalpre()
{
	// TODO: Add your control notification handler code here
	int nPrePage=m_nCurrentPage-1;      //确定前一页的索引位置
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
	CSetWeighDlg dlg;
	dlg.ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);//先读取表信息
	if(dlg.DoModal()==IDOK)
	{
		GetIndexVal(dlg.m_dA1,dlg.m_dA2);
	}
}


//根据页面情况设置按钮状态
void CProductNewDlg::SetWizButton(UINT nPos)
{
	GetDlgItem(IDC_EVALPRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EVALNEXT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EVALIN)->EnableWindow(TRUE);

	switch(nPos)
	{
	case 0: //第一步(上一步失效)
		GetDlgItem(IDC_EVALPRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 1: //中间步
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 2://中间步
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 3://中间步
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 4://中间步
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 5://中间步
		GetDlgItem(IDC_EVALIN)->EnableWindow(FALSE);
		break;
	case 6: //最后一步
		GetDlgItem(IDC_EVALNEXT)->EnableWindow(FALSE);
		break;
	}
}



//显示nPos页面
void CProductNewDlg::ShowPage(UINT nPos) 
{
	//显示第一页,隐藏当前页，激活下一页
	if(nPos==m_nCurrentPage)
	{
		((CProductStep0Dlg*)m_pPageList[0])->OnWizardActive();
		SetWizButton(0);
		SetTextShow(0);
	}
	else if(nPos>(UINT)m_nCurrentPage)
	{
		//执行的是下一步的操作,
		switch(m_nCurrentPage)
		{
		case 0:
			if(((CProductStep0Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)  //保存当前工作不成功继续当前页
				return;
			//((CProductStep1Dlg*)m_pPageList[nPos])->m_TechValList.DeleteAllItems();
			((CProductStep1Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);
			((CProductStep1Dlg*)m_pPageList[nPos])->ShowListCtrl();
			((CProductStep1Dlg*)m_pPageList[nPos])->OnWizardActive();

			break;
		case 1:
			if(((CProductStep1Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			//((CDlgStep2*)m_pPageList[nPos])->GetInfoFromPrevPage(((CDlgStep1*)m_pPageList[m_nCurrentPage])->m_AsistStore);  //传递信息
			((CProductStep2Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 2:
			if(((CProductStep2Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			//((CProductStep3Dlg*)m_pPageList[nPos])->m_ImpactVibValList.DeleteAllItems();
			((CProductStep3Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);
			((CProductStep3Dlg*)m_pPageList[nPos])->ShowListCtrl();
			((CProductStep3Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 3:
			if(((CProductStep3Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			//((CProductStep4Dlg*)m_pPageList[nPos])->m_ThreeProValList.DeleteAllItems();
			((CProductStep4Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);
			((CProductStep4Dlg*)m_pPageList[nPos])->ShowListCtrl();
			((CProductStep4Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 4:
			if(((CProductStep4Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			//((CProductStep5Dlg*)m_pPageList[nPos])->m_EconomyList.DeleteAllItems();
			((CProductStep5Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[0])->m_ProductInfo);
			((CProductStep5Dlg*)m_pPageList[nPos])->ShowListCtrl();
			((CProductStep5Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		case 5:
			if(((CProductStep5Dlg*)m_pPageList[m_nCurrentPage])->OnWizardNext()==-1)
				return;
			((CProductStep6Dlg*)m_pPageList[nPos])->ReadTechChart();
			((CProductStep6Dlg*)m_pPageList[nPos])->OnWizardActive();
			break;
		default:
			AfxMessageBox(_T("没有下一页,下一步操作有误"));
			break;
		}

		m_nCurrentPage=nPos;
		SetWizButton(nPos);
		SetTextShow(nPos);
	}
	else
	{
		//执行上一步操作，隐藏当前页，激活前一页,向前不用传递信息
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
			AfxMessageBox(_T("没有上一页,上一步操作有误"));
			break;
		}
		m_nCurrentPage=nPos;
		SetWizButton(nPos);
		SetTextShow(nPos);
	}

}

//设置文本状态显示变化
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




///////////////////////////////////////////模糊层次分析法计算相关
void CProductNewDlg::GetIndexVal(VectorXd& dA1,VectorXd& dA2)
{
	/////////////将评分表中获取的cstring评分值转化为double
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
		TechIndexVal.push_back(_ttol(((CProductStep1Dlg*)m_pPageList[1])->m_ListCtrlItem[i].m_IndexScore));     //cstring转double

	}
	for(int i=0;i<n2;++i)
	{
		MatInfoVal.push_back(_ttol(((CProductStep2Dlg*)m_pPageList[2])->m_ListCtrlItem[i].m_MatScore));     //cstring转double

	}
	for(int i=0;i<n3;++i)
	{
		ImpactVibVal.push_back(_ttol(((CProductStep3Dlg*)m_pPageList[3])->m_ListCtrlItem[i].m_IndexScore));     //cstring转double

	}
	for(int i=0;i<n4;++i)
	{
		ThreeProVal.push_back(_ttol(((CProductStep4Dlg*)m_pPageList[4])->m_ListCtrlItem[i].m_IndexScore));     //cstring转double

	}
	for(int i=0;i<n5;++i)
	{
		EconomyVal.push_back(_ttol(((CProductStep5Dlg*)m_pPageList[5])->m_ListCtrlItem[i].m_IndexScore));     //cstring转double

	}
	for(int i=0;i<n6;++i)
	{
		TechMaturyVal.push_back(_ttol(((CProductStep6Dlg*)m_pPageList[6])->m_ListCtrlItem[i].m_TechMaturyVal));     //cstring转double

	}
	double c1,c2,c3,c4,c5,c6;
	c1=MinVal(TechMaturyVal);    //成熟度直接评分，其余选择最低扣分项间接评分
	c2=3+MinVal(TechIndexVal);
	c3=3+MinVal(ThreeProVal);
	c4=3+MinVal(ImpactVibVal);
	c5=3+MinVal(MatInfoVal);
	c6=3+MinVal(EconomyVal);

	vector<double>().swap(TechMaturyVal);//释放vector
	vector<double>().swap(TechIndexVal);
	vector<double>().swap(ThreeProVal);
	vector<double>().swap(ImpactVibVal);
	vector<double>().swap(MatInfoVal);
	vector<double>().swap(EconomyVal);


	//保存二级指标评分
	VectorXd vTemp1(6);
	vTemp1<<c1,c2,c3,c4,c5,c6;
	m_dC2=vTemp1;

	VectorXd dC2(5);      //用于构造模糊矩阵
	dC2<<c1,c2,c3,c4,c5;

	///////////////////////////////////////通过评分按0-1型的隶属函数构建模糊矩阵
	MatrixXd dR2(dC2.size(),4); //评价集项为四个，即0，1，2，3
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
	m_dB2=dA2.transpose()*dR2;//技术指标各子指标对评价集的隶属度
	double cc1=m_dB2*dV;//技术指标的最终评分
	double cc2=c6;      //因为经济指标只有一个子指标，故评分直接为该指标评分

	//保存一级指标评分
	VectorXd vTemp2(2);
	vTemp2<<cc1,cc2;
	m_dC1=vTemp2;


	//构建上级模糊矩阵
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
	m_dB1=dA1.transpose()*dR1; //技术指标和经济指标分别对评价集的隶属度
	m_W=m_dB1*dV;  //最终评分值
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