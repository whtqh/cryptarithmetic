#pragma once
#include<iostream>
using namespace std;
class symbol
{
public:
	char layout;
	int num;
	int species_num;
	int species_check[10];
	bool Known;
	symbol()
	{
		layout = ' ';
		num = -1;
		Known = false;
		species_num = 10;
		for (int i = 0; i < 10; i++)
		{
			species_check[i] = 1;
		}
	}
	symbol(int correct_num)
	{
		layout = ' ';
		if (correct_num >= 10 || correct_num < 0)
		{
			cout << "Error in symbol defining~\n" << endl;
		}
		num = correct_num;
		species_num = 1;
		Known = true;
		for (int i = 0; i < 10; i++)
		{
			species_check[i] = -1;
		}
		species_check[num] = 1;
	}
	~symbol(){ }
	void set_impossible(int impossible_num);
};