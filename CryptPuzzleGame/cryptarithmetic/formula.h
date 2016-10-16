#pragma once
#include "symbol.h"
#include <string>
#include <math.h>
#include <puzzlebutton.h>
using namespace std;
#define ANSWER_MAX_NUM 100
class formula
{
public:
	int *N;     //加数每一行的字符数量
	int NK;		//多少行
	int N_Ans_Len;	//和的长度
	int N_Add_LenMax;	//加数的最长的长度
	int Carry_Max;			//进位的最大值 unused
	char Last_Symbol;	//当前搜索的字符
	int *carry_check;		//验算的进位数组
	int Track_Depth;		//当前递归的深度
	//set the N1 > N2, N3 >= N1
	int symbol_num;		//字符的数量
	string symbol_layout;	//数组对应的字符串
	symbol *result;			//存symbol的数组
	symbol *constant;		//存常数的数组
	symbol ***Pointer_N;	//加数的指针的二维数组
	symbol **Pointer_Ans;	//和的指针的一维数组
	
    int **answer;
    int answer_num;


	formula(string *str_in, string str_ans, int k);
	formula();
	~formula();
	void plus_track_recursion();	//递归函数
	bool find_goal_symbol();		//找到下一个搜索的字符
	void update_species();			//根据当前的进位和已知
	void restore_species();
	bool contradiction();
	void PrintAnswer();
	bool CheckStatus();
	bool CarryCheck();
};
