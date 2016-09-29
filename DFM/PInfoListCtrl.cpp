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
		strIsEval=GetItemText(m_nItem,5);

		CPoint pt=pNMItemActivate->ptAction;
		CMenu menu;       // 菜单（包含主菜单栏和子菜单）   
		CMenu *pSubMenu;  // 右键菜单   
		// 加载菜单资源到menu对象   
		if(strIsEval==CString("进行中"))
		{
			menu.LoadMenu(IDR_LISTCTRL1);   
			// 因为右键菜单是弹出式菜单，不包含主菜单栏，所以取子菜单   
			pSubMenu = menu.GetSubMenu(0);    //可能有一排一级菜单，获取第一个 
			// 将坐标值由客户坐标转换为屏幕坐标   
			ClientToScreen(&pt);   
			// 弹出右键菜单，菜单左侧与point.x坐标值对齐   
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
		}
		else
		{
			menu.LoadMenu(IDR_LISTCTRL2);   
			// 因为右键菜单是弹出式菜单，不包含主菜单栏，所以取子菜单   
			pSubMenu = menu.GetSubMenu(0);    //可能有一排一级菜单，获取第一个 
			// 将坐标值由客户坐标转换为屏幕坐标   
			ClientToScreen(&pt);   
			// 弹出右键菜单，菜单左侧与point.x坐标值对齐   
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
	dlg.DoModal();
   //((CProductStep0Dlg*)dlg.m_pPageList[0])->m_ProductNum=GetItemText(m_nItem,1);
   //((CProductStep0Dlg*)dlg.m_pPageList[0])->m_ProductName=GetItemText(m_nItem,2);
   //((CProductStep0Dlg*)dlg.m_pPageList[0])->m_ProductSub=GetItemText(m_nItem,3);
   //((CProductStep0Dlg*)dlg.m_pPageList[0])->m_TypeInfo=GetItemText(m_nItem,1);
}
