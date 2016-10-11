#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#include "formula.h"
void main()
{
	string *str_in;//using c_str() while printf
	int k = 0;
	cin >> k;
	str_in = new string[k];
	string str_ans;

	cout << "Input " << k << " string as Addend and a sum like SEND + MORE = MONEY" << endl;
	for (int i = 0; i < k; i++)
	{
		cin >> str_in[i];
	}
	cin >> str_ans;

	for (int i = 0; i < k; i++)
	{
		cout << str_in[i] << endl;
	}
	cout << "-------------------" << endl;
	cout << str_ans << endl;

	formula My_Formula = formula(str_in, str_ans, k);
	/*for (int i = 0; i < k; i++)
	{
	for (int j = 0; j < My_Formula.N_Add_LenMax; j++)
	{
	cout << My_Formula.Pointer_N[i][j]->num ;
	}
	cout << endl;
	}
	for (int i = 0; i < My_Formula.N_Ans_Len; i++)
	{
	cout << My_Formula.Pointer_Ans[i]->num;
	}
	cout << endl;*/
	My_Formula.track_recursion();
}