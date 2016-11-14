// ChoosePathDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ChoosePathDlg.h"
#include "afxdialogex.h"


// CChoosePathDlg dialog

IMPLEMENT_DYNAMIC(CChoosePathDlg, CDialogEx)

CChoosePathDlg::CChoosePathDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChoosePathDlg::IDD, pParent)
	, m_editPathTxt(_T(""))
{

}

CChoosePathDlg::~CChoosePathDlg()
{
}

void CChoosePathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
	DDX_Text(pDX, IDC_EDIT_PATH, m_editPathTxt);
}


BEGIN_MESSAGE_MAP(CChoosePathDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VIEW, &CChoosePathDlg::OnBnClickedButtonView)
	ON_BN_CLICKED(IDCANCEL, &CChoosePathDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CChoosePathDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CChoosePathDlg message handlers


void CChoosePathDlg::OnBnClickedButtonView()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, (CString)("xls"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(CString)("Excel文件(*.xls)|*.xls|Excel文件(*.xlsx)|*.xlsx||"), NULL);

	if (dlg.DoModal() == IDOK){
		CString str = dlg.GetPathName();
		m_editPath.SetWindowText(str);

	}
}



void CChoosePathDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CChoosePathDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//UpdateData();
	//CString str;
	//m_editPath.GetWindowText(str);
	//if (str.IsEmpty()){
	//	AfxMessageBox(CString("请选择导入文件!"));
	//	return;
	//}
	CDialogEx::OnOK();
}
