#pragma once


// CPInfoListCtrl

class CPInfoListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CPInfoListCtrl)

public:
	CPInfoListCtrl();
	virtual ~CPInfoListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	int m_nItem;                //编辑表项的行号
	//int m_nSubItem;             //编辑表项的列号
	afx_msg void OnDeteteItem1();//右键菜单删除1
	afx_msg void OnDeteteItem2();//右键菜单删除2
	afx_msg void OnMenuEvalin();//右键菜单新建评分
	afx_msg void OnMenuUpdatelist();//list刷新
};


