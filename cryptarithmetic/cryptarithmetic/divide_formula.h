#pragma once
#include "formula.h"
using namespace std;

class divide_formula
{
	public:
		int *N;								//����ÿһ�е��ַ�����
		int *R;

		int NK;								//������
		
		int N_Ans_Len;					//�͵ĳ���
		int N_Add_LenMax;			//��������ĳ���
		int R_Add_LenMax;			//��������ĳ���

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
		//Add remainder from multiple
		symbol ***Pointer_R;		//������ָ��Ķ�ά����

		symbol **Pointer_Ans;		//�͵�ָ���һά����
		symbol **Pointer_Up;		//��������ָ���һά����
		symbol **Pointer_Down;	//������ָ���һά����

		/*						DEFGH						<-	str_down
	str_up  ABCD | XXXXXXXXXXXX			<-	str_ans
						 /	XXXXX							--->[4]
							  SDAFR			--->[4]
							  XXFRF						--->[3]
								 XFAD			--->[3]
								 FDSA						--->[2]
								   RTRW		--->[2]
								   FADS						--->[1]
								     FRER		--->[1]
									 FADS					--->[0]		of str_in[][]
									   FDS		--->[0]		<-str_remain[][]
		*/



		divide_formula(string str_up, string str_down, string *str_in, string *str_remain, string str_ans);
		//
		~divide_formula();
		void divide_track_recurison();

		bool find_goal_symbol();		//�ҵ���һ���������ַ�
		void update_species();			//���ݵ�ǰ�Ľ�λ����֪
		void restore_species();
		bool contradiction();
		void PrintAnswer();
		bool CheckStatus();
		bool CarryCheck();
};