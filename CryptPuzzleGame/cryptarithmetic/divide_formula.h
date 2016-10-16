#pragma once
#include "formula.h"
using namespace std;

class divide_formula
{
	public:
		int *N;								//加数每一行的字符数量
		int *R;

		int NK;								//多少行
		
		int N_Ans_Len;					//和的长度
		int N_Add_LenMax;			//加数的最长的长度
		int R_Add_LenMax;			//余数的最长的长度

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
		//Add remainder from multiple
		symbol ***Pointer_R;		//余数的指针的二维数组

		symbol **Pointer_Ans;		//和的指针的一维数组
		symbol **Pointer_Up;		//被乘数的指针的一维数组
		symbol **Pointer_Down;	//乘数的指针的一维数组

		/*						DEFGH						<-	str_down
	str_up  ABCD | XXXXXXXXXXXX			<-	str_ans
						 /	XXXXX							--->[4]
							  SDAFR			--->[4]
							  XXFRF						--->[3]
								 XFAD			--->[3]
								 FDSA						--->[2]
								   RTRW		--->[2]
								   FADS						--->[1]
								     FRER		--->[1]
									 FADS					--->[0]		of str_in[][]
									   FDS		--->[0]		<-str_remain[][]
		*/



		divide_formula(string str_up, string str_down, string *str_in, string *str_remain, string str_ans);
		//
		~divide_formula();
		void divide_track_recurison();

		bool find_goal_symbol();		//找到下一个搜索的字符
		void update_species();			//根据当前的进位和已知
		void restore_species();
		bool contradiction();
		void PrintAnswer();
		bool CheckStatus();
		bool CarryCheck();
};