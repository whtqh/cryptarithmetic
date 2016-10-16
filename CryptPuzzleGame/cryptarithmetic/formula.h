#pragma once
#include "symbol.h"
#include <string>
using namespace std;

class formula
{
public:
	int *N;     //����ÿһ�е��ַ�����
	int NK;		//������
	int N_Ans_Len;	//�͵ĳ���
	int N_Add_LenMax;	//��������ĳ���
	int Carry_Max;			//��λ�����ֵ unused
	char Last_Symbol;	//��ǰ�������ַ�
	int *carry_check;		//����Ľ�λ����
	int Track_Depth;		//��ǰ�ݹ�����
	//set the N1 > N2, N3 >= N1
	int symbol_num;		//�ַ�������
	string symbol_layout;	//�����Ӧ���ַ���
	symbol *result;			//��symbol������
	symbol *constant;		//�泣��������
	symbol ***Pointer_N;	//������ָ��Ķ�ά����
	symbol **Pointer_Ans;	//�͵�ָ���һά����
	
	formula(string *str_in, string str_ans, int k);
	formula();
	~formula();
	void plus_track_recursion();	//�ݹ麯��
	bool find_goal_symbol();		//�ҵ���һ���������ַ�
	void update_species();			//���ݵ�ǰ�Ľ�λ����֪
	void restore_species();
	bool contradiction();
	void PrintAnswer();
	bool CheckStatus();
	bool CarryCheck();
};