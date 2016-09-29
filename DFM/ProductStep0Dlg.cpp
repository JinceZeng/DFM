// ProductStep0Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep0Dlg.h"
#include "afxdialogex.h"


// CProductStep0Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep0Dlg, CDialogEx)

CProductStep0Dlg::CProductStep0Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep0Dlg::IDD, pParent)
	, m_ProductName(_T(""))
	, m_ProductNum(_T(""))
	, m_ProductSub(_T(""))
	, m_EvalTypeVal(0)
	, m_TypeInfo(_T(""))
	, m_isEval(0)
{
}

CProductStep0Dlg::~CProductStep0Dlg()
{
}

void CProductStep0Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PRODUCTNAME, m_ProductName);
	DDX_Text(pDX, IDC_PRODUCTNUM, m_ProductNum);
	DDX_Text(pDX, IDC_PRODUCTSUB, m_ProductSub);
	DDX_Control(pDX, IDC_COMBO_EVALTYPE, m_cmbEvalType);
	DDX_CBIndex(pDX, IDC_COMBO_EVALTYPE, m_EvalTypeVal);
	DDX_Text(pDX, IDC_TYPEINFO, m_TypeInfo);
}


BEGIN_MESSAGE_MAP(CProductStep0Dlg, CDialogEx)
END_MESSAGE_MAP()


// CProductStep0Dlg message handlers


BOOL CProductStep0Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化下拉菜单
	CString sql = CString("select * from EvalModelInfo");
	m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
	while (!m_pRs->adoEOF)
	{
		CString str = (CString)(m_pRs->GetCollect("EvalModelNam")); 
		m_cmbEvalType.AddString(str);
		m_pRs->MoveNext();
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}




//激活执行初始化操作
DWORD CProductStep0Dlg::OnWizardActive()
{
	//接收外界信息,可以完成一些初始化工作

	ShowWindow(SW_SHOW);
	return 0;
}

//可以检验并保存当前工作
DWORD CProductStep0Dlg::OnWizardNext()
{
	//保存当前工作，传递信息
	UpdateData(TRUE);
	if(m_ProductName==""||m_ProductNum==""||m_ProductSub==""||m_EvalTypeVal==-1||m_TypeInfo=="")
	{
		AfxMessageBox(CString("请先完成产品信息输入"));
		return -1;
	}
	//遍历数据库避免保存相同产品信息
	CString sql=CString("select * from ProductInfo where ProductNam ='")+m_ProductName+CString("' and ProductNum='")+m_ProductNum+"'";
	m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
	int nCount=0;
	while (!m_pRs->adoEOF)
	{
		nCount++;
		m_pRs->MoveNext();

	}
	if(nCount>0){
		AfxMessageBox(CString("数据库已存在此产品信息"));
		return -1;
	}
	//若没有重复信息，则将产品信息插入数据库中(access插入数据注意设置字段索引可重复)
	else
	{
	CTime time;
	time = CTime::GetCurrentTime();
	CString str_Time = time.Format("%Y-%m-%d %H:%M:%S");
	CString str_EvalType;
	str_EvalType=(CString)(char *)(_bstr_t)(m_EvalTypeVal+1);
	CString str,str_IsEval;
	str_IsEval=(CString)(char *)(_bstr_t)(m_isEval);
	//str_IsEval=m_ProductName+CString("_")+str;
	try
	{
	theApp.m_pConnect->Execute((_bstr_t)(CString("insert into ProductInfo(ProductNam,ProductNum,ProductSub,EvalModelID,EvalTypeIntro,IsEval,EvalTime) values('")
		+m_ProductName+"','"+m_ProductNum+"','"+m_ProductSub+"',"+str_EvalType+",'"+m_TypeInfo+"',"+str_IsEval+",'"+str_Time+("')")) , NULL, adCmdText);   //insert操作时数据库中对应字符型需加‘’
	}
	catch(_com_error e)
	{
		CString temp;
		temp.Format(e.Description());
		AfxMessageBox(temp);
		return -1;
	}
	////删除控件状态
	//m_ProductName= "";
	//m_ProductNum = "";
	//m_ProductSub = "";
	//m_cmbEvalType.Clear();
	//m_EvalTypeVal=-1;
	//m_TypeInfo="";
	//UpdateData(false);
	AfxMessageBox(CString("新建评分保存成功"));

	ShowWindow(SW_HIDE);
	return 0;
	}
}

//可以检验上一步工作（不会被调用）
DWORD CProductStep0Dlg::OnWizardPrevious()
{ 
	ShowWindow(SW_HIDE);
	return 0;
}