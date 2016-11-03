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
	m_bEditing=FALSE;             //�Ƿ�������ڱ༭�Ĭ��Ϊ��
	m_nlisCombo.clear();          //��¼��Ͽ�������
	m_nNoEdit.clear();           //��¼���ɱ༭��
	m_strlisCombo.clear();       //�洢��Ͽ����������ַ��� 
}

CTechValListCtrl::~CTechValListCtrl()
{
	//m_nNoEdit.clear();
	//m_nlisCombo.clear();
	//m_strlisCombo.clear(); 
	vector<int>().swap(m_nNoEdit);//�����������С����������
	vector<int>().swap(m_nlisCombo);
	vector<vector<CString>>().swap(m_strlisCombo);
}


BEGIN_MESSAGE_MAP(CTechValListCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CTechValListCtrl message handlers

void CTechValListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	POSITION pos;
	BOOL bSelected=FALSE;

	//����Ƿ���Item���ڱ��༭
	if(m_bEditing==TRUE)
		goto default_session;

	//����Ƿ���Item��ѡ��,û��ʱ������༭
	pos=GetFirstSelectedItemPosition();       //��ȡ��һ����ѡ�е���

	if(pos)
	{
		//�õ��������Item
		LVHITTESTINFO testinfo;
		testinfo.pt.x=point.x;
		testinfo.pt.y=point.y;               //���ʱ����λ�ã�Ӧ���������ListCtrl�Ŀͻ������꣩
		testinfo.flags=LVHT_ONITEMLABEL;     //����ı����Ǳ���

		if(SubItemHitTest(&testinfo)<0)
			goto default_session;            //û�е�����Ч��

		m_nItem=testinfo.iItem;
		m_nSubItem=testinfo.iSubItem;        //�������������к����к�

		//�������Ƿ�ѡ��,û��ѡ�в�����༭
		while(pos)                            //�����࣬�п���ͬʱѡ���˶��У��༭λ��Ҫ��ѡ������ѡ
		{
			if(m_nItem==GetNextSelectedItem(pos))   //ȷ��ѡ�е���
			{
				bSelected=TRUE;
				break;
			}
		}

		if(bSelected==FALSE)
			goto default_session;   //û�е�����Ч�������༭

		//�ж��Ƿ���ƥ��ָ�����ƥ���
		isCombo=true;//ÿ�ν�����Ҫ���¸�ֵĬ��Ϊ��
		CString strClassify=this->GetItemText(m_nItem,1);
		if(strClassify==CString("���䣨ƥ�䣩"))
		{
			isCombo=false; //�趨Ϊ��combo��
			::SendMessageA(GetParent()->m_hWnd,WM_INDEXMATCH,m_nItem,0); //�����ƥ��ָ�����Ϣ�������ڣ�����ƥ��  
		}


		//�Ƿ�Ϊ��Ͽ������
		int n=m_nlisCombo.size();
		for(int i=0;i<n;i++)
		{
			if(m_nSubItem==m_nlisCombo[i]&&isCombo)
			{
				m_bEditing=MyBeginComboBox();
				return;
			}
		}

		//�Ƿ�Ϊ�༭�������
		int m=m_nNoEdit.size();
		for(int i=0;i<m;i++)
		{
			if(m_nSubItem==m_nNoEdit[i])
			{
				return;
			}
		}

		//��ʼ�༭,��������༭���Ͻ��
		m_bEditing=MyBeginEdit();
		return;

	}

default_session:
	CListCtrl::OnLButtonDown(nFlags, point);
}




BOOL CTechValListCtrl::MyBeginEdit(void)
{
	//�õ����༭���������
	CRect rect;
	if(GetSubItemRect(m_nItem,m_nSubItem,LVIR_LABEL,rect)==FALSE)   //��ȡ�б���Ĵ�С
		return FALSE;
	//�����༭�ؼ�
	int style=WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER;
	if(m_edit.Create(style,rect,this,ID_MYEDIT)==FALSE)     
		return FALSE;

	//ȡ���༭���������
	CString txtItem=GetItemText(m_nItem,m_nSubItem);        //��ȡ�б�����ı�

	//ȡ����������д���༭�ؼ�
	m_edit.SetWindowTextW(txtItem);
	m_edit.SetFocus();
	m_edit.SetSel(0,-1);     //ѡ�е��ַ���Χvoid SetSel( long nStartChar, long nEndChar );
	m_edit.ShowWindow(SW_SHOW);

	return TRUE;
}

void CTechValListCtrl::MyEndEdit(bool bValidate)
{
	//�༭�������Ч�ģ����豻�༭���������
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

	//���ٱ༭����
	m_edit.DestroyWindow();  //������ֻ�����ٴ�����Դ
	m_bEditing=FALSE;

	//::SendMessageA(GetParent()->m_hWnd,WM_USEREDIT,0,0);     //�����Զ�����Ϣ��������,�༭��Ҳ��Ҫ���¼�������
}

////////////�༭��Ͽ�

//3��ʼ�༭��Ͽ�
BOOL CTechValListCtrl::MyBeginComboBox(void)
{
	//�õ����༭���������
	CRect rect;
	if(GetSubItemRect(m_nItem,m_nSubItem,LVIR_LABEL,rect)==FALSE)   //��ȡ�б���Ĵ�С
		return FALSE;

	//�����༭�ؼ�
	int style=WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER|WS_VSCROLL|CBS_DROPDOWNLIST;
	if(m_ComboBox.Create(style,rect,this,ID_MYCOMBO)==FALSE)     
		return FALSE;

	//ȡ���༭���������
	CString txtItem=GetItemText(m_nItem,m_nSubItem);        //��ȡ��ǰ�б�����ı�

	m_ComboBox.InitCombo(m_strlisCombo[m_nItem]);     //�����Ͽ�

	int n=m_ComboBox.FindString(0,txtItem);

	if(n>=0)
		m_ComboBox.SetCurSel(n);

	m_ComboBox.SetFocus();
	m_ComboBox.ShowWindow(SW_SHOW);

	return TRUE;
}

