#pragma once


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
	//////////////////////////��һҳ����һҳ�Ĳ���
	DWORD OnWizardActive();     //����ִ�г�ʼ������

	////////////////////////��ǰҳ������һҳ
	DWORD OnWizardNext();       //���Լ��鲢���浱ǰ����

	///////////////////////��ǰҳ������һҳ����CListCtrl���Զ�������Ϣ������ֻ���� OnWizardNext������Ϣ���ݵ���һҳ��
	DWORD OnWizardPrevious();   //���Լ�����һ���������ñ���
};
