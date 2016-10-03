#include "Hashtables_2.h"
#include <iostream>

using namespace std;

#define PROBE 1
#define RESIZE_HT 2
#define MAX_LOAD_FACTOR (2.0 / 3)

Hashtable :: Hashtable(const Hashtable& another)
{
	full = new bool[another.size];
	bucket = new Value[another.size];
	size = another.size;
	load_factor = another.load_factor;
	
	for (int i = 0; i < another.size; i++)
	{
		full[i] = another.full[i];
		bucket[i] = another.bucket[i];
	}
}

void Hashtable :: Rehash()
{
	int old_size = size;
	size *= RESIZE_HT;
	load_factor *= old_size / size;
	Value *new_buckets = new Value[size]();
	bool *new_full_val = new bool[size]();
	int index = 0;
	for(int i = 0; i < old_size; i++)
	{
		if (full[i])
		{
			index = Hash_function(bucket[i].name);
			while(full[index])
			{
				index += PROBE;
			}
			new_buckets[index] = bucket[i];
			new_full_val[index] = true;
		}
	}
	delete [] bucket;
	delete [] full;
	bucket = new_buckets;
	full = new_full_val;
	return;
}

bool Hashtable :: insert(const Key& name, const Value& v)
{
	load_factor += 1.0 / size;
	if (load_factor >= MAX_LOAD_FACTOR)
	{
		Rehash();
	}
	
	int index = Hash_function(name);
	int start_index = index;
	while (full[index])
	{
		index += PROBE;
		if (index == start_index)
		{
			Rehash();
		}
		if (index >= size)
		{
			index -= size;
		}
	}
	full[index] = true;
	bucket[index] = v;

	return 1;
}

int Hashtable :: Hash_function(const Key& name) const
{
	int sum = 0;
	for (int i = 0; i < name.size(); i++)
	{
		sum += (int)name[i];
	}
	
	return (sum % size); 
}

bool Hashtable :: erase(const Key& name)
{
	int index = Hash_function(name);
	while ((bucket[index].name != name) && (full[index] != 0))
	{
		index += PROBE;
	}
	
	if (full[index])
	{
		full[index] = false;
		bucket[index] = {};
		load_factor -= 1.0 / size;
		return 1;
	}
	else
	{
		return 0;
	}
}

bool Hashtable :: contains(const Key& name) const
{
	int index = Hash_function(name);
	while ((bucket[index].name != name) && (full[index] != false))
	{
		index += PROBE;
	}
	if (full[index])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Hashtable :: clear()
{
	for (int i = 0; i < size; i++)
	{
		bucket[i] = {};
		full[i] = false;
	}
	load_factor = 0;
}

void Hashtable :: print()
{
	cout << "Printing hashtable :" << endl;
	for (int i = 0; i < size; i++)
	{
		if (full[i])
		{
			cout << "Index : " << i << "\nName : " << bucket[i].name << "\nAge value : " << bucket[i].age << endl;
		}
	}
}

Hashtable :: ~Hashtable()
{
	delete [] bucket;
	delete [] full;
}

