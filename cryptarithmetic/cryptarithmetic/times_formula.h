#pragma once
#include "formula.h"
using namespace std;

class times_formula
{
public:
	int *N;								//����ÿһ�е��ַ�����
	int NK;								//������
	int N_Ans_Len;					//�͵ĳ���
	int N_Add_LenMax;			//��������ĳ���
	int N_Multi_Up_Len;
	int N_Multi_Down_Len;
	int Carry_Max;					//��λ�����ֵ unused
	char Last_Symbol;			//��ǰ�������ַ�
	int *carry_check;				//����Ľ�λ����
	int Track_Depth;				//��ǰ�ݹ�����
											
	int symbol_num;				//�ַ�������
	string symbol_layout;		//�����Ӧ���ַ���
	symbol *result;				//��symbol������
	symbol *constant;			//�泣��������
	symbol ***Pointer_N;		//������ָ��Ķ�ά����
	symbol **Pointer_Ans;		//�͵�ָ���һά����
	symbol **Pointer_Up;		//��������ָ���һά����
	symbol **Pointer_Down;	//������ָ���һά����

	times_formula(string str_up, string str_down, string *str_in, string str_ans);
	~times_formula();
	void times_track_recurison();

	bool find_goal_symbol();		//�ҵ���һ���������ַ�
	void update_species();			//���ݵ�ǰ�Ľ�λ����֪
	void restore_species();
	bool contradiction();
	void PrintAnswer();
	bool CheckStatus();
	bool CarryCheck();
};