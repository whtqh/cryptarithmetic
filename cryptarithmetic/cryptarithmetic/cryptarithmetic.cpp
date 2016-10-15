#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#include "formula.h"
#include "minus_formula.h"
#include "times_formula.h"
void main()
{
	string str_up;
	string str_down;
	string *str_in;//using c_str() while printf
	string str_ans;
	int k = 0;
	//cin >> k;
	cout << "input times formula's str_up & str_down" << endl;
	cin >> str_up;
	cin >> str_down;
	cout << "input str_in one by one" << endl;
	k = str_down.size();
	str_in = new string[k];
	for (int i = 0; i < k; i++)
	{
		string str_temp;
		cin >> str_temp;
		for (int j = 0; j < i; j++)
		{
			str_temp = str_temp + '0';
		}
		str_in[i] = str_temp;
	}

	cout << "input str_ans " << endl;
	cin >> str_ans;
	times_formula Times_Formula = times_formula(str_up, str_down, str_in, str_ans);
	Times_Formula.times_track_recurison();
	

	//cout << "Input " << k << " string as Addend and a sum like SEND + MORE = MONEY" << endl;
	//for (int i = 0; i < k; i++)
	//{
	//	cin >> str_in[i];
	//}
	//cin >> str_ans;

	//formula My_Formula = formula(str_in, str_ans, k);

	//My_Formula.plus_track_recursion();
	
	//Befor Minus_Formula need to do some jobs to str_ans & str_in
	//minus_formula Minus_Formula = minus_formula(str_ans, str_in);
	//Minus_Formula.minus_track_recursion();




}