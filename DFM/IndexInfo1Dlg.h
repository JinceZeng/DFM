#pragma once
//#define WM_DELETEPDLG WM_USER+7 
// CIndexInfo1Dlg dialog

class CIndexInfo1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIndexInfo1Dlg)

public:
	CIndexInfo1Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIndexInfo1Dlg();

// Dialog Data
	enum { IDD = IDD_INDEXINFO1_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	void DrawTitleBar(CDC* pDC);         //具体重绘标题区域
	afx_msg void OnPaint();
};
