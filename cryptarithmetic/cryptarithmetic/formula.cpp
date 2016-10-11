#include "formula.h"

formula::formula(string *str_in, string str_ans,int k)
{
	// Set Known Constant
	constant = new symbol[10];
	result = new symbol[10];
	Carry_Max = k - 1;
	NK = k;
	string temp_const_str = "0123456789";
	for (int i = 0; i < 10; i++)
	{
		constant[i].Known = true;
		constant[i].num = i;
		constant[i].layout = temp_const_str[i];
	}
	N = new int[k];
	N_Add_LenMax = 0;
	for (int i = 0; i < k; i++)
	{
		N[i] = (int)str_in[i].size();
		if (N[i] > N_Add_LenMax)
			N_Add_LenMax = N[i];
	}
	N_Ans_Len = (int)str_ans.size();

	//Find unique list and select known nums
	symbol_num = 0;
	symbol_layout = "";
	Pointer_N = new symbol**[k];
	for (int i = 0; i < k; i++)
	{
		Pointer_N[i] = new symbol*[N_Add_LenMax];
	}
	Pointer_Ans = new symbol*[N_Ans_Len];

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
	//Transform 
}
formula::~formula()
{
	delete []result;
	delete []constant;
}
void formula::track_recursion()
{
	if (CheckStatus())
	{
		cout << "-----------Answer-----------" << endl;
		return;
	}
	if (this->find_goal_symbol() == false)
	{
		return;
	}
	int temp_id = 0;
	for (int i = 0; i < 10; i++)
	{
		//Track_recurision
		if (result[i].layout == Last_Symbol)
		{
			temp_id = i;
			break;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		result[temp_id].Known = true;
		if (result[temp_id].species_check[i] == 1)
		{
			result[temp_id].num = i;

			track_recursion();
			this->restore_species();
		}
	}
	return;
}
bool formula::find_goal_symbol() //calculate the min weight of each colum
{
	this->update_species();
	int Next_Location = 0;
	int min_factor = 0;
	bool find_first_min = false;
	for (int j = 0; j < N_Add_LenMax; j++)
	{
		int temp_choice_factor = 0;
		for (int i = 0; i < NK; i++)
		{
			if (Pointer_N[i][j]->Known == false)
			{
				temp_choice_factor = temp_choice_factor + Pointer_N[i][j]->species_num;
			}
		}
		if (Pointer_Ans[j]->Known == false)
		{
			temp_choice_factor = temp_choice_factor + Pointer_Ans[j]->species_num;
		}
		if(find_first_min == false && temp_choice_factor > 0)//Bug...
		{
			min_factor = temp_choice_factor;
			Next_Location = j;
			find_first_min = true;
		}
		if (min_factor > temp_choice_factor&&temp_choice_factor>0)
		{
			min_factor = temp_choice_factor;
			Next_Location = j;
		}
	}
	if (N_Add_LenMax < N_Ans_Len)
	{
		for (int j = N_Add_LenMax; j < N_Ans_Len; j++)
		{
			if (Pointer_Ans[j]->Known == false)
			{
				if (Pointer_Ans[j]->species_num < min_factor)
				{
					min_factor = Pointer_Ans[j]->species_num;
					Next_Location = j;
				}
			}
		}
	}
	if (find_first_min == false)
	{
		Last_Symbol = ' ';
		return false;
	}
	if (Next_Location >= N_Add_LenMax)
	{
		Last_Symbol = Pointer_Ans[Next_Location]->layout;
	}
	else 
	{
		int min_num = 10;
		int min_id = -1;
		for (int i = 0; i < NK; i++)
		{
			if (Pointer_N[i][Next_Location]->Known == false)
			{
				if (Pointer_N[i][Next_Location]->species_num <= min_num)
				{
					min_num = Pointer_N[i][Next_Location]->species_num;
					min_id = i;
				}
			}
		}
		Last_Symbol = Pointer_N[min_id][Next_Location]->layout;
		if (Pointer_Ans[Next_Location]->Known == false)
		{
			if (Pointer_Ans[Next_Location]->species_num <= min_num)
			{
				min_num = Pointer_Ans[Next_Location]->species_num;
			}
			Last_Symbol = Pointer_Ans[Next_Location]->layout;
		}
	}
	return true;
}
void formula::update_species()	//Before Do it add a check accessible func.
{
	this->contradiction();
	int Temp_Carry = 0;
	int Sum_Bit = 9 * NK + Temp_Carry;
	for (int j = 0; j < N_Add_LenMax; j++)
	{
		int unknown_num = 0;
		int unknown_id = 0;
		for (int i = 0; i < NK; i++)
		{
			if (Pointer_N[i][j]->Known == true)
				Sum_Bit = Sum_Bit - 9 + Pointer_N[i][j]->num;
			else
			{
				unknown_num++;
				unknown_id = i;
			}
		}
		if (unknown_num == 1)
		{
			if (Pointer_Ans[j]->Known == true)
			{
				int temp_sum = 0;
				for (int t = 0; t < NK; t++)
				{
					if(t != unknown_id)
					temp_sum = temp_sum + Pointer_N[t][j]->num;
				}
				//TODO
				for (int t = 0; t < Temp_Carry; t++)
				{
					for (int p = 0; p < 10; p++)
					{
						Pointer_N[unknown_id][j]->species_check[p] = -1;
					}
					Pointer_N[unknown_id][j]->species_num = 0;
					int remainder = t + temp_sum - 10 * (int)((t + temp_sum) / 10);
					if (remainder <= Pointer_Ans[j]->num)	//think about 9+9+9+9+x = 7
					{
						Pointer_N[unknown_id][j]->species_check[Pointer_Ans[j]->num - remainder] = 1;
						Pointer_N[unknown_id][j]->species_num++;
					}
					else //think about 9+9+9+9+x = 3
					{
						Pointer_N[unknown_id][j]->species_check[Pointer_Ans[j]->num + 10 - remainder] = 1;
						Pointer_N[unknown_id][j]->species_num++;
					}
				}
			}
			Temp_Carry = (int)(Sum_Bit / 10);
		}
		else if(unknown_num == 0)
		{
			if (Pointer_Ans[j]->Known == true)
			{
				Temp_Carry = (int)((Sum_Bit - Pointer_Ans[j]->num) / 10);
			}
			else
			{
				for (int p = 0; p < 10; p++)
				{
					Pointer_Ans[j]->species_check[p] = -1;
				}
				for (int t = 0; t <= Temp_Carry; t++)
				{
					Pointer_Ans[j]->species_num = 0;
					int temp_c = (int)((Sum_Bit + t - Temp_Carry) / 10);
					int remainder = Sum_Bit + t - Temp_Carry - 10 * temp_c ;
					Pointer_Ans[j]->species_check[remainder] = 1;
					Pointer_Ans[j]->species_num++;
				}
				Temp_Carry = (int)(Sum_Bit / 10);
			}
		}
		else
		{
			Temp_Carry = (int)(Sum_Bit / 10);
		}
		Sum_Bit = 9 * NK + Temp_Carry;
	}
	if (N_Ans_Len > N_Add_LenMax)
	{
		for (int j = N_Add_LenMax; j < N_Ans_Len; j++)
		{
			Sum_Bit = Temp_Carry;
			if (Pointer_Ans[j]->Known == true)
			{
				Temp_Carry = (int)((Sum_Bit - Pointer_Ans[j]->num) / 10);
			}
			else
			{
				for (int p = 0; p < 10; p++)
				{
					Pointer_Ans[j]->species_check[p] = -1;
				}
				for (int t = 0; t <= Temp_Carry; t++)
				{
					Pointer_Ans[j]->species_num = 0;
					int temp_c = (int)((Sum_Bit + t - Temp_Carry) / 10);
					int remainder = Sum_Bit + t - Temp_Carry - 10 * temp_c;
					Pointer_Ans[j]->species_check[remainder] = 1;
					Pointer_Ans[j]->species_num++;
				}
				Temp_Carry = (int)(Sum_Bit / 10);
			}
			
		}
	}
	
}
void formula::contradiction() 
{
	bool flag_all[10] = { false };
	for (int i = 0; i < symbol_num; i++)
	{
		if (result[i].Known == true)
		{
			flag_all[result[i].num] = true;
		}
	}

	for (int j = 0; j < 10; j++)
	{
		if (flag_all[j] == true)
		{
			for (int i = 0; i < symbol_num; i++)
			{
				if (result[i].num != j)
				{
					result[i].species_check[j] = -1;
				}
			}
		}
	}
	
}
void formula::restore_species()
{
	for (int i = 0; i < symbol_num; i++)
	{
		if (result[i].Known == false)
		{
			result[i].num = -1;
			result[i].species_num = 10;
			for (int j = 0; j < 10; j++)
			{
				result[i].species_check[j] = 1;
			}
		}
		if (result[i].layout == Last_Symbol)
		{
			result[i].Known = false;
			//TODO:
		}
	}

}
void formula::PrintAnswer()
{
	for (int i = 0; i < NK; i++)
	{
	for (int j = 0; j < N_Add_LenMax; j++)
	{
	cout << Pointer_N[i][N_Add_LenMax - j -1]->num ;
	}
	cout << endl;
	}
	cout << "+ _____________" << endl;
	for (int i = 0; i < N_Ans_Len; i++)
	{
	cout << Pointer_Ans[N_Ans_Len - i -1]->num;
	}
	cout << endl;
}
bool formula::CheckStatus() {
	for (int i = 0; i < symbol_num; i++)
	{
		if (result[i].Known == false)
		{
			return false;
		}
	}
	PrintAnswer();
	return true;
}