// IndexInfo1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "IndexInfo1Dlg.h"
#include "afxdialogex.h"


// CIndexInfo1Dlg dialog

IMPLEMENT_DYNAMIC(CIndexInfo1Dlg, CDialogEx)

CIndexInfo1Dlg::CIndexInfo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIndexInfo1Dlg::IDD, pParent)
{

}

CIndexInfo1Dlg::~CIndexInfo1Dlg()
{
}

void CIndexInfo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIndexInfo1Dlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CIndexInfo1Dlg message handlers
void CIndexInfo1Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	DestroyWindow();
	CDialogEx::OnClose();
	delete this;  //�ͷ��ڴ�
	/*::SendMessageA(AfxGetMainWnd(),WM_DELETEPDLG,0,0);*/
}





void CIndexInfo1Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	DrawTitleBar(&dc);
}


void CIndexInfo1Dlg::DrawTitleBar(CDC* pDC)
{
	CRect m_rectPanel;                //�ӶԻ���İ�ΧȦ
	GetDlgItem(IDC_INDEXINFO1)->GetWindowRect(&m_rectPanel);
	ScreenToClient(&m_rectPanel);

	///////////////////////////////////////////////////////////////////////////����ͼƬ
	CDC dcMem;                     //���ڻ�����ͼ���ڴ�DC
	dcMem.CreateCompatibleDC(pDC); //��������DC���������ڴ�DC 

	CBitmap bmp;                                        //�ڴ��г�����ʱͼ���λͼ 
	bmp.LoadBitmapW(IDB_INDEXINFO1);
	CBitmap* pOldmap=dcMem.SelectObject(&bmp);          //��λͼѡ����ڴ�DC

	BITMAP bm;
	bmp.GetBitmap(&bm);    //��ȡͼƬ��Ϣ

	pDC->TransparentBlt(m_rectPanel.left,m_rectPanel.top,m_rectPanel.right,m_rectPanel.bottom,    //Ҫ��ͼ��Ŀ��λ��
		&dcMem,
		0,0,bm.bmWidth,bm.bmHeight,RGB(0,0,255));                      //���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨

	dcMem.SelectObject(pOldmap);
	dcMem.DeleteDC();            //�Ͽ�DC���
	bmp.DeleteObject();         //ɾ��λͼ 
}