#pragma once
#include "afxwin.h"
#include "goldata.h"

#define WM_UPDATEDATA WM_USER+1    //���¶Ի���ؼ�

// CProductStep0Dlg dialog

class CProductStep0Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep0Dlg)

public:
	CProductStep0Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep0Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP0_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRs;
	CString m_ProductName;  //��Ʒ��
	CString m_ProductNum;   //��Ʒ���
	CString m_ProductSub;   //��Ʒ�������
	CComboBox m_cmbEvalType;//combo���Ʊ���
	int m_EvalTypeVal;      //combo���Ʊ���
	CString str_EvalType;   //��������ID
	CString m_TypeInfo;     //�������ͽ���
	int m_isEval;           //�Ƿ��Ѿ�����
	CProductInfo m_ProductInfo;//�ṹ�屣���Ʒ��Ϣ
	virtual BOOL OnInitDialog();
public:
	//��Ӧ���Ի��򼸸���ť����Ϣ
	DWORD OnWizardActive();     //����ִ�г�ʼ������
	DWORD OnWizardNext();       //���Լ��鲢���浱ǰ����
	DWORD OnWizardPrevious();   //���Լ�����һ�����������ñ���

	afx_msg LRESULT OnUpdateData(WPARAM wParam,LPARAM lParam);//�Զ�����Ϣ���¿ؼ���Ϣ
	void SaveProductInfo();    //�����Ʒ��Ϣ
};
