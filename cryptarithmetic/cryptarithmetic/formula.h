#pragma once
#include "symbol.h"
#include <string>
using namespace std;

class formula
{
public:
	int *N;
	int NK;
	int N_Ans_Len;
	int N_Add_LenMax;
	int Carry_Max;
	char Last_Symbol;
	char RestoreSymbol;
	int Track_Depth;
	//set the N1 > N2, N3 >= N1
	int symbol_num;
	string symbol_layout;
	symbol *result;
	symbol *constant;
	symbol ***Pointer_N;
	symbol **Pointer_Ans;
	
	formula(string *str_in, string str_ans, int k);
	~formula();
	void track_recursion();
	bool find_goal_symbol();
	void update_species();
	void restore_species();
	bool contradiction();
	void PrintAnswer();
	bool CheckStatus();
};