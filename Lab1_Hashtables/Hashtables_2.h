
#if !defined(HASH_2)
#define HASH_2

#define HASHTABLE_INIT_SIZE 2
#define PROBE 1
#define RESIZE_HT 2
#define MAX_LOAD_FACTOR (2.0/3)

#include <iostream>
#include <assert.h>
#include <stdlib.h>

/*
	Key is string, can be the name of a student.
*/

typedef std::string Key;

/*
	struct VALUE is the value in hashtable.
	Consists of Key and corresponding elements.
*/

typedef 
	struct VALUE
	{
		Key name;
		int age;
		int weight;
	}Value;
/*
	class Hashtable
	
	Agorithm: 
			Liniar probe algorithm is used to place data.
			All needed paremeters are listed in these definitions : 
				Max load factor : MAX_LOAD_FACTOR
				Probe : PROBE
	Size: 
			Bytes allocated for keeping information
			Starting value is defined in HASHTABLE_INIT_SIZE.

	Rehashing:
			Gets more memory for hashtable, multipling its size in value which is
		placed in RESIZE_HT definition.
*/

class Hashtable
{
public :
	//Constructors.
	Hashtable(){};
	//Copy consturor.
	Hashtable( const Hashtable& );
	
	/*
		Inserting the key in table.
		Returns the bool value which shows the success of the operation.	
	*/
	bool insert(const Key& , const Value&);

	// Clears all table, setting all buckets to 0.
	void clear();

	/*
		Erasing the element with the key - name.
		0 means the name is not found.
	*/
	bool erase( const Key& );

	// Checks out whether the element is in the table.
	bool contains(const Key&) const;

	/*
		Swaps the hashtable with h hashtables
		These function swaps all arraies just swaping the pointers,
		unlike std::swap function which makes it better for the perpose.
	*/
	void swap(Hashtable&);

	//Common assignment operator
	Hashtable& operator= (const Hashtable&);

	/*
		Returns the value placed in hashtable for key - name
		if no such name in table - behavior is undefined.
	*/
	Value& operator[] (const Key&);

	// Returns the current size of hashtable
	double get_load_factor() const;

	/*
		Returns the value of the name
		Trows an exception if name is not found
	*/
	Value& at (const Key& name);

	/*
		Checks out wether the hashtable is empty.
		Returns true if it is empty.
	*/
	bool empty() const;

	/*
		Returns current allocated memory
	*/
	size_t get_size();
	
	friend bool operator == (const Hashtable&, const Hashtable&);
	friend bool operator != (const Hashtable&, const Hashtable&);


	//Distructors.
	~Hashtable();

	void print();

private:
	int Hash_function(const Key& name) const;
	void Rehash();
	
	Value *bucket = new Value[HASHTABLE_INIT_SIZE]();
	int size = HASHTABLE_INIT_SIZE;
	bool *full = new bool[HASHTABLE_INIT_SIZE]();
	double load_factor = 0;
};

#endif