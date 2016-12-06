// ProductStep2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "ProductStep2Dlg.h"
#include "afxdialogex.h"
#include "ChoosePathDlg.h"


// CProductStep2Dlg dialog

IMPLEMENT_DYNAMIC(CProductStep2Dlg, CDialogEx)

CProductStep2Dlg::CProductStep2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductStep2Dlg::IDD, pParent)
	,m_LowValItemNum(0)
{
	m_ListCtrlItem.clear();
}

CProductStep2Dlg::~CProductStep2Dlg()
{
	vector<CMatChartItem>().swap(m_ListCtrlItem);
	vector<CLowValItem>().swap(m_LowValItem);

}

void CProductStep2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAT, m_MatInfoList);
}


BEGIN_MESSAGE_MAP(CProductStep2Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_INPUTMAT, &CProductStep2Dlg::OnBnClickedInputmat)
END_MESSAGE_MAP()


// CProductStep2Dlg message handlers




BOOL CProductStep2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//将列表控件先初始化,插入表头
	CRect rect1;
	int width1;
	m_MatInfoList.GetClientRect(&rect1);
	width1=rect1.Width();

	m_MatInfoList.InsertColumn(0,CString("位号"),LVCFMT_CENTER,width1/10);
	m_MatInfoList.InsertColumn(1,CString("代号"),LVCFMT_CENTER,width1*3/10);
	m_MatInfoList.InsertColumn(2,CString("材料名称"),LVCFMT_CENTER,width1*3/10);
	m_MatInfoList.InsertColumn(3,CString("数量"),LVCFMT_CENTER,width1/10);
	m_MatInfoList.InsertColumn(4,CString("备注"),LVCFMT_CENTER,width1/5);


	//设置不可编辑列
	vector<int> nNoEdit;
	nNoEdit.push_back(0);               //第零列不可以编辑
	nNoEdit.push_back(1);  
	nNoEdit.push_back(2);  
	nNoEdit.push_back(3);
	nNoEdit.push_back(4);  
	m_MatInfoList.SetnNoEditList(nNoEdit);
	vector<int>().swap(nNoEdit);//释放vector


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////激活当前页(从上一页或下一页转到本页都会调用)
//由于只有一个结构信息，利用CListCtl的缓存可以保存信息，不用自己更新CListCtrl
DWORD CProductStep2Dlg::OnWizardActive()
{
	//接受信息输入，完成初始化工作
	//m_MatInfoList.DeleteAllItems();
	//m_LowValItem.clear();
	//m_LowValItemNum=0;
	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////前往下一页
//可以检验并保存当前工作,返回-1不切换，返回0切换
DWORD CProductStep2Dlg::OnWizardNext()
{
	//if (m_MatInfoList.GetItemCount()==0)
	//{
	//	AfxMessageBox(CString("导入材料表未完成"));
	//	return -1;
	//}
	ShowWindow(SW_HIDE);     //暂时这样写，后期加检验判断
	return 0;

}

/////////////////////////////////////////前往上一页
//可以检验上一步工作不用保存
DWORD CProductStep2Dlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);        //暂时这样写，后期加检验判断
	return 0;
}





void CProductStep2Dlg::OnBnClickedInputmat()
{
	// TODO: Add your control notification handler code here
	CChoosePathDlg dlg;
	CString str;
	if (dlg.DoModal()==IDOK)
	{
		UpdateData();
		str=dlg.m_editPathTxt;
		if (str.IsEmpty()){
			AfxMessageBox(CString("请选择导入文件!"));
			return;
		}
	}
	ReadMatChart(str,0 , false);
}


void CProductStep2Dlg::ReadMatChart(CString excelFile,int sheetIndex,bool header)
{
	if(FAILED(::CoInitialize(NULL))) return;

	_ConnectionPtr pCon = NULL;
	_RecordsetPtr pSchema = NULL;
	CString tableName;

	pCon.CreateInstance(__uuidof(Connection));
	pSchema.CreateInstance(__uuidof(Recordset));

	CString connStr;
	CString hdr = header ? CString("YES") : CString("NO");    
	CString strEnd=excelFile.Right(1);

	if(excelFile!=CString(""))  
		if( strEnd== CString("x"))        
			connStr= CString("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=") + excelFile+CString(";Extended Properties=\"Excel 12.0 Xml;HDR=") + hdr +CString(";IMEX=1\"");                    
		else        
			connStr= CString("Provider='Microsoft.JET.OLEDB.4.0';Data Source=")+ excelFile +CString(";Extended Properties=\"Excel 8.0;HDR=") + hdr+CString(";IMEX=1\"");
	try
	{
		pCon->Open((_bstr_t)(connStr),"","",adModeUnknown);
		pSchema=NULL;
		pSchema=pCon->OpenSchema(adSchemaTables);
		_bstr_t table_name;
		for(int i = 0; i < sheetIndex; ++i) pSchema->MoveNext();
        table_name=pSchema->Fields->GetItem("TABLE_NAME")->Value;
		tableName=(LPCSTR)table_name;

	}
	catch(_com_error &e)
	{        
		CString temp;
		temp.Format(e.Description());
		AfxMessageBox(temp);
	}

	::CoUninitialize();



	CString sql;
	sql=CString("SELECT * FROM [")+tableName+CString("]");
	pSchema.CreateInstance(__uuidof(Recordset));
	try
	{
		pSchema->Open((_bstr_t)(sql).AllocSysString(),(_bstr_t)(connStr),adOpenStatic,adLockOptimistic, adCmdText);
	}
	catch(_com_error e)
	{
		CString temp;
		temp.Format(e.Description());
		AfxMessageBox(temp);
	}

	vector<vector<CString>> str_AllItem;     //用于临时存储excel表信息
	vector<CString> str_OneItem;    //临时存储excel表中的每行的数据
	//int cellCount = 0;
	while(!pSchema->adoEOF)
	{
		for(long i = 0; i < pSchema->GetFields()->GetCount(); ++i)
		{    
			CString str;
			_variant_t var = pSchema->GetFields()->GetItem(i)->Value;
			if(var.vt!=VT_NULL) str=(LPCSTR)(_bstr_t)(var);
			str_OneItem.push_back(str);
			//++cellCount;
		}
		str_AllItem.push_back(str_OneItem);
		vector<CString>().swap(str_OneItem);//释放掉

		pSchema->MoveNext();
	}
	SetListItem(str_AllItem);     //设置list条目

	vector<vector<CString>>().swap(str_AllItem);
}



