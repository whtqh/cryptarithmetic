#pragma once
#include "formula.h"
using namespace std;

class times_formula
{
public:
	int *N;								//加数每一行的字符数量
	int NK;								//多少行
	int N_Ans_Len;					//和的长度
	int N_Add_LenMax;			//加数的最长的长度
	int N_Multi_Up_Len;
	int N_Multi_Down_Len;
	int Carry_Max;					//进位的最大值 unused
	char Last_Symbol;			//当前搜索的字符
	int *carry_check;				//验算的进位数组
	int Track_Depth;				//当前递归的深度
											
	int symbol_num;				//字符的数量
	string symbol_layout;		//数组对应的字符串
	symbol *result;				//存symbol的数组
	symbol *constant;			//存常数的数组
	symbol ***Pointer_N;		//加数的指针的二维数组
	symbol **Pointer_Ans;		//和的指针的一维数组
	symbol **Pointer_Up;		//被乘数的指针的一维数组
	symbol **Pointer_Down;	//乘数的指针的一维数组

	times_formula(string str_up, string str_down, string *str_in, string str_ans);
	~times_formula();
	void times_track_recurison();

	bool find_goal_symbol();		//找到下一个搜索的字符
	void update_species();			//根据当前的进位和已知
	void restore_species();
	bool contradiction();
	void PrintAnswer();
	bool CheckStatus();
	bool CarryCheck();
};