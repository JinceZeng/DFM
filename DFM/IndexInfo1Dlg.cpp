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
	delete this;  //释放内存
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
	CRect m_rectPanel;                //子对话框的包围圈
	GetDlgItem(IDC_INDEXINFO1)->GetWindowRect(&m_rectPanel);
	ScreenToClient(&m_rectPanel);

	///////////////////////////////////////////////////////////////////////////加载图片
	CDC dcMem;                     //用于缓冲作图的内存DC
	dcMem.CreateCompatibleDC(pDC); //依附窗口DC创建兼容内存DC 

	CBitmap bmp;                                        //内存中承载临时图象的位图 
	bmp.LoadBitmapW(IDB_INDEXINFO1);
	CBitmap* pOldmap=dcMem.SelectObject(&bmp);          //将位图选择进内存DC

	BITMAP bm;
	bmp.GetBitmap(&bm);    //获取图片信息

	pDC->TransparentBlt(m_rectPanel.left,m_rectPanel.top,m_rectPanel.right,m_rectPanel.bottom,    //要贴图的目标位置
		&dcMem,
		0,0,bm.bmWidth,bm.bmHeight,RGB(0,0,255));                      //将内存DC上的图象拷贝到前台

	dcMem.SelectObject(pOldmap);
	dcMem.DeleteDC();            //断开DC句柄
	bmp.DeleteObject();         //删除位图 
}