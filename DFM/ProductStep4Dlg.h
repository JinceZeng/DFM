#pragma once


// CProductStep4Dlg dialog

class CProductStep4Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductStep4Dlg)

public:
	CProductStep4Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductStep4Dlg();

// Dialog Data
	enum { IDD = IDD_PRODUCTSTEP4_DLG };

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
