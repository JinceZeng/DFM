
// DFMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DFM.h"
#include "DFMDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"
#include "ChangePwdDlg.h"
#include "ProductNewDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDFMDlg 对话框




CDFMDlg::CDFMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDFMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDFMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PRODUCTINFO, m_ProductInfoList);
}

BEGIN_MESSAGE_MAP(CDFMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(ID_MENU_LOGIN, &CDFMDlg::OnMenuLogin)
	ON_COMMAND(ID_MENU_ABOUT, &CDFMDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_PSW, &CDFMDlg::OnMenuPsw)
	ON_COMMAND(ID_EVALNEW, &CDFMDlg::OnEvalnew)
	ON_MESSAGE(WM_DELETEDATA,&CDFMDlg::OnDeleteData)
	ON_MESSAGE(WM_UPDATELIST,&CDFMDlg::OnUpdateList)
	ON_MESSAGE(WM_EVALIN,&CDFMDlg::OnEvalIn)
	ON_COMMAND(IDC_MODELNEW, &CDFMDlg::OnEvalnew)//新建评分按钮相应
END_MESSAGE_MAP()


//控件大小位置变化(暂未使用此功能)
//BEGIN_EASYSIZE_MAP(CDFMDlg, CDialogEx) 
//	EASYSIZE(IDC_MODELNEW,ES_BORDER,ES_BORDER,IDC_EVALRESULT,ES_KEEPSIZE,ES_HCENTER) //此处根据自己需求 
//	EASYSIZE(IDC_EVALRESULT,IDC_MODELNEW,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_HCENTER)
//	EASYSIZE(IDC_LIST_PRODUCTINFO,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
//END_EASYSIZE_MAP 

// CDFMDlg 消息处理程序

BOOL CDFMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//// 将“关于...”菜单项添加到系统菜单中。

	//// IDM_ABOUTBOX 必须在系统命令范围内。
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != NULL)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	UINT indicators[] = 
	{
		IDS_INDICATOR_MESSAGE,
		IDS_INDICATOR_USER,
		IDS_INDICATOR_TIME
	};
	ModifyStyle(WS_THICKFRAME,0);
	if(!m_Statusbar.Create(this)||
		!m_Statusbar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Can't create status bar\n");
		return false;
	}
	ModifyStyle(0,WS_THICKFRAME);

	//获取IDS_INDICATOR_MESSAGE,IDS_INDICATOR_USER，IDS_INDICATOR_TIME的索引和对应的宽度
	index1 = m_Statusbar.CommandToIndex(IDS_INDICATOR_MESSAGE);
	index2 = m_Statusbar.CommandToIndex(IDS_INDICATOR_USER);
	index3 = m_Statusbar.CommandToIndex(IDS_INDICATOR_TIME);

	m_Statusbar.GetPaneInfo(index1,nID,nStyle,nWidth1);
	m_Statusbar.GetPaneInfo(index2,nID,nStyle,nWidth2);
	m_Statusbar.GetPaneInfo(index3,nID,nStyle,nWidth3);

	CRect rect;
	GetClientRect(&rect);

	//设置面板的宽度
	m_Statusbar.SetPaneInfo(index1,nID,nStyle,rect.Width()/2);
	m_Statusbar.SetPaneInfo(index2,nID,nStyle,rect.Width()/3);
	m_Statusbar.SetPaneInfo(index3,nID,nStyle,rect.Width()/6);

	//重新摆放控件 因为增加状态栏之后 控件相对位置发生变化  重新摆放才能显示出来
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0); 

	//设置文本 index=0，2处的文本内容
	CString str1=_T("可制造性评价");
	CTime time;
	time = CTime::GetCurrentTime();
	CString str2 = time.Format("%Y-%m-%d");
	m_Statusbar.SetPaneText(0,str1);
	m_Statusbar.SetPaneText(2,str2);


    //菜单项初始化变灰操作
	CMenu *pMenu = GetMenu();
	pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(4)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	//pMenu->Detach();
	//DrawMenuBar();    //更新菜单显示
	//按钮变灰
	GetDlgItem(IDC_MODELNEW)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVALRESULT)->EnableWindow(FALSE);

	ChangeStyle(m_ProductInfoList);//list风格改变
	//将列表控件先初始化,插入表头
	CRect rec1;
	int width1;
	m_ProductInfoList.GetClientRect(&rec1);
	width1=rec1.Width();

	m_ProductInfoList.InsertColumn(0,_T("序号"), LVCFMT_CENTER,width1/16);
	m_ProductInfoList.InsertColumn(1,_T("ID"), LVCFMT_CENTER,width1/16);
	m_ProductInfoList.InsertColumn(2,_T("产品编号"),LVCFMT_CENTER,width1/8);
	m_ProductInfoList.InsertColumn(3,_T("产品名称"),LVCFMT_CENTER,width1/8);
	m_ProductInfoList.InsertColumn(4,_T("隶属整件"),LVCFMT_CENTER,width1/8);
	m_ProductInfoList.InsertColumn(5,_T("评价模型"),LVCFMT_CENTER,width1/8);
	m_ProductInfoList.InsertColumn(6,_T("任务状态"),LVCFMT_CENTER,width1/8);
	m_ProductInfoList.InsertColumn(7,_T("评价人"),LVCFMT_CENTER,width1/8);
	m_ProductInfoList.InsertColumn(8,_T("评价时间"),LVCFMT_CENTER,width1/8);

	OnMenuLogin();
	//INIT_EASYSIZE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDFMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDFMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDFMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//响应窗口大小变化（暂未使用）
void CDFMDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	//改变状态栏大小
	CRect rectDlg,rectBar;
	GetClientRect(rectDlg);
	if(m_Statusbar&&(0 != rectDlg.Width()))

	{

		CStatusBar *m_pwndStatusBar = (CStatusBar*)&m_Statusbar;  

		m_pwndStatusBar->GetClientRect(&rectBar);  

		m_pwndStatusBar->SetPaneInfo(index1,nID,nStyle,rectDlg.Width()/2); 
		m_pwndStatusBar->SetPaneInfo(index2,nID,nStyle,rectDlg.Width()/3);
		m_pwndStatusBar->SetPaneInfo(index3,nID,nStyle,rectDlg.Width()/6); 
		m_pwndStatusBar->MoveWindow(0,cy-rectBar.Height(),rectDlg.Width(),rectBar.Height());  

	}

	//UPDATE_EASYSIZE;

}


void CDFMDlg::ChangeStyle(CPInfoListCtrl &m_ListCtrl)
{
	//获得原有风格
	DWORD dwStyle =::GetWindowLong(m_ListCtrl.m_hWnd,GWL_STYLE);
	dwStyle &= ~(LVS_TYPEMASK); 
	dwStyle &= ~(LVS_EDITLABELS);

	//设置新风格
	SetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE,dwStyle|LVS_REPORT|LVS_NOLABELWRAP|LVS_SHOWSELALWAYS);

	//设置扩展风格
	DWORD styles = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES/*|LVS_EX_CHECKBOXES*/;  
	ListView_SetExtendedListViewStyleEx(m_ListCtrl.m_hWnd, styles, styles ); 

}


void CDFMDlg::UpdateListCtrl()
{
	m_ProductInfoList.DeleteAllItems();
	_RecordsetPtr m_pRs1;

	CString sql = CString("select * from ProductInfo");
	m_pRs1 = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);

	int n=0;
	while (!m_pRs1->adoEOF)
	{
		CString str0;
		str0.Format(CString("%d"),n+1); //int转cstring
		CString str8 = (m_pRs1->GetCollect("ProductID"));       //数据库中int型数据获取后不能加cstring强制转换
		CString str1 = (CString)(m_pRs1->GetCollect("ProductNam"));
		CString str2 = (CString)(m_pRs1->GetCollect("ProductNum"));
		CString str3 = (CString)(m_pRs1->GetCollect("ProductSub")); 

		CString str4;
		CString str44 = m_pRs1->GetCollect("EvalModelID");
		_RecordsetPtr m_pRs2;
		CString sql = CString("select * from EvalModelInfo where EvalModelID=") + str44 ;
		m_pRs2 = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		str4 =(CString)m_pRs2->GetCollect("EvalModelNam");
		

		CString str5;
		CString str55;
		str55 = m_pRs1->GetCollect("IsEval");
		int i = _ttoi(str55);                //cstring转int  
		//int i=atoi((char *)(_bstr_t)str55);//cstring转int
		if(i==0) str5=CString("进行中");
		else     str5=CString("已发布");

		CString str6 = theApp.name;
		CString str7 = (CString)(m_pRs1->GetCollect("EvalTime"));

		m_ProductInfoList.InsertItem(n,str0);
		m_ProductInfoList.SetItemText(n,1,str8);
		m_ProductInfoList.SetItemText(n,2,str1);
		m_ProductInfoList.SetItemText(n,3,str2);
		m_ProductInfoList.SetItemText(n,4,str3);
		m_ProductInfoList.SetItemText(n,5,str4);
		m_ProductInfoList.SetItemText(n,6,str5);
		m_ProductInfoList.SetItemText(n,7,str6);
		m_ProductInfoList.SetItemText(n,8,str7);

	    n++;
		m_pRs1->MoveNext();
	}


}

