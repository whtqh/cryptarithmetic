#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#include "formula.h"
#include "minus_formula.h"
#include "times_formula.h"
#include "divide_formula.h"
void call_plus_func()
{
	string *str_in;
	string str_ans;
	int k = 0;
	cout << "Input : k =  ";
	cin >> k;
	cout << "Input " << k << " string as Addend and a sum like SEND + MORE = MONEY" << endl;
	str_in = new string[k];
	for (int i = 0; i < k; i++)
	{
		cin >> str_in[i];
	}
	cin >> str_ans;
	formula My_Formula = formula(str_in, str_ans, k);
	My_Formula.plus_track_recursion();
	
}
void call_minus_func()
{
	string str_ans;
	string *str_in;
	str_in = new string[2];
	
	cin >> str_ans;
	cin >> str_in[0];
	cin >> str_in[1];

	minus_formula Minus_Formula = minus_formula(str_ans, str_in);
	Minus_Formula.minus_track_recursion();
}
void call_times_func()
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
}
void call_divide_func()
{
	string str_up;
	string str_down;
	string *str_in;//using c_str() while printf
	string *str_remain;
	string str_ans;
	int k = 0;
	//cin >> k;
	cout << "input dividid formula's str_up & str_down" << endl;
	cin >> str_up;
	cin >> str_down;
	cout << "input str_in one by one" << endl;
	k = str_down.size();
	str_in = new string[k];
	str_remain = new string[k];
	for (int i = k-1; i >= 0; i--)
	{
		string str_temp;

		//Add up
		cin >> str_temp;
		for (int j = 0; j < i; j++)
		{
			str_temp = str_temp + '0';
		}
		str_in[i] = str_temp;

		//Remainder
		cin >> str_temp;
		for (int j = 1; j < i; j++)	//Less one '0'
		{
			str_temp = str_temp + '0';
		}
		str_remain[i] = str_temp;
	}
	
	cout << "input str_ans " << endl;
	cin >> str_ans;
	divide_formula Divide_Formula = divide_formula(str_up, str_down, str_in, str_remain, str_ans);
	Divide_Formula.divide_track_recurison();
}

void main()
{
	//call_plus_func();
	//call_minus_func();
	call_times_func();
	//call_divide_func();
	return;
}