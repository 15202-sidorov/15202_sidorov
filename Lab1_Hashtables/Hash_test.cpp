#include <stdlib.h>
#include <iostream>
#include "Hashtables_2.h"
using namespace std;
#include "gtest/gtest.h"



TEST(HashtableTest,InitTest)
{
	Hashtable h;
	Value my_val_1 = {.name = "Ilia", .age = 10, .weight = 11};
	Value my_val_2 = {.name = "Ivan", .age = 100, .weight = 150};
	Value my_val_3 = {.name = "Masha", .age = 140, .weight = 23};
	Value my_val_4 = {.name = "Dima", .age = 14, .weight = 23};

	ASSERT_EQ(true,h.insert(my_val_1.name, my_val_1));
	ASSERT_EQ(true,h.insert(my_val_2.name, my_val_2));
	ASSERT_EQ(true,h.insert(my_val_3.name, my_val_3));
	ASSERT_EQ(true,h.insert(my_val_4.name, my_val_4));
}

TEST(HashtableTest,ContainsTest)
{
	Hashtable h;
	Value my_val_1 = {.name = "Ivan", .age = 10, .weight = 11};
	h.insert(my_val_1.name,my_val_1);
	EXPECT_EQ(true,h.contains("Ivan"));
	
	EXPECT_EQ(false,h.contains("Nobody"));
}

TEST(HashtableTest,EraseTest)
{
	Hashtable h;
	Value my_val_1 = {.name = "Ilia", .age = 10, .weight = 11};
	h.insert(my_val_1.name,my_val_1);
	h.erase("Ilia");
	EXPECT_EQ(false,h.contains("Ilia"));
}

TEST(HashtableTest,GetValueOperation)
{
	Hashtable h;
	Value my_val_1 = {.name = "Ilia", .age = 10, .weight = 11};
	h.insert(my_val_1.name,my_val_1);
	EXPECT_EQ(my_val_1.age,h["Ilia"].age);
	EXPECT_EQ(my_val_1.weight,h["Ilia"].weight);
	
}

TEST(HashtableTest,GetValueOprationWithException)
{
	Hashtable h;
	Value my_val_1 = {.name = "Ivan", .age = 10, .weight = 11};
	h.insert(my_val_1.name,my_val_1);
	
	EXPECT_EQ(my_val_1.age,h.at("Ivan").age);
	EXPECT_EQ(my_val_1.weight,h.at("Ivan").weight);
	
	try
	{
		h.at("Someone");
	}
	catch(int e)
	{
		ASSERT_EQ(-1,e);
	}

}


TEST(HashtableTest, CopyInitTest)
{
	Hashtable h;
	Value my_val_1 = {.name = "Ilia", .age = 10, .weight = 11};
	Value my_val_2 = {.name = "Ivan", .age = 100, .weight = 150};
	Value my_val_3 = {.name = "Masha", .age = 140, .weight = 23};
	Value my_val_4 = {.name = "Dima", .age = 14, .weight = 23};
	

	h.insert(my_val_1.name, my_val_1);
	h.insert(my_val_2.name, my_val_2);
	h.insert(my_val_3.name, my_val_3);
	h.insert(my_val_4.name, my_val_4);

	Hashtable h2(h);

	EXPECT_EQ(h2["Ilia"].age,h["Ilia"].age);
	EXPECT_EQ(h2["Ivan"].age,h["Ivan"].age);
	EXPECT_EQ(h2["Masha"].age,h["Masha"].age);
	EXPECT_EQ(h2["Dima"].age,h["Dima"].age);

}

TEST(HashtableTest, OperatorsTest)
{
	Hashtable h;
	Value my_val_1 = {.name = "Ilia", .age = 10, .weight = 11};
	Value my_val_2 = {.name = "Ivan", .age = 100, .weight = 150};
	Value my_val_3 = {.name = "Masha", .age = 140, .weight = 23};
	Value my_val_4 = {.name = "Dima", .age = 14, .weight = 23};
	

	h.insert(my_val_1.name, my_val_1);
	h.insert(my_val_2.name, my_val_2);
	h.insert(my_val_3.name, my_val_3);
	h.insert(my_val_4.name, my_val_4);

	Hashtable h2 = h;
	EXPECT_EQ(h2,h);
	EXPECT_EQ(false,(h2 != h));
}


TEST(HashtableTest,ClearTest)
{
	Hashtable h;
	EXPECT_EQ(true,h.empty());
	
	h.clear();
	EXPECT_EQ(true,h.empty());
}



int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}