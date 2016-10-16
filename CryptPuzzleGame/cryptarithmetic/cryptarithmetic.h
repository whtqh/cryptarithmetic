#ifndef CRYPTARITHMETIC_H
#define CRYPTARITHMETIC_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

#include "formula.h"
#include "minus_formula.h"
#include "times_formula.h"
#include "divide_formula.h"

void call_plus_func(string filepath);
void call_minus_func();
void call_times_func();
void call_divide_func();

#endif // CRYPTARITHMETIC_H