void CProductStep2Dlg::SetListItem(vector<vector<CString>>& str_AllItem)
{
	//m_MatInfoList.DeleteAllItems();
	m_ListCtrlItem.clear();
	CMatChartItem m_OneItem;//每条list的信息

	for (int i=3,n=0;i<str_AllItem.size()-1;i++)       //插入数据一般从第四行开始
	{
		CString strItem;
		strItem.Format(CString("%d"),n+1);

		//保存表的每条信息
		m_OneItem.nItem=strItem;
		m_OneItem.m_MatNum=str_AllItem[i][3];
		m_OneItem.m_MatNam=str_AllItem[i][5];
		m_OneItem.m_MatAmount=str_AllItem[i][7];
		m_OneItem.m_MatRemark=str_AllItem[i][8];


		if(str_AllItem[i][3]==CString("")) continue;      //判别稀疏项

		m_MatInfoList.InsertItem(n,m_OneItem.nItem);              //数据取法和明细表的格式有关
		m_MatInfoList.SetItemText(n,1,m_OneItem.m_MatNum); //代号
		m_MatInfoList.SetItemText(n,2,m_OneItem.m_MatNam); //名称
		m_MatInfoList.SetItemText(n,3,m_OneItem.m_MatAmount); //数量
		m_MatInfoList.SetItemText(n,4,m_OneItem.m_MatRemark); //备注


		++n;

		m_ListCtrlItem.push_back(m_OneItem);
	}
	MatchMatVal(m_ListCtrlItem);  //匹配分值
}

void CProductStep2Dlg::MatchMatVal(vector<CMatChartItem>& m_ListCtrlItem)
{
	_RecordsetPtr m_pRs;
	vector<vector<CString>> m_MatMatchInfo;       //数据库中的匹配信息
	CString sql = CString("select * from Material");
	m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
	while (!m_pRs->adoEOF)
	{
		vector<CString> vtemp;
		CString str_Num = (CString)(m_pRs->GetCollect("Mnum")); 
		CString str_DeductVal = (CString)(m_pRs->GetCollect("DeductVal")); 

		vtemp.push_back(str_Num);
		vtemp.push_back(str_DeductVal);

		m_MatMatchInfo.push_back(vtemp);
		vector<CString>().swap(vtemp);

		m_pRs->MoveNext();
	}

	//匹配得分
	for (int i=0;i<m_ListCtrlItem.size();++i)
	{
		for (int j=0;j<m_MatMatchInfo.size();++j)
		{
			if(m_ListCtrlItem[i].m_MatNum==m_MatMatchInfo[j][0]) 
			{
				m_ListCtrlItem[i].m_MatScore=m_MatMatchInfo[j][1];
				break;
			}
			m_ListCtrlItem[i].m_MatScore=CString("0");  //若匹配不到则不扣分
		}
		
	}
	vector<vector<CString>>().swap(m_MatMatchInfo);
	SaveLowValItem(m_ListCtrlItem);//存储低分项
}

//存储低分项
void CProductStep2Dlg::SaveLowValItem(vector<CMatChartItem>& m_ListCtrlItem)
{
	for (int i=0;i<m_ListCtrlItem.size();++i)
	{
		CString strDeductVal=m_ListCtrlItem[i].m_MatScore;//提取评分
		CLowValItem OneLowValItem;
		int nDeductVal= _ttoi(strDeductVal);
		if (nDeductVal<0)
		{
			CString str;
			str.Format(CString("%d"),m_LowValItemNum+1);
			OneLowValItem.m_Item=str;
			OneLowValItem.m_ChartNam=CString("材料表");
			OneLowValItem.m_Classify=CString("材料");
			OneLowValItem.m_TechEvalIndex=m_ListCtrlItem[i].m_MatNam;
			OneLowValItem.m_IndexScore=m_ListCtrlItem[i].m_MatScore;
			OneLowValItem.m_LowValAdvice=CString("不使用该材料");

			m_LowValItem.push_back(OneLowValItem);

			++m_LowValItemNum;
		}
	}
}