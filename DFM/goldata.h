////////////////////辅助存储数据，方便数据在类间的传递
#pragma once
#include <vector>
#include <map>
#include <afx.h>
#include <utility>


using std::map;
using std::vector;
using std::pair;



struct CProductInfo //产品信息
{
	CString m_ProductName;  //产品名
	CString m_ProductNum;   //产品编号
	CString m_ProductSub;   //产品隶属组件
	CString str_EvalType;   //评价类型ID
	CString m_TypeInfo;     //评价类型介绍
	int m_isEval;           //是否已经评价
};


struct CTechChartItem //工艺表的每条数据
{
	CString nItem;                  //序号
	CString m_ChooseTech;           //采用工艺
	CString m_ReqClassify;          //要求分类
	CString m_TechEvalIndex;        //工艺评价指标
	vector<CString> m_ValComboStr;  //评分下拉菜单对应的所有字符
	CString m_IndexWeigh;           //指标权重

};