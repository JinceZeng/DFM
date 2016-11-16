#pragma once
#include "goldata.h"
#include "afxcmn.h"
#include "TechValListCtrl.h"
// CProductStep6Dlg dialog

class CProductStep6Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep6Dlg)

public:
	CProductStep6Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep6Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP6_DLG };

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
	virtual BOOL OnInitDialog();
	CTechValListCtrl m_TechMaturyList;
	vector<vector<CString>> m_TechMaturityInfo; //�洢���ճ����������Ϣ   
	vector<CString> m_TechType;                 //�洢���й������ͣ�����combo��ʼ��
	vector<CMaturyChartItem> m_ListCtrlItem;    //�洢List��Ŀ

	afx_msg LRESULT OnDeleteIndexItem(WPARAM wParam,LPARAM lParam); //ɾ��ĳ������ָ��
	afx_msg LRESULT OnAddIndexItem(WPARAM wParam,LPARAM lParam);//���ĳ������ָ��
	afx_msg LRESULT OnSetIndexVal(WPARAM wParam,LPARAM lParam);//����ָ��÷�

	void ReadTechChart();              //��ȡ���ճ����
};
