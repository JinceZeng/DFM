#pragma once


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
};
