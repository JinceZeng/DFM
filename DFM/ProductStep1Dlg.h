#pragma once


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
};

