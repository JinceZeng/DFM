#pragma once

#define ID_MYEDIT 101
#define ID_MYCOMBO 102
#define WM_SETINDEXVAL WM_USER+4    //设置得分
#define WM_INDEXMATCH WM_USER+5     //特殊评分项的匹配操作
#define WM_SETINDEXINFO WM_USER+6   //设置指标评分说明
#define WM_COMBOSEARCH WM_USER+8    //下拉单字符查找


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
	afx_msg void OnKillFocus(CWnd* pNewWnd);              //结束编辑
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
    bool bMatching;    //匹配中
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchange();                         //结束编辑
	void InitCombo(vector<CString>& lisStr);               //初始化组合框列表,动态变化是个麻烦事
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnCbnKillfocus();                         //失去焦点后结束编辑
	afx_msg void OnCbnEditchange();                    //combo编辑改变后响应
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

	//基本属性
public:
	BOOL m_bEditing;            //是否有表项正在编辑
protected:
	CMyEdit1  m_edit;             //编辑控件
	CMyCombo1 m_ComboBox;        //组合框
	int m_nItem;                //编辑表项的行号
	int m_nSubItem;             //编辑表项的列号


	vector<int> m_nlisCombo;               //录组合框对应的列(方便编辑)
	vector<int> m_nNoEdit;                 //记录不可编辑项
	vector<vector<CString>> m_strlisCombo;         //存储组合框所包含的字符串   


public:
	bool isCombo;                          //进一步判断是否需要下拉
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL MyBeginEdit(void);
	BOOL MyBeginComboBox(void);     //开始编辑组合框
	void MyEndEdit(bool bValidate);
	void MyEndComboBox(void);         //结束组合框编辑

	virtual void PreSubclassWindow();
	//afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnMenuInsertitem();      //响应插入行
	//afx_msg void OnMenuDeleteitem();      //响应删除行
	//afx_msg void OnMenuCheck();           //响应检测
	afx_msg LRESULT OnComboSearch(WPARAM wParam,LPARAM lParam);//下拉单字符查找消息

	void SetnComboList(vector<int>& nlisCombo);      //设置加载组合框的列
	void SetnNoEditList(vector<int>& nlisNoEdit);    //设置不可编辑项
	void SetComboString(vector<CString>& lisStr);   //设置第nItem行组合框字符串


};




