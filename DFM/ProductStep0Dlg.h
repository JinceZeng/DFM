#pragma once
#include "afxwin.h"



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
	CString m_ProductName;
	CString m_ProductNum;
	CString m_ProductSub;
	CComboBox m_cmbEvalType;
	int m_EvalTypeVal;
	CString m_TypeInfo;
	int m_isEval;
	virtual BOOL OnInitDialog();
public:
	//��Ӧ���Ի��򼸸���ť����Ϣ
	DWORD OnWizardActive();     //����ִ�г�ʼ������
	DWORD OnWizardNext();       //���Լ��鲢���浱ǰ����
	DWORD OnWizardPrevious();   //���Լ�����һ�����������ñ���
};
