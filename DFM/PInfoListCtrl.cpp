// PInfoListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "PInfoListCtrl.h"
#include "ProductNewDlg.h"


// CPInfoListCtrl

IMPLEMENT_DYNAMIC(CPInfoListCtrl, CListCtrl)

CPInfoListCtrl::CPInfoListCtrl()
{

}

CPInfoListCtrl::~CPInfoListCtrl()
{
}


BEGIN_MESSAGE_MAP(CPInfoListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CPInfoListCtrl::OnNMRClick)
	ON_NOTIFY_REFLECT(NM_CLICK, &CPInfoListCtrl::OnNMClick)
	ON_COMMAND(ID_DETETE_ITEM1, &CPInfoListCtrl::OnDeteteItem1)
	ON_COMMAND(ID_DETETE_ITEM2, &CPInfoListCtrl::OnDeteteItem2)
	ON_COMMAND(ID_MENU_EVALIN, &CPInfoListCtrl::OnMenuEvalin)
END_MESSAGE_MAP()



// CPInfoListCtrl message handlers




void CPInfoListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//int nItem;
	POSITION pos = GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(CString("No items were selected!\n"));
	}
	else
	{
		while (pos)
		{
			m_nItem = GetNextSelectedItem(pos);
			TRACE(_T("Item %d was selected!\n"), m_nItem);
			// you could do your own processing on nItem here
		}
		CString strIsEval;
		strIsEval=GetItemText(m_nItem,6);

		CPoint pt=pNMItemActivate->ptAction;
		CMenu menu;       // �˵����������˵������Ӳ˵���   
		CMenu *pSubMenu;  // �Ҽ��˵�   
		// ���ز˵���Դ��menu����   
		if(strIsEval==CString("������"))
		{
			menu.LoadMenu(IDR_LISTCTRL1);   
			// ��Ϊ�Ҽ��˵��ǵ���ʽ�˵������������˵���������ȡ�Ӳ˵�   
			pSubMenu = menu.GetSubMenu(0);    //������һ��һ���˵�����ȡ��һ�� 
			// ������ֵ�ɿͻ�����ת��Ϊ��Ļ����   
			ClientToScreen(&pt);   
			// �����Ҽ��˵����˵������point.x����ֵ����   
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
		}
		else
		{
			menu.LoadMenu(IDR_LISTCTRL2);   
			// ��Ϊ�Ҽ��˵��ǵ���ʽ�˵������������˵���������ȡ�Ӳ˵�   
			pSubMenu = menu.GetSubMenu(0);    //������һ��һ���˵�����ȡ��һ�� 
			// ������ֵ�ɿͻ�����ת��Ϊ��Ļ����   
			ClientToScreen(&pt);   
			// �����Ҽ��˵����˵������point.x����ֵ����   
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
		}

	}

	
}



void CPInfoListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CPInfoListCtrl::OnDeteteItem1()
{
	// TODO: Add your command handler code here
}


void CPInfoListCtrl::OnDeteteItem2()
{
	// TODO: Add your command handler code here
}


void CPInfoListCtrl::OnMenuEvalin()
{
	// TODO: Add your command handler code here
	CProductNewDlg dlg;
	dlg.bInfoWrited=true;
	dlg.DoModal();
	//dlg.ShowPage(1);
	CString str;
	str=GetItemText(m_nItem,1);

	_RecordsetPtr m_pRs;
	CString sql = CString("select * from ProductInfo where ProductID=") + str ;
	m_pRs = theApp.m_pConnect->Execute(_bstr_t(sql), NULL, adCmdText);
	CString str1 = (CString)m_pRs->GetCollect("ProductNam");
	CString str2 = (CString)m_pRs->GetCollect("ProductNum");
	CString str3 = (CString)(m_pRs->GetCollect("ProductSub")); 

	CString str44 =  m_pRs->GetCollect("EvalModelID");
	int int4 = _ttoi(str44);

	CString str5 = (CString)(m_pRs->GetCollect("EvalTypeIntro")); 
	((CProductStep0Dlg*)dlg.m_pPageList[0])->m_ProductName=str1;
	((CProductStep0Dlg*)dlg.m_pPageList[0])->m_ProductNum=str2;
	((CProductStep0Dlg*)dlg.m_pPageList[0])->m_ProductSub=str3;
	((CProductStep0Dlg*)dlg.m_pPageList[0])->m_EvalTypeVal=int4;
	((CProductStep0Dlg*)dlg.m_pPageList[0])->m_TypeInfo=str5;

	
	//::SendMessage(((CProductStep0Dlg*)dlg.m_pPageList[0])->m_hWnd,WM_UPDATEDATA,FALSE,FALSE);
}
