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
	//////////////////////////上一页到下一页的操作
	DWORD OnWizardActive();     //激活执行初始化操作

	////////////////////////当前页进入下一页
	DWORD OnWizardNext();       //可以检验并保存当前工作

	///////////////////////当前页进入上一页（由CListCtrl能自动保存信息，所以只需在 OnWizardNext保存信息传递到下一页）
	DWORD OnWizardPrevious();   //可以检验上一步工作不用保存
	CTechValListCtrl m_MatInfoList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedInputmat();//导入材料表

	//用于连接Excel
	void ReadMatChart(CString excelFile,int sheetIndex,bool header);//读取excel表
	vector<vector<CString>> str_AllItem;//用于存储excel表信息
	void SetListItem(vector<vector<CString>>& str_AllItem);//设置list条目

};
