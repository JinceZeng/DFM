#pragma once
#include "afxwin.h"
#include <vector>
using std::vector;

#include "ProductStep0Dlg.h"
#include "ProductStep1Dlg.h"
#include "ProductStep2Dlg.h"
#include "ProductStep3Dlg.h"
#include "ProductOutDlg.h"

// CProductNewDlg dialog

class CProductNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductNewDlg)

public:
	CProductNewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductNewDlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTNEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
public:
	vector<CDialogEx*> m_pPageList;   //��¼���ӶԻ���
	int m_nCurrentPage;               //��ǰ��ʾҳ
	bool bInfoWrited;                 //��Ʒ��Ϣ�Ƿ���д��
	CRect m_rectPanel;                //�ӶԻ���İ�ΧȦ
	void ShowPage(UINT nPos);         //��ʾnPosҳ���0��ʼ����
	void SetWizButton(UINT nPos);     //����ҳ��������ð�ť״̬
	void SetTextShow(UINT nPos);      //����ҳ����������ı���ʾ 
	afx_msg void OnBnClickedEvalpre();   //ǰһ��
	afx_msg void OnBnClickedEvalnext();  //��һ��
	afx_msg void OnBnClickedEvalin();    //��������
};
