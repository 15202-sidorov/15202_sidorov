#include <stdlib.h>
#include <iostream>
#include "Hashtables_2.h"
using namespace std;


int main()
{
	Hashtable h;
	Value my_val_1 = {.name = "Ilia", .age = 10, .weight = 11};
	Value my_val_2 = {.name = "Ivan", .age = 100, .weight = 150};
	h.insert(my_val_1.name, my_val_1);
	h.insert(my_val_2.name, my_val_2);
	h.print();
	return 0;
}
