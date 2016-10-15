#include "divide_formula.h"
using namespace std;

divide_formula::divide_formula(string str_up, string str_down, string *str_in, string *str_remain, string str_ans)
{
	// Set Known Constant
	constant = new symbol[10];
	result = new symbol[10];
	int k = str_down.size();		//Diiferent to Plus Formula.
	Carry_Max = k - 1;
	NK = k;
	Track_Depth = 0;
	string temp_const_str = "0123456789";
	for (int i = 0; i < 10; i++)
	{
		constant[i].Known = true;
		constant[i].num = i;
		constant[i].layout = temp_const_str[i];
	}
	//Str_in
	N = new int[k];
	N_Add_LenMax = 0;
	for (int i = 0; i < k; i++)
	{
		N[i] = (int)str_in[i].size();
		if (N[i] > N_Add_LenMax)
			N_Add_LenMax = N[i];
	}
	//str_remained
	R = new int[k];
	R_Add_LenMax = 0;
	for (int i = 0; i < k; i++)
	{
		R[i] = (int)str_remain[i].size();
		if (R[i] > R_Add_LenMax)
			R_Add_LenMax = R[i];
	}

	N_Ans_Len = (int)str_ans.size();
	N_Multi_Up_Len = (int)str_up.size();
	N_Multi_Down_Len = (int)str_down.size();

	carry_check = new int[N_Ans_Len];
	//Find unique list and select known nums
	symbol_num = 0;
	symbol_layout = "";
	Pointer_N = new symbol**[k];
	for (int i = 0; i < k; i++)
	{
		Pointer_N[i] = new symbol*[N_Add_LenMax];
	}
	Pointer_Ans = new symbol*[N_Ans_Len];
	Pointer_Up = new symbol*[N_Multi_Up_Len];
	Pointer_Down = new symbol*[N_Multi_Down_Len];

	//Add remainder to divide
	Pointer_R = new symbol**[k];
	for (int i = 0; i < k; i++)
	{
		Pointer_R[i] = new symbol*[R_Add_LenMax];
	}
	
	//transform Added and Sum nums to matrix

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < N[i]; j++)
		{
			std::size_t found_in_const = temp_const_str.find(str_in[i][j]);
			if (found_in_const == std::string::npos)
			{
				std::size_t found = symbol_layout.find(str_in[i][j]);
				if (found == std::string::npos)
				{
					if (symbol_num < 10)
						symbol_num++;
					else
						printf("Unvalid Input para\n");
					result[size(symbol_layout)].layout = str_in[i][j]; //Add new char
					Pointer_N[i][N[i] - j - 1] = &result[size(symbol_layout)];
					symbol_layout = symbol_layout + str_in[i][j];
				}
				else
					Pointer_N[i][N[i] - j - 1] = &result[(int)found];
			}
			else
			{
				Pointer_N[i][N[i] - j - 1] = &constant[(int)found_in_const];
			}
		}
		for (int j = N[i]; j < N_Add_LenMax; j++)
		{
			Pointer_N[i][j] = &constant[0];
		}
	}

	//Remainder
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < R[i]; j++)
		{
			std::size_t found_in_const = temp_const_str.find(str_remain[i][j]);
			if (found_in_const == std::string::npos)
			{
				std::size_t found = symbol_layout.find(str_remain[i][j]);
				if (found == std::string::npos)
				{
					if (symbol_num < 10)
						symbol_num++;
					else
						printf("Unvalid Input para\n");
					result[size(symbol_layout)].layout = str_remain[i][j]; //Add new char
					Pointer_R[i][R[i] - j - 1] = &result[size(symbol_layout)];
					symbol_layout = symbol_layout + str_remain[i][j];
				}
				else
					Pointer_R[i][R[i] - j - 1] = &result[(int)found];
			}
			else
			{
				Pointer_R[i][R[i] - j - 1] = &constant[(int)found_in_const];
			}
		}
		for (int j = R[i]; j < N_Add_LenMax; j++)
		{
			Pointer_R[i][j] = &constant[0];
		}
	}
	//Add sum num to Pointer
	for (int i = 0; i < N_Ans_Len; i++)
	{
		std::size_t found_in_const = temp_const_str.find(str_ans[i]);
		if (found_in_const == std::string::npos)
		{
			std::size_t found = symbol_layout.find(str_ans[i]);
			if (found == std::string::npos)
			{
				if (symbol_num < 10)
					symbol_num++;
				else
					printf("Unvalid Input para\n");
				result[size(symbol_layout)].layout = str_ans[i];//Add new char
				Pointer_Ans[N_Ans_Len - i - 1] = &result[size(symbol_layout)];
				symbol_layout = symbol_layout + str_ans[i];
			}
			else
				Pointer_Ans[N_Ans_Len - i - 1] = &result[(int)found];
		}
		else
		{
			Pointer_Ans[N_Ans_Len - i - 1] = &constant[(int)found_in_const];
		}
	}
	for (int i = 0; i < N_Multi_Up_Len; i++)
	{
		std::size_t found_in_const = temp_const_str.find(str_up[i]);
		if (found_in_const == std::string::npos)
		{
			std::size_t found = symbol_layout.find(str_up[i]);
			if (found == std::string::npos)
			{
				if (symbol_num < 10)
					symbol_num++;
				else
					printf("Unvalid Input para\n");
				result[size(symbol_layout)].layout = str_up[i];
				Pointer_Up[N_Multi_Up_Len - i - 1] = &result[size(symbol_layout)];
				symbol_layout = symbol_layout + str_up[i];
			}
			else
				Pointer_Up[N_Multi_Up_Len - i - 1] = &result[(int)found];
		}
		else
		{
			Pointer_Up[N_Multi_Up_Len - i - 1] = &constant[(int)found_in_const];
		}
	}
	for (int i = 0; i < N_Multi_Down_Len; i++)
	{
		std::size_t found_in_const = temp_const_str.find(str_down[i]);
		if (found_in_const == std::string::npos)
		{
			std::size_t found = symbol_layout.find(str_down[i]);
			if (found == std::string::npos)
			{
				if (symbol_num < 10)
					symbol_num++;
				else
					printf("Unvalid Input para\n");
				result[size(symbol_layout)].layout = str_down[i];
				Pointer_Down[N_Multi_Down_Len - i - 1] = &result[size(symbol_layout)];
				symbol_layout = symbol_layout + str_down[i];
			}
			else
				Pointer_Down[N_Multi_Down_Len - i - 1] = &result[(int)found];
		}
		else
		{
			Pointer_Down[N_Multi_Down_Len - i - 1] = &constant[(int)found_in_const];
		}
	}
	
	//Transform 
}

divide_formula::~divide_formula()
{

}