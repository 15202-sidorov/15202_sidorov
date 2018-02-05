#include <iostream>
#include "Hashtables_2.h"
#include "Hash_test.h"


using namespace std;

void HashtableTest::SetUp()
{
	Hashtable h;
	my_val_1 = {.name = "Ilia", .age = 10, .weight = 11};
	my_val_2 = {.name = "Ivan", .age = 100, .weight = 150};
	my_val_3 = {.name = "Masha", .age = 140, .weight = 23};
	my_val_4 = {.name = "Dima", .age = 14, .weight = 23};
}

void HashtableTest::InsertValues()
{
	h.insert(my_val_1.name, my_val_1);
	h.insert(my_val_2.name, my_val_2);
	h.insert(my_val_3.name, my_val_3);
	h.insert(my_val_4.name, my_val_4);
}


TEST_F(HashtableTest,InitTest)
{
	ASSERT_EQ(true,h.insert(my_val_1.name, my_val_1));
	ASSERT_EQ(true,h.insert(my_val_2.name, my_val_2));
	ASSERT_EQ(true,h.insert(my_val_3.name, my_val_3));
	ASSERT_EQ(true,h.insert(my_val_4.name, my_val_4));
}

TEST_F(HashtableTest,ContainsTest)
{
	h.insert(my_val_1.name,my_val_1);
	EXPECT_EQ(true,h.contains(my_val_1.name));
	
	EXPECT_EQ(false,h.contains("Nobody"));
}

TEST_F(HashtableTest,EraseTest)
{
	h.insert(my_val_1.name,my_val_1);
	h.erase(my_val_1.name);
	EXPECT_EQ(false,h.contains(my_val_1.name));
}

TEST_F(HashtableTest,GetValueOperation)
{
	h.insert(my_val_1.name,my_val_1);
	EXPECT_EQ(my_val_1.age,h["Ilia"].age);
	EXPECT_EQ(my_val_1.weight,h["Ilia"].weight);
	
}

TEST_F(HashtableTest,GetValueOprationWithException)
{

	h.insert(my_val_1.name,my_val_1);
	
	EXPECT_EQ(my_val_1.age,h.at("Ilia").age);
	EXPECT_EQ(my_val_1.weight,h.at("Ilia").weight);
	
	try
	{
		h.at("Someone");
	}
	catch(int e)
	{
		ASSERT_EQ(-1,e);
	}

}


TEST_F(HashtableTest, CopyInitTest)
{

	InsertValues();

	Hashtable h2(h);

	EXPECT_EQ(h2["Ilia"].age,h["Ilia"].age);
	EXPECT_EQ(h2["Ivan"].age,h["Ivan"].age);
	EXPECT_EQ(h2["Masha"].age,h["Masha"].age);
	EXPECT_EQ(h2["Dima"].age,h["Dima"].age);

}

TEST_F(HashtableTest, OperatorsTest)
{
	InsertValues();

	Hashtable h2 = h;
	EXPECT_EQ(true, (h2 == h));
	EXPECT_EQ(false,(h2 != h));
}


TEST_F(HashtableTest,ClearTest)
{
	EXPECT_EQ(true,h.empty());
	
	h.clear();
	EXPECT_EQ(true,h.empty());

	SetUp();
	InsertValues();
	EXPECT_EQ(false,h.empty());
	h.clear();
	EXPECT_EQ(true,h.empty());
}

TEST_F(HashtableTest,SwapTest)
{
	Hashtable h2;
	

	h.insert(my_val_1.name, my_val_1);
	h.insert(my_val_2.name, my_val_2);
	h2.insert(my_val_3.name, my_val_3);
	h2.insert(my_val_4.name, my_val_4);

	h.swap(h2);

	EXPECT_EQ(my_val_1.age,h2["Ilia"].age);
	EXPECT_EQ(my_val_1.name,h2["Ilia"].name);
	EXPECT_EQ(my_val_1.weight,h2["Ilia"].weight);

	EXPECT_EQ(my_val_2.age,h2["Ivan"].age);
	EXPECT_EQ(my_val_2.name,h2["Ivan"].name);
	EXPECT_EQ(my_val_2.weight,h2["Ivan"].weight);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}