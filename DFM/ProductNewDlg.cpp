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

	m_pPageList.clear();            //记录各子对话框
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

	///////////////////////////////////////如果信息没写入显示第一页否则显示第二页
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
		//	return (HBRUSH)::GetStockObject(NULL_BRUSH);   //设置透明画刷
		CFont font;
		font.CreatePointFont(125,_T("隶书"));    //设置字体背景
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
	case 3: //最后一步
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
			//((CProductStep1Dlg*)m_pPageList[nPos])->m_ProductInfo=((CProductStep0Dlg*)m_pPageList[m_nCurrentPage])->m_ProductInfo;
			((CProductStep1Dlg*)m_pPageList[nPos])->ReadTechChart(((CProductStep0Dlg*)m_pPageList[m_nCurrentPage])->m_ProductInfo);
			((CProductStep1Dlg*)m_pPageList[nPos])->ShowListCtrl(((CProductStep1Dlg*)m_pPageList[nPos])->m_Lvl4TechID);
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
			//((CDlgStep3*)m_pPageList[nPos])->GetExternInfo(((CDlgStep2*)m_pPageList[m_nCurrentPage])->m_NodNamList);   //传递节点信息
			((CProductStep3Dlg*)m_pPageList[nPos])->OnWizardActive();
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
		default:
			AfxMessageBox(_T("没有上一页,上一步操作有误"));
			break;
		}
		m_nCurrentPage=nPos;
		SetWizButton(nPos);
		SetTextShow(nPos);
	}

}

//设置文本状态显示
void CProductNewDlg::SetTextShow(UINT nPos)
{
	CStatic *cs1,*cs2;
	cs1=new CStatic();
	cs2=new CStatic();
	switch(nPos)
	{
	case 0:
		cs1->Create(CString("可制造性评价"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,30,130,50),this);
		cs2->Create(CString("产品信息录入"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,150,130,170),this);
		break;
	case 1:
		//cs2->Invalidate();
		cs2->Create(CString("工艺性评分表"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,150,130,170),this);
		break;
	case 2:
		//cs2->Invalidate();
		cs2->Create(CString("工艺成熟度表"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,150,130,170),this);
		break;
	case 3:
		//cs2->Invalidate();
		cs2->Create(CString("环境适应性表"),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(20,150,130,170),this);
	}
	//delete cs1,cs2;
}