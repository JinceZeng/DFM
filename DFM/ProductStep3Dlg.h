#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TechValListCtrl.h"
#include "goldata.h"
#include "IndexInfo1Dlg.h"


// CProductStep3Dlg dialog

class CProductStep3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep3Dlg)

public:
	CProductStep3Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep3Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP3_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	//////////////////////////��һҳ����һҳ�Ĳ���
	DWORD OnWizardActive();     //����ִ�г�ʼ������

	////////////////////////��ǰҳ������һҳ
	DWORD OnWizardNext();       //���Լ��鲢���浱ǰ����

	///////////////////////��ǰҳ������һҳ����CListCtrl���Զ�������Ϣ������ֻ���� OnWizardNext������Ϣ���ݵ���һҳ��
	DWORD OnWizardPrevious();   //���Լ�����һ���������ñ���

	CEdit m_IndexInfoTxt;                      //�༭����Ʊ�������ʾ����ϸ��
	CFont m_editFont;                          //����
	CTechValListCtrl m_ImpactVibValList;       //listctrl���Ʊ���
	vector<CString> m_Lvl3TechID;              //�����㹤��ָ��ID
	vector<vector<CString>> m_IndexValInfo;    //�洢ָ�����ֵ�������Ͷ�Ӧ��ֵ������֮��ƥ�䣨���η������ݿ�������ջ������ 
	vector<CTechChartItem> m_ListCtrlItem;     //�洢List��Ŀ
	vector<CString> m_IndexInfo;               //�洢ָ������˵��
	CIndexInfo1Dlg *pDlg;                      //���ڴ�����ģ̬�Ի���               

	void ReadTechChart(CProductInfo &m_ProductInfo);              //��ȡ���ձ�
	void ShowListCtrl();                                          //��ʾ���ֱ�
	void SetListItem(vector<CTechChartItem> &m_ListCtrlItem);     //����list��Ŀ

	afx_msg LRESULT OnSetIndexInfo(WPARAM wParam,LPARAM lParam);  //����ָ������˵��
	//afx_msg LRESULT OnDeletepDlg(WPARAM wParam,LPARAM lParam);    //�ͷ�pDlg��Աָ��(��֪����ô��ȡ�����ھ��û��)
	afx_msg LRESULT OnSetIndexVal(WPARAM wParam,LPARAM lParam);//����ָ��÷�
};