void CDFMDlg::OnMenuLogin()
{
	// TODO: Add your command handler code here
	CLoginDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		_RecordsetPtr m_pRs;
		CString sql = CString("select * from Login where Uname='") + theApp.name + "'";
		m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		CString str_power = m_pRs->GetCollect("Power");
		int power = atoi((char *)(_bstr_t)str_power);
		if (power == 1)
		{
			//m_Toolbar.GetToolBarCtrl().EnableButton(IDB_addcai, true);
			//m_Toolbar.GetToolBarCtrl().EnableButton(IDB_kaitai, true);
			//m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiezhang, true);
			//m_Toolbar.GetToolBarCtrl().EnableButton(IDB_jiesuan, true);
			//m_Toolbar.GetToolBarCtrl().EnableButton(IDB_yuangong, true);
			//m_Toolbar.GetToolBarCtrl().EnableButton(IDB_logout, true);
			CMenu *pMenu = GetMenu();           //更改菜单显示
			pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(4)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->EnableMenuItem(0,MF_BYPOSITION | MF_GRAYED);
			AfxGetMainWnd()->DrawMenuBar();    //更新菜单显示

			//更新按钮
			GetDlgItem(IDC_MODELNEW)->EnableWindow(true);
			GetDlgItem(IDC_EVALRESULT)->EnableWindow(true);
		}
		m_Statusbar.SetPaneText(1, CString("当前用户: ") + theApp.name);
		SetWindowText(CString("可制造性评价      当前登录用户: ") + theApp.name);


        UpdateListCtrl();
	}
}


//自定义消息删除某一条产品信息
LRESULT CDFMDlg::OnDeleteData(WPARAM wParam,LPARAM lParam)
{
	m_ProductInfoList.DeleteItem(wParam);
	CString str((TCHAR*)lParam);   //lparam转cstring(此处必须用tchar,char会导致精度损耗)
	_RecordsetPtr m_pRs;
	CString sql = CString("delete * from ProductInfo where ProductID=") + str;
	try
	{
		m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
		AfxMessageBox(CString("产品信息删除成功"));
	}
	catch(_com_error &e)
	{        
		CString temp;
		temp.Format(e.Description());
		AfxMessageBox(temp);
	}

	UpdateListCtrl();
	return 0;
}


//自定义消息刷新list
LRESULT CDFMDlg::OnUpdateList(WPARAM wParam,LPARAM lParam)
{
	UpdateListCtrl();
	return 0;
}

//自定义消息进入评价
LRESULT CDFMDlg::OnEvalIn(WPARAM wParam,LPARAM lParam)
{
	CProductNewDlg dlg;
	CString str;
	str=m_ProductInfoList.GetItemText(wParam,1);
	dlg.strProductID=str;   //获取产品信息ID
	dlg.bInfoWrited=true;   //右键菜单重新编辑，产品信息已写入
	dlg.DoModal();
	return 0;
}






//关于对话框
void CDFMDlg::OnMenuAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

//修改密码
void CDFMDlg::OnMenuPsw()
{
	// TODO: Add your command handler code here
	CChangePwdDlg dlg;
	dlg.DoModal();
}



//新建评价
void CDFMDlg::OnEvalnew()
{
	// TODO: Add your command handler code here
	CProductNewDlg dlg;
	dlg.DoModal();
}

