#if !defined(HASH_2)
#define HASH_2

#define HASHTABLE_INIT_SIZE 10

#include <iostream>

typedef std::string Key;

typedef 
	struct VALUE
	{
		Key name;
		int age;
		int weight;
	}Value;


class Hashtable
{
public :
//Constructors
	Hashtable(){};
//Copy consturor
	Hashtable(const Hashtable& another);

//Inserting the key in table
//Returns the bool value which shows the success of the operation	
	bool insert(const Key& name, const Value& v);

//Clears all table, setting all buckets to 0
	void clear();

//Erasing the element
//0 means the name is not found
	bool erase(const Key& name);

//Checks out whether the element is in the table
	bool contains(const Key& name) const;

	void print();

//Distructors
	~Hashtable();

private:
//Hash function calculates the place in hashtable of a key	
	int Hash_function(const Key& name) const;
//Liniar probing rehashing	
	void Rehash();
//The array of all values kept in hashtable	
//Initial values are all 0
	Value *bucket = new Value[HASHTABLE_INIT_SIZE]();
//Current capacity of hashtable	
	int size = HASHTABLE_INIT_SIZE;
//Array shows which buckets are currently empty and which are not
//Initial value are all 0
	bool *full = new bool[HASHTABLE_INIT_SIZE]();
	double load_factor = 0;
};

#endif