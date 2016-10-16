#pragma once
#include "formula.h"
using namespace std;

class minus_formula
{
public:
	formula add_formula;
	minus_formula(string str_up, string *str_other) :add_formula(str_other, str_up, 2) {};
	~minus_formula();
	void minus_track_recursion();
};
