#pragma once


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
};
