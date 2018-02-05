#include "Hashtables_2.h"


Hashtable :: Hashtable(const Hashtable& another)
{
	delete [] full;
	delete [] bucket;
	full = new bool[another.size];
	bucket = new Value[another.size];
	size = another.size;
	load_factor = another.load_factor;
	
	// std copy
	for (int i = 0; i < another.size; i++)
	{
		full[i] = another.full[i];
		bucket[i] = another.bucket[i];
	}
}

void Hashtable :: Rehash()
{
	size_t old_size = size;
	size *= RESIZE_HT;
	load_factor = 0;
	Value *new_buckets = new Value[size]();
	bool *new_full_val = new bool[size]();
	int index = 0;
	for(int i = 0; i < old_size; i++)
	{
		if (full[i])
		{
			index = Hash_function(bucket[i].name);
			while(new_full_val[index])
			{
				index += PROBE;
				index %= size;
			}
			new_buckets[index] = bucket[i];
			new_full_val[index] = true;
			load_factor += 1.0/size;
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
	load_factor += (1.0/size);
	if (load_factor > MAX_LOAD_FACTOR)
	{
		Rehash();
	}
	
	int index = Hash_function(name);
	int start_index = index;
	while (full[index])
	{
		index += PROBE;
		index %= size;
		if (index == start_index)
		{
			Rehash();
		}
	}
	full[index] = true;
	bucket[index] = v;

	return true;
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
		index %= size;
	}
	
	if (full[index])
	{
		full[index] = false;
		bucket[index] = {};
		load_factor -= 1.0 / size;
		return 1;
	}
	return 0;
}

bool Hashtable :: contains(const Key& name) const
{
	int index = Hash_function(name);
	while ((bucket[index].name != name) && (full[index] != false))
	{
		index += PROBE;
		index %= size;
	}
	
	return (full[index]);
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

void Hashtable :: swap(Hashtable& h)
{
	Value *tmp_bucket = bucket;
	bool *tmp_full = full;
	size_t tmp_size = size;
	double tmp_load_factor = load_factor;

	full = h.full;
	bucket = h.bucket;
	size = h.size;
	load_factor = h.load_factor;

	h.bucket = tmp_bucket;
	h.full = tmp_full;
	h.size = tmp_size;
	h.load_factor = tmp_load_factor;
	 

	return;
}

Hashtable& Hashtable :: operator= (const Hashtable& h)
{
	if (&h == this)
	{
		return *this;
	}

	size = h.size;
	load_factor = h.load_factor;
	delete [] bucket;
	delete [] full;
	bucket = new Value[size];
	full =  new bool[size];

	// std copy
	for (int i = 0 ; i < size; i++)
	{
		bucket[i] = h.bucket[i];
		full[i] = h.full[i];
	}
	return *this;
}

Value& Hashtable :: operator[] (const Key& name) const
{
	int index = Hash_function(name);
	while ((bucket[index].name != name) && (full[index] != false))
	{
		index += PROBE;
		index %= size;
	}
	return bucket[index];
}


bool operator == (const Hashtable& a, const Hashtable& b)
{
	if (a.size != b.size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < a.size; i++)
		{
			if (a.full[i] == b.full[i])
			{
				if (!a.full[i])
				{
					continue;
				}
				else
				{
					if ((a.bucket[i].age != b.bucket[i].age)
							|| (b.bucket[i].weight != a.bucket[i].weight))
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool operator != (const Hashtable& a, const Hashtable& b)
{
	return !(a == b); 
}

bool Hashtable :: empty() const
{
	return (load_factor == 0);
}

Value& Hashtable :: at (const Key& name)
{
	try
	{
		if (!contains(name))
		{
			throw -1;
		}
	}
	catch(int)
	{
		std :: cout << "Does not contains name : " << name << std :: endl;
		throw -1;
	}
	
	return (*this)[name];
}

const Value& Hashtable :: at (const Key& name) const
{
	try
	{
		if (!contains(name))
		{
			throw -1;
		}
	}
	catch(int)
	{
		std :: cout << "Does not contains name : " << name << std :: endl;
		throw -1;
	}
	
	return (*this)[name];
}

size_t Hashtable :: get_size()
{
	return size;
}

Hashtable :: ~Hashtable()
{
	delete [] bucket;
	delete [] full;
}

