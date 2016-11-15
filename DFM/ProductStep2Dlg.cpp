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
{
	str_AllItem.clear();
}

CProductStep2Dlg::~CProductStep2Dlg()
{
	vector<vector<CString>>().swap(str_AllItem);
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
	//���б�ؼ��ȳ�ʼ��,�����ͷ
	CRect rect1;
	int width1;
	m_MatInfoList.GetClientRect(&rect1);
	width1=rect1.Width();

	m_MatInfoList.InsertColumn(0,CString("λ��"),LVCFMT_CENTER,width1/10);
	m_MatInfoList.InsertColumn(1,CString("����"),LVCFMT_CENTER,width1*3/10);
	m_MatInfoList.InsertColumn(2,CString("��������"),LVCFMT_CENTER,width1*3/10);
	m_MatInfoList.InsertColumn(3,CString("����"),LVCFMT_CENTER,width1/10);
	m_MatInfoList.InsertColumn(4,CString("��ע"),LVCFMT_CENTER,width1/5);


	//���ò��ɱ༭��
	vector<int> nNoEdit;
	nNoEdit.push_back(0);               //�����в����Ա༭
	nNoEdit.push_back(1);  
	nNoEdit.push_back(2);  
	nNoEdit.push_back(3);
	nNoEdit.push_back(4);  
	m_MatInfoList.SetnNoEditList(nNoEdit);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////���ǰҳ(����һҳ����һҳת����ҳ�������)
//����ֻ��һ���ṹ��Ϣ������CListCtl�Ļ�����Ա�����Ϣ�������Լ�����CListCtrl
DWORD CProductStep2Dlg::OnWizardActive()
{
	//������Ϣ���룬��ɳ�ʼ������
	m_MatInfoList.DeleteAllItems();
	ShowWindow(SW_SHOW);
	return 0;
}

/////////////////////////////////////////////ǰ����һҳ
//���Լ��鲢���浱ǰ����,����-1���л�������0�л�
DWORD CProductStep2Dlg::OnWizardNext()
{

	ShowWindow(SW_HIDE);     //��ʱ����д�����ڼӼ����ж�
	return 0;

}

/////////////////////////////////////////ǰ����һҳ
//���Լ�����һ���������ñ���
DWORD CProductStep2Dlg::OnWizardPrevious()
{
	ShowWindow(SW_HIDE);        //��ʱ����д�����ڼӼ����ж�
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
			AfxMessageBox(CString("��ѡ�����ļ�!"));
			return;
		}
	}
	ReadMatChart(str,0 , false);
	SetListItem(str_AllItem);
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


	vector<CString> str_OneItem;
	str_AllItem.clear();
	int cellCount = 0;
	while(!pSchema->adoEOF)
	{
		str_OneItem.clear();
		for(long i = 0; i < pSchema->GetFields()->GetCount(); ++i)
		{    
			CString str;
			_variant_t var = pSchema->GetFields()->GetItem(i)->Value;
			if(var.vt!=VT_NULL) str=(LPCSTR)(_bstr_t)(var);
			str_OneItem.push_back(str);
			++cellCount;
		}
		str_AllItem.push_back(str_OneItem);
		pSchema->MoveNext();
	}
}



void CProductStep2Dlg::SetListItem(vector<vector<CString>>& str_AllItem)
{
	m_MatInfoList.DeleteAllItems();
	for (int i=3,n=0;i<str_AllItem.size()-1;i++)       //��������һ��ӵ����п�ʼ
	{
		CString strItem;
		strItem.Format(CString("%d"),n+1);

		if(str_AllItem[i][3]==CString("")) continue;
		m_MatInfoList.InsertItem(n,strItem);              //����ȡ������ϸ��ĸ�ʽ�й�
		m_MatInfoList.SetItemText(n,1,str_AllItem[i][3]); 
		m_MatInfoList.SetItemText(n,2,str_AllItem[i][5]);
		m_MatInfoList.SetItemText(n,3,str_AllItem[i][7]);
		m_MatInfoList.SetItemText(n,4,str_AllItem[i][8]);

		++n;
	}
}