#pragma once
#include "afxcmn.h"
#include "TechValListCtrl.h"
#include "goldata.h"

// CProductStep5Dlg dialog

class CProductStep5Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep5Dlg)

public:
	CProductStep5Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep5Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP5_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//////////////////////////��һҳ����һҳ�Ĳ���
	DWORD OnWizardActive();     //����ִ�г�ʼ������

	////////////////////////��ǰҳ������һҳ
	DWORD OnWizardNext();       //���Լ��鲢���浱ǰ����

	///////////////////////��ǰҳ������һҳ����CListCtrl���Զ�������Ϣ������ֻ���� OnWizardNext������Ϣ���ݵ���һҳ��
	DWORD OnWizardPrevious();   //���Լ�����һ���������ñ���
	CTechValListCtrl m_EconomyList;
	vector<CString> m_Lvl3TechID;              //�����㹤��ָ��ID
	vector<vector<CString>> m_IndexValInfo;    //�洢ָ�����ֵ�������Ͷ�Ӧ��ֵ������֮��ƥ�䣨���η������ݿ�������ջ������ 
	vector<CTechChartItem> m_ListCtrlItem;     //�洢List��Ŀ

	vector<CLowValItem> m_LowValItem;          //�洢�ͷ���
	int m_LowValItemNum;                     //��¼�ͷ�����Ŀ��
	void SaveLowValItem(vector<CTechChartItem>& m_ListCtrlItem);   //����ͷ���

	void ReadTechChart(CProductInfo &m_ProductInfo);              //��ȡ���ձ�
	void ShowListCtrl();                                          //��ʾ���ֱ�
	void SetListItem(vector<CTechChartItem> &m_ListCtrlItem);     //����list��Ŀ

	afx_msg LRESULT OnSetIndexVal(WPARAM wParam,LPARAM lParam);//����ָ��÷�
	virtual BOOL OnInitDialog();
};
