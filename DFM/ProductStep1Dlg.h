#pragma once
#include "TechValListCtrl.h"
#include "goldata.h"

// CProductStep1Dlg dialog





class CProductStep1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep1Dlg)

public:
	CProductStep1Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep1Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP1_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//��Ӧ���Ի��򼸸���ť����Ϣ
	DWORD OnWizardActive();     //����ִ�г�ʼ������
	DWORD OnWizardNext();       //���Լ��鲢���浱ǰ����
	DWORD OnWizardPrevious();   //���Լ�����һ�����������ñ���
public:
	virtual BOOL OnInitDialog();
	CTechValListCtrl m_TechValList;            //listctrl���Ʊ���
	vector<CString> m_Lvl3TechID;              //�����㹤��ָ��ID
	vector<vector<CString>> m_IndexValInfo;    //�洢ָ�����ֵ������Ϣ������֮��ƥ�䣨���η������ݿ�������ջ������ 
	vector<CTechChartItem> m_ListCtrlItem;     //�洢List��Ŀ

	void ReadTechChart(CProductInfo &m_ProductInfo);  //��ȡ���ձ�
	void ShowListCtrl();                         //��ʾ���ֱ�
	void SetListItem(vector<CTechChartItem> &m_ListCtrlItem);     //����list��Ŀ

	afx_msg LRESULT OnSetIndexVal(WPARAM wParam,LPARAM lParam);//����ָ��÷�
	afx_msg LRESULT OnIndexMatch(WPARAM wParam,LPARAM lParam); //�����������ƥ�����

	BOOL m_bLegal;                                    //������������
	//void DeleteStructInfo();      //����һҳ�ṹ��������ʱ��Ҫɾ��ԭ�ṹ,�ᱻ�ظ�ʹ��
};

