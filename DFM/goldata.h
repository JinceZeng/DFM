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
	CString m_ChooseTech;           //���ù���
	CString m_ReqClassify;          //Ҫ�����
	CString m_TechEvalIndex;        //��������ָ��
	vector<CString> m_ValComboStr;  //���������˵���Ӧ�������ַ�
	CString m_IndexWeigh;           //ָ��Ȩ��

};