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
	afx_msg void OnDeteteItem1();//�Ҽ��˵�ɾ��1
	afx_msg void OnDeteteItem2();//�Ҽ��˵�ɾ��2
	afx_msg void OnMenuEvalin();//�Ҽ��˵��½�����
	afx_msg void OnMenuUpdatelist();//listˢ��
};


