#pragma once

#define ID_MYEDIT 101
#define ID_MYCOMBO 102
#define WM_SETINDEXVAL WM_USER+4    //���õ÷�
#define WM_INDEXMATCH WM_USER+5     //�����������ƥ�����
#define WM_SETINDEXINFO WM_USER+6   //����ָ������˵��
#define WM_COMBOSEARCH WM_USER+8    //�������ַ�����
#define WM_DETELE_INDEXITEM WM_USER+10    //ɾ��ĳ������ָ��
#define WM_ADD_INDEXITEM WM_USER+11    //���ĳ������ָ��


#include <vector>
using std::vector;




// CMyEdit


class CMyEdit1 : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit1)

public:
	CMyEdit1();
	virtual ~CMyEdit1();
protected:
	CFont m_font;
private:
	BOOL m_bInputValid;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);              //�����༭
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};



#pragma once

// CMyCombo

class CMyCombo1 : public CComboBox
{
	DECLARE_DYNAMIC(CMyCombo1)

public:
	CMyCombo1();
	virtual ~CMyCombo1();

protected:
	CFont m_font;
    bool bMatching;    //ƥ����
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchange();                         //�����༭
	void InitCombo(vector<CString>& lisStr);               //��ʼ����Ͽ��б�,��̬�仯�Ǹ��鷳��
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnCbnKillfocus();                   //ʧȥ���������༭
	afx_msg void OnCbnEditchange();                    //combo�༭�ı����Ӧ
};




#pragma once
// CTechValListCtrl

class CTechValListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CTechValListCtrl)

public:
	CTechValListCtrl();
	virtual ~CTechValListCtrl();

protected:
	DECLARE_MESSAGE_MAP()

	//��������
public:
	BOOL m_bEditing;            //�Ƿ��б������ڱ༭
protected:
	CMyEdit1  m_edit;             //�༭�ؼ�
	CMyCombo1 m_ComboBox;        //��Ͽ�
	int m_nItem;                //�༭������к�
	int m_nSubItem;             //�༭������к�


	vector<int> m_nlisCombo;               //¼��Ͽ��Ӧ����(����༭)
	vector<int> m_nNoEdit;                 //��¼���ɱ༭��
	vector<vector<CString>> m_strlisCombo;         //�洢��Ͽ����������ַ���   


public:
	bool isCombo;                          //��һ���ж��Ƿ���Ҫ����
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL MyBeginEdit(void);
	BOOL MyBeginComboBox(void);     //��ʼ�༭��Ͽ�
	void MyEndEdit(bool bValidate);
	void MyEndComboBox(void);         //������Ͽ�༭

	virtual void PreSubclassWindow();
	//afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnMenuInsertitem();      //��Ӧ������
	//afx_msg void OnMenuDeleteitem();      //��Ӧɾ����
	//afx_msg void OnMenuCheck();           //��Ӧ���
	afx_msg LRESULT OnComboSearch(WPARAM wParam,LPARAM lParam);//�������ַ�������Ϣ

	void SetnComboList(vector<int>& nlisCombo);      //���ü�����Ͽ����
	void SetnNoEditList(vector<int>& nlisNoEdit);    //���ò��ɱ༭��
	void SetComboString(vector<CString>& lisStr);   //���õ�nItem����Ͽ��ַ���


	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuAdditem();
	afx_msg void OnDeteteItem3();
};




