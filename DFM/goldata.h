////////////////////�����洢���ݣ��������������Ĵ���
#pragma once
#include <vector>
#include <map>
#include <afx.h>
#include <utility>


using std::map;
using std::vector;
using std::pair;



struct CProductInfo //��Ʒ��Ϣ
{
	CString m_ProductName;  //��Ʒ��
	CString m_ProductNum;   //��Ʒ���
	CString m_ProductSub;   //��Ʒ�������
	CString str_EvalType;   //��������ID
	CString m_TypeInfo;     //�������ͽ���
	int m_isEval;           //�Ƿ��Ѿ�����
};


struct CTechChartItem //���ձ��ÿ������
{
	CString nItem;                  //���
	CString m_Classify;             //���
	CString m_TechEvalIndex;        //��������ָ��
	vector<CString> m_ValComboStr;  //���������˵���Ӧ�������ַ�
	CString m_ComboStrChoose;       //��ѡ���combo�ַ�
	CString m_IndexScore;           //ָ��÷�

};

struct CMatChartItem //���ϱ��ÿ������
{
	CString nItem;               //λ��
	CString m_MatNum;            //����
	CString m_MatNam;            //����
	CString m_MatAmount;         //����
	CString m_MatRemark;         //��ע
	CString m_MatScore;          //��������
};

struct CMaturyChartItem //���ճ�����ÿ������
{
	CString nItem;              //���
	CString m_TechNam;          //������
	CString m_TechMaturyVal;    //���ճ�������
	CString m_TechUseStatus;    //����ʹ��״̬
};

struct CResultChartItem //���۽�����ÿ������
{
	CString nItem;              //���
	CString m_ItemNam;          //�����Ŀ��
	CString m_ItemVal;          //�����Ŀ��ʾֵ
};

struct CLowValItem     //�ͷ��������ÿ������
{
	CString m_Item;                 //���
	CString m_ChartNam;             //��������
	CString m_Classify;             //���
	CString m_TechEvalIndex;        //��������ָ��
	CString m_IndexScore;           //ָ��÷�
	CString m_LowValAdvice;         //�ͷ����

};

struct CIndexValItem
{
	CString m_Item;            //���
	CString m_IndexNam;        //ָ����
	CString m_IndexVal;        //����ֵ
};