#pragma once
#include "formula.h"
using namespace std;

class times_formula
{
public:
	formula add_formula;

	times_formula(string str_up, string str_down, string *str_in, string str_ans);
	~times_formula();
};