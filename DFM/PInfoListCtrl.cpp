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

	if(theApp.name!=CString(""))//如果登录成功则可执行右键操作
	{
		POSITION pos = GetFirstSelectedItemPosition();
		CPoint pt=pNMItemActivate->ptAction;
		CMenu menu;       // 菜单（包含主菜单栏和子菜单）   
		CMenu *pSubMenu;  // 右键菜单 
		if (pos == NULL)
		{
			/*AfxMessageBox(CString("没有选中项！\n"));*/
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
	dlg.strProductID=str;   //获取产品信息ID
	dlg.bInfoWrited=true;   //右键菜单重新编辑，产品信息已写入
	dlg.DoModal();
}


void CPInfoListCtrl::OnMenuUpdatelist()
{
	// TODO: Add your command handler code here
	::SendMessage(GetParent()->m_hWnd,WM_UPDATELIST,0,0);
}
