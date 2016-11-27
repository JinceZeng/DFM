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
	CString m_Classify;             //类别
	CString m_TechEvalIndex;        //工艺评价指标
	vector<CString> m_ValComboStr;  //评分下拉菜单对应的所有字符
	CString m_ComboStrChoose;       //所选择的combo字符
	CString m_IndexScore;           //指标得分

};

struct CMatChartItem //材料表的每条数据
{
	CString nItem;               //位号
	CString m_MatNum;            //代号
	CString m_MatNam;            //名称
	CString m_MatAmount;         //数量
	CString m_MatRemark;         //备注
	CString m_MatScore;          //材料评分
};

struct CMaturyChartItem //工艺成熟表的每条数据
{
	CString nItem;              //序号
	CString m_TechNam;          //工艺名
	CString m_TechMaturyVal;    //工艺成熟评分
	CString m_TechUseStatus;    //工艺使用状态
};

struct CResultChartItem //评价结果表的每条数据
{
	CString nItem;              //序号
	CString m_ItemNam;          //结果条目名
	CString m_ItemVal;          //结果条目显示值
};

struct CLowValItem     //低分项结果表的每条数据
{
	CString m_Item;                 //序号
	CString m_ChartNam;             //所属表名
	CString m_Classify;             //类别
	CString m_TechEvalIndex;        //工艺评价指标
	CString m_IndexScore;           //指标得分
	CString m_LowValAdvice;         //低分项建议

};

struct CIndexValItem
{
	CString m_Item;            //序号
	CString m_IndexNam;        //指标名
	CString m_IndexVal;        //评分值
};