// ProductStep5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep5Dlg.h"
#include "afxdialogex.h"


// CProductStep5Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep5Dlg, CDialogEx)

CProductStep5Dlg::CProductStep5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep5Dlg::IDD, pParent)
	,m_LowValItemNum(0)
{
	m_ListCtrlItem.clear();
	m_Lvl3TechID.clear();
	m_IndexValInfo.clear();
}

CProductStep5Dlg::~CProductStep5Dlg()
{
	vector<CString>().swap(m_Lvl3TechID);
	vector<CTechChartItem>().swap(m_ListCtrlItem);
	vector<vector<CString>>().swap(m_IndexValInfo);
	vector<CLowValItem>().swap(m_LowValItem);
}

void CProductStep5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ECONOMY, m_EconomyList);
}


BEGIN_MESSAGE_MAP(CProductStep5Dlg, CDialogEx)
	ON_MESSAGE(WM_SETINDEXVAL,&CProductStep5Dlg::OnSetIndexVal)
END_MESSAGE_MAP()


// CProductStep5Dlg message handlers
/////////////////////////////////////激活当前页(从上一页或下一页转到本页都会调用)
//由于只有一个结构信息，利用CListCtl的缓存可以保存信息，不用自己更新CListCtrl
DWORD CProductStep5Dlg::OnWizardActive()
{
	//接受信息输入，完成初始化工作
	//m_LowValItem.clear();
	//m_LowValItemNum=0;      //窗口激活就重新计数
	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////前往下一页
//可以检验并保存当前工作,返回-1不切换，返回0切换
DWORD CProductStep5Dlg::OnWizardNext()
{
	//保存当前工作，传递信息
	if(m_EconomyList.m_bEditing==TRUE)
	{
		MessageBox(_T("错误:列表控件处于编辑状态"));
		return -1;
	}
	for (int i=0;i<m_ListCtrlItem.size();++i)
	{
		CString str=m_EconomyList.GetItemText(i,3);
		if(str==CString(""))
		{
			AfxMessageBox(CString("评分项未完成"));
			return -1;
		}
	}
	SaveLowValItem(m_ListCtrlItem);   //若m_ListCtrlItem信息输入完成，则存储其中低分项

	ShowWindow(SW_HIDE);     //暂时这样写，后期加检验判断
	return 0;

}

/////////////////////////////////////////前往上一页
//可以检验上一步工作不用保存
DWORD CProductStep5Dlg::OnWizardPrevious()
{
	if(m_EconomyList.m_bEditing==TRUE)
	{
		MessageBox(_T("错误:列表控件处于编辑状态"));
		return -1;
	}
	else
	{
		//m_bLegal=FALSE;
		ShowWindow(SW_HIDE);
		return 0;
	}
}

BOOL CProductStep5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect1;
	int width1;
	m_EconomyList.GetClientRect(&rect1);
	width1=rect1.Width();

	m_EconomyList.InsertColumn(0,CString("序号"),LVCFMT_CENTER,width1/10);
	m_EconomyList.InsertColumn(1,CString("类别"),LVCFMT_CENTER,width1/10);
	m_EconomyList.InsertColumn(2,CString("评分项"),LVCFMT_CENTER,width1*3/10);
	m_EconomyList.InsertColumn(3,CString("评分项特征"),LVCFMT_CENTER,width1*2/5);
	m_EconomyList.InsertColumn(4,CString("评分值"),LVCFMT_CENTER,width1/10);


	//设置不可编辑列
	vector<int> nNoEdit;
	nNoEdit.push_back(0);               //第零列不可以编辑
	nNoEdit.push_back(1);  
	nNoEdit.push_back(2); 
	nNoEdit.push_back(3); 
	m_EconomyList.SetnNoEditList(nNoEdit);
	vector<int>().swap(nNoEdit);//释放vector

	vector<int> nComboLis;
	nComboLis.push_back(3);            //第三列有组合框控制
    m_EconomyList.SetnComboList(nComboLis);
	vector<int>().swap(nComboLis);//释放vector
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CProductStep5Dlg::ReadTechChart(CProductInfo& m_ProductInfo)
{
	_RecordsetPtr m_pRs0;
	m_Lvl3TechID.clear();
	int UpID=15;             //搜寻工艺指标（指标ID为15：制造经济性）的子项
	CString strUpID=(CString)(char *)(_bstr_t)(UpID);

	CString sql0 = CString("select * from CreateIndexTree where EvalModelID=")+m_ProductInfo.str_EvalType+CString("and TechEvalIndexUpID=")+strUpID;
	try
	{
		m_pRs0 = theApp.m_pConnect->Execute(_bstr_t(sql0), NULL, adCmdText);
	}
	catch(_com_error e)
	{
		CString temp;
		temp.Format(e.Description());
		AfxMessageBox(temp);
	}
	while (!m_pRs0->adoEOF)
	{

		CString str = (CString)(m_pRs0->GetCollect("TechEvalIndexID"));
		m_Lvl3TechID.push_back(str);
		m_pRs0->MoveNext();

	}
}



void CProductStep5Dlg::ShowListCtrl()
{
	_RecordsetPtr m_pRs,m_pRs2;
	m_ListCtrlItem.clear();
	m_IndexValInfo.clear();

	CTechChartItem m_OneItem;//每条list的信息
	int nItem=1;             //序号
	for (int i=0;i<m_Lvl3TechID.size();i++)
	{
		CString strItem;
		strItem.Format(CString("%d"),nItem);
		CString sql = CString("select * from TechEvalIndex where TechEvalIndexID=")+m_Lvl3TechID[i];
		try
		{
			m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
			CString strTechNam=(CString)(m_pRs->GetCollect("TechEvalIndexNam"));
			CString strClassify=(CString)(m_pRs->GetCollect("TechClassify"));
			//CString strIndexInfo=(CString)(m_pRs->GetCollect("TechEvalIndexInfo"));

			//m_IndexInfo.push_back(strIndexInfo);

			vector<CString> m_ValComboStr;  //用于存储评分combo字符
			vector<CString> vTemp;          //辅助存储评分项和对应分值
			CString sql2 = CString("select * from EvalIndexVal where TechEvalIndexID=")+m_Lvl3TechID[i];
			m_pRs2 = theApp.m_pConnect->Execute(_bstr_t(sql2), NULL, adCmdText);
			while(!m_pRs2->adoEOF)
			{
				CString strValInfo=(CString)(m_pRs2->GetCollect("TechEvalIndexValInfo"));
				CString strVal=(CString)(m_pRs2->GetCollect("TechDeductVal"));
				m_ValComboStr.push_back(strValInfo);   //用于combo初始化

				CString str=strValInfo+CString(":")+strVal;//为避免用三维vector，所以这样表示
				vTemp.push_back(str);

				m_pRs2->MoveNext();
			}

			m_IndexValInfo.push_back(vTemp);
			vector<CString>().swap(vTemp);//释放临时vector


			//每条list信息
			m_OneItem.nItem=strItem;
			m_OneItem.m_Classify=strClassify;
			m_OneItem.m_TechEvalIndex=strTechNam;
			m_OneItem.m_ValComboStr=m_ValComboStr;

			vector<CString>().swap(m_ValComboStr);//释放vector
			nItem++;

			m_ListCtrlItem.push_back(m_OneItem);//依次存入list的每行信息
		}

		catch(_com_error e)
		{
			CString temp;
			temp.Format(e.Description());
			AfxMessageBox(temp);
		}
	}
	SetListItem(m_ListCtrlItem);
}



void CProductStep5Dlg::SetListItem(vector<CTechChartItem>& m_ListCtrlItem)
{
	m_EconomyList.DeleteAllItems();
	for (int i=0;i<m_ListCtrlItem.size();i++)
	{
		m_EconomyList.InsertItem(i,m_ListCtrlItem[i].nItem);
		m_EconomyList.SetItemText(i,1,m_ListCtrlItem[i].m_Classify);
		m_EconomyList.SetItemText(i,2,m_ListCtrlItem[i].m_TechEvalIndex);
		m_EconomyList.SetComboString(m_ListCtrlItem[i].m_ValComboStr);   //将combo字符赋给listctrl扩展类中的m_strlisCombo用于combo初始化
	}
}


LRESULT CProductStep5Dlg::OnSetIndexVal(WPARAM wParam,LPARAM lParam)
{
	//对应分值的输入
	CString strValInfo=m_EconomyList.GetItemText(wParam,3);

	CStringArray strArrayNam,strArrayVal;
	//提取指标变量描述
	for (int i=0;i<m_IndexValInfo[wParam].size();++i)
	{
		strArrayNam.Add(m_IndexValInfo[wParam][i].Left(m_IndexValInfo[wParam][i].Find(':')));
		strArrayVal.Add(m_IndexValInfo[wParam][i].Right(m_IndexValInfo[wParam][i].GetLength()-m_IndexValInfo[wParam][i].Find(':')-1));//提取指标评分项评分

	}

	//进行匹配选取对应评分
	int j=0;
	for (;j<strArrayNam.GetCount();++j)
	{
		if(strArrayNam[j]==strValInfo) break;
	}
	CString strDeductVal=strArrayVal[j];//提取评分
	m_EconomyList.SetItemText(wParam,4,strDeductVal);                    //设置分值

	m_ListCtrlItem[wParam].m_ComboStrChoose=strValInfo;                  //存储所选的评分项
	m_ListCtrlItem[wParam].m_IndexScore=strDeductVal;                    //存储分值，用于后期模糊综合分析

	return 0;
}



//存储低分项(待m_ListCtrlItem赋值完成后调用)
void CProductStep5Dlg::SaveLowValItem(vector<CTechChartItem>& m_ListCtrlItem)
{
	m_LowValItem.clear();
	m_LowValItemNum=0;
	for (int i=0;i<m_ListCtrlItem.size();++i)
	{
		CString strDeductVal=m_ListCtrlItem[i].m_IndexScore;//提取评分
		CLowValItem OneLowValItem;
		int nDeductVal= _ttoi(strDeductVal);
		if (nDeductVal<0)
		{
			CString str;
			str.Format(CString("%d"),m_LowValItemNum+1);
			OneLowValItem.m_Item=str;
			OneLowValItem.m_ChartNam=CString("制造经济性表");
			OneLowValItem.m_Classify=m_ListCtrlItem[i].m_Classify;
			OneLowValItem.m_TechEvalIndex=m_ListCtrlItem[i].m_TechEvalIndex;
			OneLowValItem.m_IndexScore=m_ListCtrlItem[i].m_IndexScore;


			CStringArray strArrayNam,strArrayVal;
			for (int j=0;j<m_IndexValInfo[i].size();++j)
			{
				strArrayNam.Add(m_IndexValInfo[i][j].Left(m_IndexValInfo[i][j].Find(':')));   //提取指标评分项名
				strArrayVal.Add(m_IndexValInfo[i][j].Right(m_IndexValInfo[i][j].GetLength()-m_IndexValInfo[i][j].Find(':')-1));//提取指标评分项评分
			}

			int k=0;      //获取评分项评分为0，即不扣分的项作为建议
			for (;k<strArrayVal.GetCount();++k)
			{
				if(strArrayVal[k]==CString("0")) break;
			}
			OneLowValItem.m_LowValAdvice=strArrayNam[k];

			m_LowValItem.push_back(OneLowValItem);

			++m_LowValItemNum;
		}
	}
}