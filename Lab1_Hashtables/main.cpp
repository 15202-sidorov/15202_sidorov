#include <stdlib.h>
#include <iostream>
#include "Hashtables_2.h"
using namespace std;


int main()
{
	Hashtable h;
	Value my_val_1 = {.name = "Ilia", .age = 10, .weight = 11};
	Value my_val_2 = {.name = "Ivan", .age = 100, .weight = 150};
	Value my_val_3 = {.name = "Masha", .age = 140, .weight = 23};
	Value my_val_4 = {.name = "Dima", .age = 14, .weight = 23};
	h.insert(my_val_1.name, my_val_1);
	h.insert(my_val_2.name, my_val_2);
	h.insert(my_val_3.name, my_val_3);
	cout << h.contains("Ilia") << endl;
	cout << h.contains("Masha") << endl;
	cout << h.contains("smt") << endl;
	h.print();
	cout << "Erasing"<< endl;
	h.erase("Masha");
	cout << h.contains("Masha") << endl;
	h.print();

	//cout << h["Masha"].age << endl;

	try
	{
		cout << "Ilia's age : "<< h.at("Ilia").age << endl;
	}
	catch(int)
	{
		return -1;
	}

	return 0;
}
