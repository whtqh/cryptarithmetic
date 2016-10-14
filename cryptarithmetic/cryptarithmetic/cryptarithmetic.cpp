#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#include "formula.h"
#include "minus_formula.h"
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

	//formula My_Formula = formula(str_in, str_ans, k);

	//My_Formula.plus_track_recursion();

	minus_formula Minus_Formula = minus_formula(str_ans, str_in);
	Minus_Formula.minus_track_recursion();


}