//4 ������Ͽ�༭
void CTechValListCtrl::MyEndComboBox(void)
{
	CString txtItem;
	m_ComboBox.GetWindowTextW(txtItem);
	SetItemText(m_nItem,m_nSubItem,txtItem);

	//���ٱ༭����
	m_ComboBox.DestroyWindow();
	m_bEditing=FALSE;

	::SendMessageA(GetParent()->m_hWnd,WM_SETINDEXVAL,m_nItem,0);     //�����Զ�����Ϣ�������ڲ�������ֵ
}


//void CTechValListCtrl::InputIndexVal()
//{
//	//��Ӧ��ֵ������
//	CString strIndexNam=GetItemText(m_nItem,2);
//	CString strValInfo=GetItemText(m_nItem,3);
//	/*CString sql = CString("select * from TechEvalIndex where TechEvalIndexNam= '")+strIndexNam+CString("'");*/
//	CString sql_tabnam;	
//	sql_tabnam.Format(_T("select * from TechEvalIndex where TechEvalIndexNam='%s'"),strIndexNam);
//	_bstr_t bstrsql_tabnam=(_bstr_t)sql_tabnam;
//
//	m_pRecordset_tab=theApp.m_pConnect->Execute(bstrsql_tabnam, NULL, adCmdText);
//	/*m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);*/
//	CString strIndexID=(CString)(m_pRecordset_tab->GetCollect("TechEvalIndexID"));  //��ѯָ��ID
//	m_pRecordset_tab.Release();
//
//	CString sql1= CString("select * from EvalIndexVal where TechEvalIndexID= ")+strIndexID+CString("and TechEvalIndexValInfo = '")+strValInfo+CString("'");
//
//	m_pRecordset_tab= theApp.m_pConnect->Execute(_bstr_t(sql1), NULL, adCmdText);
//	CString strDeductVal=(CString)(m_pRecordset_tab->GetCollect("TechDeductVal"));  //��ѯ��ֵ
//
//	SetItemText(m_nItem,4,strDeductVal);                    //���÷�ֵ
//}



void CTechValListCtrl::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���

	ModifyStyle(LVS_EDITLABELS,0L);     //��ֹ����༭
	ModifyStyle(0L,LVS_REPORT);         //��ΪReport����
	ModifyStyle(0L,LVS_SHOWSELALWAYS);   //ʼ�ո����ȱ�ѡ�еı���

	SetExtendedStyle(LVS_EX_FULLROWSELECT|        //�������б�ѡ��
		LVS_EX_HEADERDRAGDROP|       //���������϶�
		LVS_EX_GRIDLINES|            //����������
		LVS_EX_ONECLICKACTIVATE|     //����ѡ�б���
		LVS_EX_FLATSB);              //��ƽ���

	CListCtrl::PreSubclassWindow();      
}



//���ü�����Ͽ����
void CTechValListCtrl::SetnComboList(vector<int>& nlisCombo)
{
	m_nlisCombo.clear();

	int n=nlisCombo.size();
	for(int i=0;i<n;i++)
		m_nlisCombo.push_back(nlisCombo[i]);  //�������
}

//���ò��ɱ༭��
void CTechValListCtrl::SetnNoEditList(vector<int>& nlisNoEdit)
{
	m_nNoEdit.clear();

	int n=nlisNoEdit.size();
	for(int i=0;i<n;i++)
		m_nNoEdit.push_back(nlisNoEdit[i]);  //�������
}

//������Ͽ��ַ���
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



// CMyEdit ��Ϣ�������


int CMyEdit1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	//�ı�����
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
	wcscpy_s(logfont.lfFaceName,_T("����"));

	m_font.DeleteObject();
	if(m_font.CreateFontIndirectW(&logfont))
		SetFont(&m_font);
	return 0;


	//return 0;
}


/*void CMyEdit::OnEnKillfocus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}*/


void CMyEdit1::OnKillFocus(CWnd* pNewWnd)
{
	//�õ������ڣ���֪ͨ�����ڽ����༭����
	CTechValListCtrl *parent=(CTechValListCtrl*)GetParent();
	if(parent)
	{
		parent->MyEndEdit(m_bInputValid);
		m_bInputValid=TRUE;
	}
	CEdit::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������
}


BOOL CMyEdit1::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	//����ESC����Enter�����µ���Ϣ������ΪWM_KILLFOUCS��Ϣ
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==13)           //�س���
			pMsg->message=WM_KILLFOCUS;
		
		if(pMsg->wParam==27)      //ESC��
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
	
	//�õ������ڣ���֪ͨ�����ڽ����༭����
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

	//�ı�����
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
	wcscpy(logfont.lfFaceName,_T("����"));

	m_font.DeleteObject();
	if(m_font.CreateFontIndirectW(&logfont))
		SetFont(&m_font);
	return 0;

}

//��ʼ����Ͽ��б�
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
//	//�õ������ڣ���֪ͨ�����ڽ����༭����
//	CTechValListCtrl *parent=(CTechValListCtrl*)GetParent();
//	if(parent&&!bMatching)
//	{
//		parent->MyEndComboBox();
//	}
//}




