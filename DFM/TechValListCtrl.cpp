// TechValListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "TechValListCtrl.h"

// CTechValListCtrl

IMPLEMENT_DYNAMIC(CTechValListCtrl, CListCtrl)

CTechValListCtrl::CTechValListCtrl():
isCombo(true)
{
	m_bEditing=FALSE;             //是否存在正在编辑项，默认为否
	m_nlisCombo.clear();          //记录组合框所在项
	m_nNoEdit.clear();           //记录不可编辑项
	m_strlisCombo.clear();       //存储组合框所包含的字符串 
}

CTechValListCtrl::~CTechValListCtrl()
{
	//m_nNoEdit.clear();
	//m_nlisCombo.clear();
	//m_strlisCombo.clear(); 
	vector<int>().swap(m_nNoEdit);//清除容器并最小化它的容量
	vector<int>().swap(m_nlisCombo);
	vector<vector<CString>>().swap(m_strlisCombo);
}


BEGIN_MESSAGE_MAP(CTechValListCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CTechValListCtrl message handlers

void CTechValListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	POSITION pos;
	BOOL bSelected=FALSE;

	//检查是否有Item正在被编辑
	if(m_bEditing==TRUE)
		goto default_session;

	//检查是否有Item被选中,没有时不进入编辑
	pos=GetFirstSelectedItemPosition();       //获取第一个被选中的行

	if(pos)
	{
		//得到被点击的Item
		LVHITTESTINFO testinfo;
		testinfo.pt.x=point.x;
		testinfo.pt.y=point.y;               //点击时鼠标的位置（应该是相对于ListCtrl的客户区坐标）
		testinfo.flags=LVHT_ONITEMLABEL;     //点击的必须是标题

		if(SubItemHitTest(&testinfo)<0)
			goto default_session;            //没有点中有效区

		m_nItem=testinfo.iItem;
		m_nSubItem=testinfo.iSubItem;        //求出被点中项的行号与列号

		//检查该项是否被选中,没被选中不进入编辑
		while(pos)                            //不多余，有可能同时选中了多行，编辑位置要从选中行中选
		{
			if(m_nItem==GetNextSelectedItem(pos))   //确定选中的行
			{
				bSelected=TRUE;
				break;
			}
		}

		if(bSelected==FALSE)
			goto default_session;   //没有点在有效区不被编辑

		//判断是否是匹配指标项弹出匹配框
		isCombo=true;//每次进来都要重新赋值默认为真
		CString strClassify=this->GetItemText(m_nItem,1);
		if(strClassify==CString("机箱（匹配）"))
		{
			isCombo=false; //设定为非combo行
			::SendMessageA(GetParent()->m_hWnd,WM_INDEXMATCH,m_nItem,0); //如果是匹配指标项发消息到父窗口，进行匹配  
		}


		//是否为组合框控制项
		int n=m_nlisCombo.size();
		for(int i=0;i<n;i++)
		{
			if(m_nSubItem==m_nlisCombo[i]&&isCombo)
			{
				m_bEditing=MyBeginComboBox();
				return;
			}
		}

		//是否为编辑框控制项
		int m=m_nNoEdit.size();
		for(int i=0;i<m;i++)
		{
			if(m_nSubItem==m_nNoEdit[i])
			{
				return;
			}
		}

		//开始编辑,其余情况编辑框管辖区
		m_bEditing=MyBeginEdit();
		return;

	}

default_session:
	CListCtrl::OnLButtonDown(nFlags, point);
}




BOOL CTechValListCtrl::MyBeginEdit(void)
{
	//得到被编辑表项的区域
	CRect rect;
	if(GetSubItemRect(m_nItem,m_nSubItem,LVIR_LABEL,rect)==FALSE)   //获取列表项的大小
		return FALSE;
	//创建编辑控件
	int style=WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER;
	if(m_edit.Create(style,rect,this,ID_MYEDIT)==FALSE)     
		return FALSE;

	//取被编辑表项的文字
	CString txtItem=GetItemText(m_nItem,m_nSubItem);        //获取列表项的文本

	//取出的文字填写到编辑控件
	m_edit.SetWindowTextW(txtItem);
	m_edit.SetFocus();
	m_edit.SetSel(0,-1);     //选中的字符范围void SetSel( long nStartChar, long nEndChar );
	m_edit.ShowWindow(SW_SHOW);

	return TRUE;
}

