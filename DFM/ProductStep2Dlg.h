#pragma once
#include "afxcmn.h"
#include "goldata.h"
#include "TechValListCtrl.h"

// CProductStep2Dlg dialog

class CProductStep2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep2Dlg)

public:
	CProductStep2Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep2Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP2_DLG };

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

	CTechValListCtrl m_MatInfoList;
	vector<CMatChartItem> m_ListCtrlItem;//�洢List��Ŀ

	vector<CLowValItem> m_LowValItem;          //�洢�ͷ���
	int m_LowValItemNum;                     //��¼�ͷ�����Ŀ��
	void SaveLowValItem(vector<CMatChartItem>& m_ListCtrlItem);   //����ͷ���

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedInputmat();//������ϱ�

	//��������Excel
	void ReadMatChart(CString excelFile,int sheetIndex,bool header);//��ȡexcel��

	void SetListItem(vector<vector<CString>>& str_AllItem);         //����list��Ŀ
	void MatchMatVal(vector<CMatChartItem>& m_ListCtrlItem);        //ƥ����ϵ÷�

	

};
