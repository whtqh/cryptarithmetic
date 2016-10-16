#include "symbol.h"
void symbol::set_impossible(int impossible_num)
{
	species_check[impossible_num] = -1;
	species_num--;
}
