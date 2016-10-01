// PInfoListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DFM.h"
#include "PInfoListCtrl.h"
#include "ProductNewDlg.h"
#include "DFMDlg.h"


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
	ON_COMMAND(ID_DETETE_ITEM1, &CPInfoListCtrl::OnDeteteItem1)
	ON_COMMAND(ID_DETETE_ITEM2, &CPInfoListCtrl::OnDeteteItem2)
	ON_COMMAND(ID_MENU_EVALIN, &CPInfoListCtrl::OnMenuEvalin)
	ON_COMMAND(ID_MENU_UPDATELIST, &CPInfoListCtrl::OnMenuUpdatelist)
END_MESSAGE_MAP()



// CPInfoListCtrl message handlers




void CPInfoListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if(theApp.name!=CString(""))//�����¼�ɹ����ִ���Ҽ�����
	{
		POSITION pos = GetFirstSelectedItemPosition();
		CPoint pt=pNMItemActivate->ptAction;
		CMenu menu;       // �˵����������˵������Ӳ˵���   
		CMenu *pSubMenu;  // �Ҽ��˵� 
		if (pos == NULL)
		{
			/*AfxMessageBox(CString("û��ѡ���\n"));*/
			menu.LoadMenu(IDR_LISTCTRL3);   
			pSubMenu = menu.GetSubMenu(0);      
			ClientToScreen(&pt);   
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
		}
		else
		{
			while (pos)
			{
				m_nItem = GetNextSelectedItem(pos);
				TRACE(_T("Item %d was selected!\n"), m_nItem);
			}
			CString strIsEval;
			strIsEval=GetItemText(m_nItem,6);

  
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
				pSubMenu = menu.GetSubMenu(0);      
				ClientToScreen(&pt);   
				pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
			}

		}

	}
}




void CPInfoListCtrl::OnDeteteItem1()
{
	// TODO: Add your command handler code here
	CString strID;
	strID=GetItemText(m_nItem,1);
	::SendMessage(GetParent()->m_hWnd,WM_DELETEDATA,m_nItem,(LPARAM)(LPCTSTR)strID);
}


void CPInfoListCtrl::OnDeteteItem2()
{
	// TODO: Add your command handler code here
	CString strID;
	strID=GetItemText(m_nItem,1);
	::SendMessage(GetParent()->m_hWnd,WM_DELETEDATA,m_nItem,(LPARAM)(LPCTSTR)strID);
}


void CPInfoListCtrl::OnMenuEvalin()
{
	// TODO: Add your command handler code here
	CProductNewDlg dlg;
	CString str;
	str=GetItemText(m_nItem,1);
	dlg.strProductID=str;   //��ȡ��Ʒ��ϢID
	dlg.bInfoWrited=true;   //�Ҽ��˵����±༭����Ʒ��Ϣ��д��
	dlg.DoModal();
}


void CPInfoListCtrl::OnMenuUpdatelist()
{
	// TODO: Add your command handler code here
	::SendMessage(GetParent()->m_hWnd,WM_UPDATELIST,0,0);
}