void CTechValListCtrl::MyEndEdit(bool bValidate)
{
	//编辑结果是有效的，重设被编辑表项的文字
	if(bValidate)
	{
		CString txtItem;
		m_edit.GetWindowTextW(txtItem);
		SetItemText(m_nItem,m_nSubItem,txtItem);
	}
	else
	{
		CString txtItem=GetItemText(m_nItem,m_nSubItem);
		SetItemText(m_nItem,m_nSubItem,txtItem);
	}

	//销毁编辑窗口
	m_edit.DestroyWindow();  //对象还在只是销毁窗口资源
	m_bEditing=FALSE;

	//::SendMessageA(GetParent()->m_hWnd,WM_USEREDIT,0,0);     //发送自定义消息给父窗口,编辑过也需要重新检测合理性
}

////////////编辑组合框

//3开始编辑组合框
BOOL CTechValListCtrl::MyBeginComboBox(void)
{
	//得到被编辑表项的区域
	CRect rect;
	if(GetSubItemRect(m_nItem,m_nSubItem,LVIR_LABEL,rect)==FALSE)   //获取列表项的大小
		return FALSE;

	//创建编辑控件
	int style=WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER|WS_VSCROLL|CBS_DROPDOWNLIST;
	if(m_ComboBox.Create(style,rect,this,ID_MYCOMBO)==FALSE)     
		return FALSE;

	//取被编辑表项的文字
	CString txtItem=GetItemText(m_nItem,m_nSubItem);        //获取当前列表项的文本

	m_ComboBox.InitCombo(m_strlisCombo[m_nItem]);     //填充组合框

	int n=m_ComboBox.FindString(0,txtItem);

	if(n>=0)
		m_ComboBox.SetCurSel(n);

	m_ComboBox.SetFocus();
	m_ComboBox.ShowWindow(SW_SHOW);

	return TRUE;
}

//4 结束组合框编辑
void CTechValListCtrl::MyEndComboBox(void)
{
	CString txtItem;
	m_ComboBox.GetWindowTextW(txtItem);
	SetItemText(m_nItem,m_nSubItem,txtItem);

	//销毁编辑窗口
	m_ComboBox.DestroyWindow();
	m_bEditing=FALSE;

	::SendMessageA(GetParent()->m_hWnd,WM_SETINDEXVAL,m_nItem,0);     //发送自定义消息给父窗口插入评分值
}


//void CTechValListCtrl::InputIndexVal()
//{
//	//对应分值的输入
//	CString strIndexNam=GetItemText(m_nItem,2);
//	CString strValInfo=GetItemText(m_nItem,3);
//	/*CString sql = CString("select * from TechEvalIndex where TechEvalIndexNam= '")+strIndexNam+CString("'");*/
//	CString sql_tabnam;	
//	sql_tabnam.Format(_T("select * from TechEvalIndex where TechEvalIndexNam='%s'"),strIndexNam);
//	_bstr_t bstrsql_tabnam=(_bstr_t)sql_tabnam;
//
//	m_pRecordset_tab=theApp.m_pConnect->Execute(bstrsql_tabnam, NULL, adCmdText);
//	/*m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);*/
//	CString strIndexID=(CString)(m_pRecordset_tab->GetCollect("TechEvalIndexID"));  //查询指标ID
//	m_pRecordset_tab.Release();
//
//	CString sql1= CString("select * from EvalIndexVal where TechEvalIndexID= ")+strIndexID+CString("and TechEvalIndexValInfo = '")+strValInfo+CString("'");
//
//	m_pRecordset_tab= theApp.m_pConnect->Execute(_bstr_t(sql1), NULL, adCmdText);
//	CString strDeductVal=(CString)(m_pRecordset_tab->GetCollect("TechDeductVal"));  //查询分值
//
//	SetItemText(m_nItem,4,strDeductVal);                    //设置分值
//}



void CTechValListCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	ModifyStyle(LVS_EDITLABELS,0L);     //禁止标题编辑
	ModifyStyle(0L,LVS_REPORT);         //设为Report类型
	ModifyStyle(0L,LVS_SHOWSELALWAYS);   //始终高亮度被选中的表项

	SetExtendedStyle(LVS_EX_FULLROWSELECT|        //允许整行被选中
		LVS_EX_HEADERDRAGDROP|       //允许整列拖动
		LVS_EX_GRIDLINES|            //画出网格线
		LVS_EX_ONECLICKACTIVATE|     //单击选中表项
		LVS_EX_FLATSB);              //扁平风格

	CListCtrl::PreSubclassWindow();      
}



//设置加载组合框的列
void CTechValListCtrl::SetnComboList(vector<int>& nlisCombo)
{
	m_nlisCombo.clear();

	int n=nlisCombo.size();
	for(int i=0;i<n;i++)
		m_nlisCombo.push_back(nlisCombo[i]);  //添加新项
}

//设置不可编辑项
void CTechValListCtrl::SetnNoEditList(vector<int>& nlisNoEdit)
{
	m_nNoEdit.clear();

	int n=nlisNoEdit.size();
	for(int i=0;i<n;i++)
		m_nNoEdit.push_back(nlisNoEdit[i]);  //添加新项
}

