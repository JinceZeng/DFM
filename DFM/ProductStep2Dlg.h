#pragma once
#include "afxcmn.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "TechValListCtrl.h"
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "adoEOF") rename("BOF", "adoBOF")
using namespace std;

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
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedInputmat();//������ϱ�

	//��������Excel
	void ReadMatChart(CString excelFile,int sheetIndex,bool header);//��ȡexcel��
	vector<vector<CString>> str_AllItem;//���ڴ洢excel����Ϣ
	void SetListItem(vector<vector<CString>>& str_AllItem);//����list��Ŀ

};
