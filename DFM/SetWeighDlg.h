#pragma once
#include "afxcmn.h"
#include "TechValListCtrl.h"
#include "goldata.h"

//矩阵运算库eigen3.3
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
	vector<CString> m_Lvl1TechNam;                      //第一层工艺指标名
	vector<vector<CString>> m_Lvl2TechNam;              //第二层工艺指标名
	vector<CString> m_WeighCompareInfo;                 //指标权重比较信息

	void ReadTechChart(CProductInfo &m_ProductInfo);    //读取需设置权重的一、二级指标
	void SetListItem(vector<CString>& m_Lvl1TechNam,vector<vector<CString>>& m_Lvl2TechNam);//设置list条目

	afx_msg void OnBnClickedOk();

	//计算相关
	void ConstructCompareMat(vector<CString>& m_WeighCompareInfo);//构建权重比较判断矩阵
	void ComputeWeigh(MatrixXd& M_S);   //层次分析法计算权重值
	vector<VectorXd> m_dA;              //存储层次分析法权重向量
	VectorXd m_dA1,m_dA2;
	//vector<double> m_vdMaxA;            //最大特征值
	vector<int> m_vnCoherence;          //判断是否通过一致性检验
};
