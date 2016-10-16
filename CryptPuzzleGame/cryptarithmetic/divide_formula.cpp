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
					result[(symbol_layout).size()].layout = str_in[i][j]; //Add new char
					Pointer_N[i][N[i] - j - 1] = &result[(symbol_layout).size()];
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
					result[(symbol_layout).size()].layout = str_remain[i][j]; //Add new char
					Pointer_R[i][R[i] - j - 1] = &result[(symbol_layout).size()];
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
				result[(symbol_layout).size()].layout = str_ans[i];//Add new char
				Pointer_Ans[N_Ans_Len - i - 1] = &result[(symbol_layout).size()];
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
				result[(symbol_layout).size()].layout = str_up[i];
				Pointer_Up[N_Multi_Up_Len - i - 1] = &result[(symbol_layout).size()];
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
				result[(symbol_layout).size()].layout = str_down[i];
				Pointer_Down[N_Multi_Down_Len - i - 1] = &result[(symbol_layout).size()];
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
	delete[]result;
	delete[]constant;
}

void divide_formula::divide_track_recurison()
{
	int temp_id = -1;
	int RestoreCheck[10] = { 0 };
	int RestoreNum = 0;

	if (this->find_goal_symbol() == false)			//Different find goal func to plus
	{
		return;
	}
	Track_Depth++;

	for (int i = 0; i < 10; i++)
	{
		//Track_recurision
		if (result[i].layout == Last_Symbol)
		{
			temp_id = i;
			break;
		}
	}
	//找到上一次递归中决定的下一个要找的字母位置
	if (temp_id != -1)
	{
		RestoreNum = result[temp_id].species_num;
		for (int j = 0; j < 10; j++)
		{
			RestoreCheck[j] = result[temp_id].species_check[j];
		}
		result[temp_id].Known = true;
	}


	for (int i = 0; i < 10; i++)		//遍历所有可能进行搜索
	{
		if (result[temp_id].species_check[i] == 1)
		{
			//printf("*****Depth: [ %d ]*****Type_num = %d\n", Track_Depth,result[temp_id].species_num);
			//printf("Now: value of [ %c ]= %d\n",result[temp_id].layout, i);
			result[temp_id].num = i;
			result[temp_id].species_num = 1;
			for (int j = 0; j < 10; j++)
			{
				if (j == i)
					continue;
				result[temp_id].species_check[j] = -1;
			}
			//Check if Add the temp_id's value to make up corruption
			for (int j = 0; j < symbol_num; j++)
			{
				if (result[j].species_num == 1 && result[j].species_check[i] == 1 && result[j].Known == false)
				{
					if (temp_id != -1)
					{
						for (int t = 0; t < 10; t++)
						{
							result[temp_id].species_check[t] = RestoreCheck[t];
						}
					}
					continue;
				}
			}
			if (CheckStatus())
			{
				//PrintAnswer();
				if (CarryCheck() == true)		//Different Multiple Check
				{
					cout << "-----------Answer-----------" << endl;
					PrintAnswer();					//Different Print
				}
				if (temp_id != -1)
				{
					for (int j = 0; j < 10; j++)
					{
						result[temp_id].species_check[j] = RestoreCheck[j];
					}
				}
				continue;
			}
			divide_track_recurison();	//递归函数，有可能因为搜索失败返回并且没有能够初始化。
		}
		for (int j = 0; j < 10; j++)
		{
			result[temp_id].species_check[j] = RestoreCheck[j];
		}
	}
	result[temp_id].species_num = RestoreNum;	//其实感觉没有什么意义
	result[temp_id].Known = false;
	this->restore_species();	//坑比函数
	Track_Depth--;
	return;
}
bool divide_formula::find_goal_symbol()
{
	this->update_species();
	//缩小当前取值范围
	if (contradiction() == false)
		return false;
	//如果发现取值矛盾，退出
	if (CheckStatus() == true)
		return true;
	//检查是否已经遍历所有字母

	//TODO: Add Symbol_num query in turns
	int min_factor = 10;
	int min_id = -1;
	for (int i = 0; i < symbol_num; i++)
	{
		if (result[i].Known == false)
		{
			if (result[i].species_num <= min_factor)
			{
				min_id = i;
				min_factor = result[i].species_num;
			}
		}
	}
	if (min_id != -1)
	{
		Last_Symbol = result[min_id].layout;
		return true;
	}
	else
	{
		Last_Symbol = ' ';
		return false;
	}
}
void divide_formula::update_species()
{
	//Add 
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
					if (t != unknown_id)
						temp_sum = temp_sum + Pointer_N[t][j]->num;
				}
				//TODO
				for (int p = 0; p < 10; p++)
				{
					Pointer_N[unknown_id][j]->species_check[p] = -1;
				}
				Pointer_N[unknown_id][j]->species_num = 0;
				for (int t = 0; t <= Temp_Carry; t++)
				{
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
				Temp_Carry = (int)(Temp_Carry + temp_sum / 10);
			}
			else
				Temp_Carry = (int)(Sum_Bit / 10);
		}
		else if (unknown_num == 0)
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
				Pointer_Ans[j]->species_num = 0;
				for (int t = 0; t <= Temp_Carry; t++)
				{
					int temp_c = (int)((Sum_Bit + t - Temp_Carry) / 10);
					int remainder = Sum_Bit + t - Temp_Carry - 10 * temp_c;
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
				Pointer_Ans[j]->species_num = 0;
				for (int t = 0; t <= Temp_Carry; t++)
				{
					int temp_c = (int)((Sum_Bit + t - Temp_Carry) / 10);
					int remainder = Sum_Bit + t - Temp_Carry - 10 * temp_c;
					Pointer_Ans[j]->species_check[remainder] = 1;
					Pointer_Ans[j]->species_num++;
				}
				Temp_Carry = (int)(Sum_Bit / 10);
			}

		}
	}

	//Multiple Check Null first
	//整除数论
	for (int i = 0; i < NK; i++)
	{
		int Temp_Sum = 0;
		bool Divisible = true;
		if (Pointer_Down[i]->Known == true)
		{
			Divisible = false;
			continue;
		}
		for (int j = 0; j < N[i] - i; j++)
		{
			if (Pointer_N[i][j]->Known == false)
			{
				Divisible = false;
				break;
			}
			Temp_Sum = Temp_Sum + Pointer_N[i][j]->num;
		}
		if (Divisible == true)
		{
			if (Temp_Sum % 3 != 0)
			{
				Pointer_Down[i]->species_check[3] = -1;
				Pointer_Down[i]->species_check[9] = -1;
			}
			if (Pointer_N[i][i]->num % 2 != 0)
			{
				for (int j = 0; j < 5; j++)
				{
					Pointer_Down[i]->species_check[2 * j] = -1;
				}
			}
			if (Pointer_N[i][i]->num % 5 != 0)
			{
				Pointer_Down[i]->species_check[5] = -1;
				Pointer_Down[i]->species_check[0] = -1;
			}
		}
	}

	//Zero
	for (int i = 0; i < N_Multi_Down_Len; i++)
	{
		if (Pointer_Down[i]->Known == true && Pointer_Down[i]->num == 0)
		{
			for (int j = i; j < N[i]; j++)
			{
				if (Pointer_N[i][j]->Known == false)
				{
					for (int t = 0; t < 10; t++)
					{
						Pointer_N[i][j]->species_check[t] = -1;
					}
					Pointer_N[i][j]->species_check[0] = 1;
				}
			}
		}
	}
	//Last multi
	if (Pointer_Up[0]->Known == true)
	{
		for (int i = 0; i < N_Multi_Down_Len; i++)
		{
			if (Pointer_Down[i]->Known == true && Pointer_N[i][i]->Known == false)
			{
				for (int t = 0; t < 10; t++)
				{
					Pointer_N[i][i]->species_check[t] = -1;
				}
				int temp_num = (Pointer_Down[i]->num * Pointer_Up[0]->num) % 10;
				Pointer_N[i][i]->species_check[temp_num] = 1;
			}
		}
	}
	//Divide Add
	for (int i = 0; i < NK; i++)
	{
		if (Pointer_Ans[i]->Known == true && Pointer_N[i][i]->Known == true && Pointer_R[i][i]->Known == false)
		{
			int temp_num = 0;
			if (Pointer_Ans[i]->num >= Pointer_N[i][i]->num)
				temp_num = Pointer_Ans[i]->num - Pointer_N[i][i]->num;
			else
				temp_num =10 + Pointer_Ans[i]->num - Pointer_N[i][i]->num;
			for (int t = 0; t < 10; t++)
			{
				Pointer_R[i][i]->species_check[t] = -1;
			}
			Pointer_R[i][i]->species_check[temp_num] = 1;
		}
	}

}
void divide_formula::restore_species()
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
	}
}
bool divide_formula::contradiction()
{
	bool flag_all[10] = { false };
	for (int i = 0; i < symbol_num; i++)
	{
		if (result[i].Known == true)
		{
			flag_all[result[i].num] = true;
		}
	}
	//将其他未知字母的被占用数字位设为空
	for (int j = 0; j < 10; j++)
	{
		if (flag_all[j] == true)
		{
			for (int i = 0; i < symbol_num; i++)
			{
				if (result[i].num != j && result[i].Known == false && result[i].species_check[j] == 1)
				{
					result[i].species_check[j] = -1;
					result[i].species_num--;//最好不要改这个
				}
			}
		}
	}
	//检查是否已经有字母无取值选项
	for (int i = 0; i < symbol_num; i++)
	{
		if (result[i].species_num == 0)
			return false;
	}
	return true;
}
void divide_formula::PrintAnswer()
{
	for (int i = 0; i < N_Multi_Down_Len; i++)
	{
		cout << Pointer_Down[N_Multi_Down_Len - i - 1]->num;
	}
	cout << endl;
	for (int i = 0; i < N_Multi_Up_Len; i++)
	{
		cout << Pointer_Up[N_Multi_Up_Len - i - 1]->num;
	}
	cout << " /``````````````````````````````" << endl;
	for (int i = 0; i < N_Ans_Len; i++)
	{
		cout << Pointer_Ans[N_Ans_Len - i - 1]->num;
	}
	cout << endl;
	for (int i = NK-1; i >= 0; i--)
	{
		for (int j = 0; j < N_Add_LenMax; j++)
		{
			cout << Pointer_N[i][N_Add_LenMax - j - 1]->num;
		}
		cout << endl;
		for (int j = 0; j < R_Add_LenMax; j++)
		{
			cout << Pointer_R[i][R_Add_LenMax - j - 1]->num;
		}
		cout << endl;
	}
	
}
bool divide_formula::CheckStatus()
{
	for (int i = 0; i < symbol_num; i++)
	{
		if (result[i].Known == false)
		{
			return false;
		}
	}
	return true;
}
bool divide_formula::CarryCheck()
{
	//Add Part
	for (int i = 0; i < NK; i++)
	{
		if (Pointer_N[i][N[i] - 1]->num == 0)
			return false;
	}
	if (Pointer_Ans[N_Ans_Len - 1] == 0)
		return false;

	carry_check[0] = 0;
	for (int i = 0; i < N_Add_LenMax; i++)
	{
		int sum_temp = carry_check[i];
		for (int j = 0; j < NK; j++)
		{
			sum_temp += Pointer_N[j][i]->num;
		}
		carry_check[i + 1] = (int)(sum_temp / 10);
		if (Pointer_Ans[i]->num != (sum_temp - carry_check[i + 1] * 10))
			return false;
	}
	if (N_Ans_Len > N_Add_LenMax)
	{
		for (int i = N_Add_LenMax; i < N_Ans_Len; i++)
		{
			int sum_temp = carry_check[i];
			carry_check[i + 1] = (int)(sum_temp / 10);
			if (Pointer_Ans[i]->num != (sum_temp - carry_check[i + 1] * 10))
				return false;
		}
	}
	else
	{
		if (carry_check[N_Ans_Len] != 0)
			return false;
	}

	//Muti part
	int muti_up = 0;	//会溢出的风险...
	for (int j = 0; j < N_Multi_Up_Len; j++)
	{
		muti_up = muti_up + Pointer_Up[j]->num * pow(10, j);
	}
	for (int i = 0; i < N_Multi_Down_Len; i++)
	{
		int muti_ans = 0;
		for (int j = i; j < N[i]; j++)
		{
			muti_ans = muti_ans + Pointer_N[i][j]->num*pow(10, j - i);
		}
		if (muti_ans != muti_up * Pointer_Down[i]->num)
			return false;
	}

	//Divide part
	
	
	for (int i = 0; i < N_Multi_Down_Len ; i++)
	{
		int remainder = 0;
		int up_num = 0;
		int down_num = 0;
		for (int j = i; j < R[i]; j++)
		{
			remainder = remainder + Pointer_R[i][j]->num * pow(10, j - i);
		}
		for (int j = i; j < N[i]; j++)
		{
			down_num = down_num + Pointer_N[i][j]->num * pow(10, j - i);
		}
		
		if (i < N_Multi_Down_Len - 1)
		{
			for (int j = i; j < R[i + 1]; j++)
			{
				up_num = up_num + Pointer_R[i + 1][j]->num * pow(10, j - i);
			}
		}
		else
		{
			for (int j = i; j < N_Ans_Len; j++)
			{
				up_num = up_num + Pointer_Ans[j]->num * pow(10, j - i);
			}
		}
		if (up_num != (down_num + remainder))
			return false;
	}
	
	return true;
}