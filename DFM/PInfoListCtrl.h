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
	int m_nItem;                //�༭������к�
	//int m_nSubItem;             //�༭������к�
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeteteItem1();
	afx_msg void OnDeteteItem2();
	afx_msg void OnMenuEvalin();
};


