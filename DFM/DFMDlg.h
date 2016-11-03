
// DFMDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "EasySize.h"
#include "PInfoListCtrl.h"


#define WM_DELETEDATA WM_USER+2    //删除某一条产品信息
#define WM_UPDATELIST WM_USER+3    //刷新list

// CDFMDlg 对话框
class CDFMDlg : public CDialogEx
{
	DECLARE_EASYSIZE
// 构造
public:
	CDFMDlg(CWnd* pParent = NULL);	// 标准构造函数
	//状态栏相关变量
	int index1,   //标识面板索引
		index2,
		index3,
		nWidth1,  //保存IDS_INDICATOR_MESSAGE, IDS_INDICATOR_TIME宽度
		nWidth2,
		nWidth3;
	UINT  nID,    //用于接收面板ID
		nStyle; //用于接收面板风格

	//_RecordsetPtr m_pRs;
	CStatusBar m_Statusbar;

// 对话框数据
	enum { IDD = IDD_DFM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuLogin();//登录菜单
	afx_msg void OnMenuAbout();//关于菜单
	afx_msg void OnMenuPsw();  //修改密码菜单
	afx_msg void OnEvalnew();  //新建评价

	afx_msg LRESULT OnDeleteData(WPARAM wParam,LPARAM lParam);//自定义消息删除某一条产品信息
	afx_msg LRESULT OnUpdateList(WPARAM wParam,LPARAM lParam);//自定义消息刷新list

	CPInfoListCtrl m_ProductInfoList;
	void ChangeStyle(CPInfoListCtrl &m_ListCtrl);//改变list风格
    void UpdateListCtrl();    //list数据刷新
};
