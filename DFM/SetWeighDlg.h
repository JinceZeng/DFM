#pragma once
#include "afxcmn.h"
#include "TechValListCtrl.h"
#include "goldata.h"

//���������eigen3.3
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

// CSetWeighDlg dialog

class CSetWeighDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetWeighDlg)

public:
	CSetWeighDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetWeighDlg();

// Dialog Data
	enum { IDD = IDD_SETWEIGH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTechValListCtrl m_SetWeighList;
	vector<CString> m_Lvl1TechNam;                      //��һ�㹤��ָ����
	vector<vector<CString>> m_Lvl2TechNam;              //�ڶ��㹤��ָ����
	vector<CString> m_WeighCompareInfo;                 //ָ��Ȩ�رȽ���Ϣ

	void ReadTechChart(CProductInfo &m_ProductInfo);    //��ȡ������Ȩ�ص�һ������ָ��
	void SetListItem(vector<CString>& m_Lvl1TechNam,vector<vector<CString>>& m_Lvl2TechNam);//����list��Ŀ

	afx_msg void OnBnClickedOk();

	//�������
	void ConstructCompareMat(vector<CString>& m_WeighCompareInfo);//����Ȩ�رȽ��жϾ���
	void ComputeWeigh(MatrixXd& M_S);   //��η���������Ȩ��ֵ
	vector<VectorXd> m_dA;              //�洢��η�����Ȩ������
	VectorXd m_dA1,m_dA2;
	//vector<double> m_vdMaxA;            //�������ֵ
	vector<int> m_vnCoherence;          //�ж��Ƿ�ͨ��һ���Լ���
};
