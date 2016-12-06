#pragma once
#include "afxwin.h"
#include "goldata.h"

//���������eigen3.3
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;


#include "ProductStep0Dlg.h"
#include "ProductStep1Dlg.h"
#include "ProductStep2Dlg.h"
#include "ProductStep3Dlg.h"
#include "ProductStep4Dlg.h"
#include "ProductStep5Dlg.h"
#include "ProductStep6Dlg.h"
#include "SetWeighDlg.h"
#include "ProductOutDlg.h"
#include "btnst.h"

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
	CString strProductID;             //list��ȡ�Ĳ�ƷID,�˴�ΪCString��
	CRect m_rectPanel;                //�ӶԻ���İ�ΧȦ
	void ShowPage(UINT nPos);         //��ʾnPosҳ���0��ʼ����
	void SetWizButton(UINT nPos);     //����ҳ��������ð�ť״̬
	void SetTextShow(UINT nPos);      //����ҳ����������ı���ʾ 

	afx_msg void OnBnClickedEvalpre();   //ǰһ��
	afx_msg void OnBnClickedEvalnext();  //��һ��
	afx_msg void OnBnClickedEvalin();    //��������

	//״̬��ʾ
	CStatic m_csCaption;
	CButtonST m_btnChart0;
	CButtonST m_btnChart1;
	CButtonST m_btnChart2;
	CButtonST m_btnChart3;
	CButtonST m_btnChart4;
	CButtonST m_btnChart5;
	CButtonST m_btnChart6;


	//�������
	vector<CString> m_Lvl1TechNam;                      //��һ�㹤��ָ����
	vector<vector<CString>> m_Lvl2TechNam;              //�ڶ��㹤��ָ����
	RowVectorXd m_dB1; //������������ۼ���������
	RowVectorXd m_dB2; ////����ָ������ۼ���������
	VectorXd m_dC1; //һ��ָ������ֵ
	VectorXd m_dC2; //����ָ������ֵ
	double m_W;//��������ֵ

	void GetIndexVal(VectorXd& dA1,VectorXd& dA2);                   //��ȡָ������
	double MinVal(vector<double>& IndexVal);                         //ȡ��С�۷�

	//�����ʾ���
	vector<CString>& SetResultVal(vector<CString>& m_ItemVal);      //���۽�����������ʾ��
	vector<CString> m_ItemVal;            //��������ʾֵ
	vector<CLowValItem> m_LowValItem; //����ͷ���Ľ����
	vector<CIndexValItem> m_IndexVal;   //����ָ��÷�
	void SaveResultInfo(vector<CLowValItem>& m_LowValItem,vector<CIndexValItem>& m_IndexVal);          //��m_LowValItem��m_IndexVal��ֵ

};
