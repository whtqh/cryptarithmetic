#include "formula.h"

formula::formula(string *str_in, string str_ans,int k)
{
	// Set Known Constant
	constant = new symbol[10];
	result = new symbol[10];
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
	N = new int[k];
	N_Add_LenMax = 0;
	for (int i = 0; i < k; i++)
	{
		N[i] = (int)str_in[i].size();
		if (N[i] > N_Add_LenMax)
			N_Add_LenMax = N[i];
	}
	N_Ans_Len = (int)str_ans.size();
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
	int temp_id = -1;
	int RestoreCheck[10] = { 0 };
	int RestoreNum = 0;
	
	if (this->find_goal_symbol() == false)
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

	
	for (int i = 0; i < 10; i++)//遍历所有可能进行搜索
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
				if (result[j].species_num == 1 && result[j].species_check[i] == 1&&result[j].Known == false)
				{
					if (temp_id != -1)
					{
							for (int t = 0; t < 10; t++)
							{
								result[temp_id].species_check[t] = RestoreCheck[t];
							}
					}
					return;
				}
			}
			if (CheckStatus())
			{
				//PrintAnswer();
				if (CarryCheck() == true)
				{
					cout << "-----------Answer-----------" << endl;
					PrintAnswer();
				}
				if (temp_id != -1)
				{
					for (int j = 0; j < 10; j++)
					{
						result[temp_id].species_check[j] = RestoreCheck[j];
					}
				}
				//this->restore_species();
				continue;
			}
			track_recursion();		//递归函数，有可能因为搜索失败返回并且没有能够初始化。
		}
		for (int j = 0; j < 10; j++)
		{
			result[temp_id].species_check[j] = RestoreCheck[j];
		}
		//restore_species();
	}
	result[temp_id].species_num = RestoreNum;	//其实感觉没有什么意义
	result[temp_id].Known = false;
	this->restore_species();	//坑比函数
	Track_Depth--;
	return;
}
bool formula::find_goal_symbol() //calculate the min weight of each colum
{
	this->update_species();	
	//缩小当前取值范围
	if (contradiction() == false)
		return false;
	//如果发现取值矛盾，退出
	if (CheckStatus() == true)
		return true;
	//检查是否已经遍历所有字母

	//限定当前各元素取值范围，包括解决冲突问题等。
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
	//找到权值最小的一列
	if (find_first_min == false)
	{
		//意味着都找到了，应该在这之前就跳出。
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
	//找到下一个搜索的字母
	//printf("Change to :=========>%c\n", Last_Symbol);
	return true;
}
void formula::update_species()	//Before Do it add a check accessible func.
{
	//根据进位缩小范围
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
				Pointer_Ans[j]->species_num = 0;
				for (int t = 0; t <= Temp_Carry; t++)
				{
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
bool formula::contradiction() 
{
	//记录当前已经被占用的数字
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
				if (result[i].num != j && result[i].Known == false&&result[i].species_check[j] == 1)
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
	return true;
}
bool formula::CarryCheck()
{
	//First 0 check:
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
	return true;
}