//设置组合框字符串
void CTechValListCtrl::SetComboString(vector<CString>& lisStr)
{
	int n=lisStr.size();
	//m_strlisCombo.clear();
	vector<CString> vtemp;
	vtemp.clear();
	for(int i=0;i<n;i++)
		vtemp.push_back(lisStr[i]);
	m_strlisCombo.push_back(vtemp);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit1, CEdit)

CMyEdit1::CMyEdit1()
{
	m_bInputValid=TRUE;
}

CMyEdit1::~CMyEdit1()
{
}


BEGIN_MESSAGE_MAP(CMyEdit1, CEdit)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CMyEdit 消息处理程序


int CMyEdit1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	//改变字体
	LOGFONT logfont;
	logfont.lfHeight=-12;
	logfont.lfWidth=0;
	logfont.lfEscapement=0;
	logfont.lfOrientation=0;
	logfont.lfWeight=400;
	logfont.lfItalic=0;
	logfont.lfUnderline=0;
	logfont.lfStrikeOut=0;
	logfont.lfCharSet=134;
	logfont.lfOutPrecision=0;
	logfont.lfClipPrecision=0;
	logfont.lfQuality=0;
	logfont.lfPitchAndFamily=2;
	wcscpy_s(logfont.lfFaceName,_T("宋体"));

	m_font.DeleteObject();
	if(m_font.CreateFontIndirectW(&logfont))
		SetFont(&m_font);
	return 0;


	//return 0;
}


/*void CMyEdit::OnEnKillfocus()
{
	// TODO: 在此添加控件通知处理程序代码
}*/


void CMyEdit1::OnKillFocus(CWnd* pNewWnd)
{
	//得到父窗口，并通知父窗口结束编辑过程
	CTechValListCtrl *parent=(CTechValListCtrl*)GetParent();
	if(parent)
	{
		parent->MyEndEdit(m_bInputValid);
		m_bInputValid=TRUE;
	}
	CEdit::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
}


BOOL CMyEdit1::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	//拦截ESC键和Enter键按下的消息，解释为WM_KILLFOUCS消息
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==13)           //回车键
			pMsg->message=WM_KILLFOCUS;
		
		if(pMsg->wParam==27)      //ESC键
		{
			m_bInputValid=FALSE;
			pMsg->message=WM_KILLFOCUS;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// E:\New_Document\solve_TstWizard\TstWizard\NewListCtrl.cpp : implementation file
//


// CMyCombo

IMPLEMENT_DYNAMIC(CMyCombo1, CComboBox)

CMyCombo1::CMyCombo1():
bMatching(FALSE)
{

}

CMyCombo1::~CMyCombo1()
{
}


BEGIN_MESSAGE_MAP(CMyCombo1, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CMyCombo1::OnCbnSelchange)
	ON_WM_CREATE()
	//ON_CONTROL_REFLECT(CBN_KILLFOCUS, &CMyCombo1::OnCbnKillfocus)
END_MESSAGE_MAP()



// CMyCombo message handlers




void CMyCombo1::OnCbnSelchange()
{
	// TODO: Add your control notification handler code here
	
	//得到父窗口，并通知父窗口结束编辑过程
	CTechValListCtrl *parent=(CTechValListCtrl*)GetParent();
	if(parent)
	{
		parent->MyEndComboBox();
	}
}


int CMyCombo1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	//改变字体
	LOGFONT logfont;
	logfont.lfHeight=-12;
	logfont.lfWidth=0;
	logfont.lfEscapement=0;
	logfont.lfOrientation=0;
	logfont.lfWeight=400;
	logfont.lfItalic=0;
	logfont.lfUnderline=0;
	logfont.lfStrikeOut=0;
	logfont.lfCharSet=134;
	logfont.lfOutPrecision=0;
	logfont.lfClipPrecision=0;
	logfont.lfQuality=0;
	logfont.lfPitchAndFamily=2;
	wcscpy(logfont.lfFaceName,_T("宋体"));

	m_font.DeleteObject();
	if(m_font.CreateFontIndirectW(&logfont))
		SetFont(&m_font);
	return 0;

}

//初始化组合框列表
void CMyCombo1::InitCombo(vector<CString>& lisStr)
{
	int n=lisStr.size();

	for(int i=0;i<n;i++)
	{
		this->InsertString(i,lisStr[i]);
	}
}




//void CMyCombo1::OnCbnKillfocus()
//{
//	// TODO: Add your control notification handler code here
//	//得到父窗口，并通知父窗口结束编辑过程
//	CTechValListCtrl *parent=(CTechValListCtrl*)GetParent();
//	if(parent&&!bMatching)
//	{
//		parent->MyEndComboBox();
//	}
//}




