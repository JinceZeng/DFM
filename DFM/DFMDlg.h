
// DFMDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "EasySize.h"
#include "PInfoListCtrl.h"


#define WM_DELETEDATA WM_USER+2    //ɾ��ĳһ����Ʒ��Ϣ
#define WM_UPDATELIST WM_USER+3    //ˢ��list

// CDFMDlg �Ի���
class CDFMDlg : public CDialogEx
{
	DECLARE_EASYSIZE
// ����
public:
	CDFMDlg(CWnd* pParent = NULL);	// ��׼���캯��
	//״̬����ر���
	int index1,   //��ʶ�������
		index2,
		index3,
		nWidth1,  //����IDS_INDICATOR_MESSAGE, IDS_INDICATOR_TIME���
		nWidth2,
		nWidth3;
	UINT  nID,    //���ڽ������ID
		nStyle; //���ڽ��������

	//_RecordsetPtr m_pRs;
	CStatusBar m_Statusbar;

// �Ի�������
	enum { IDD = IDD_DFM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuLogin();//��¼�˵�
	afx_msg void OnMenuAbout();//���ڲ˵�
	afx_msg void OnMenuPsw();  //�޸�����˵�
	afx_msg void OnEvalnew();  //�½�����

	afx_msg LRESULT OnDeleteData(WPARAM wParam,LPARAM lParam);//�Զ�����Ϣɾ��ĳһ����Ʒ��Ϣ
	afx_msg LRESULT OnUpdateList(WPARAM wParam,LPARAM lParam);//�Զ�����Ϣˢ��list

	CPInfoListCtrl m_ProductInfoList;
	void ChangeStyle(CPInfoListCtrl &m_ListCtrl);//�ı�list���
    void UpdateListCtrl();    //list����ˢ��
};
