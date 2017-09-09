#pragma once

namespace exercise_initializerList
{
/*********************************************
http://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/
https://stackoverflow.com/questions/11584251/calling-constructor-of-another-class-through-initialization-list-having-problem
----------------------------------------------
- Instead of doing initilaization of class members in the constructor body...
- ... you do it in the "initializer list"
--> no copying of values happens


Two things can ONLY be done with the list!!!
1.) Non-static const data members:
- Class constants that differ per object can be set via initializer list only!

2.) Reference members:
- need to be initialited by initializer list
- can't have default values!


----------------------------------------------
lvalue = object that occupies identifyiable location in memory
rvalue = opposite of lvalue

*********************************************/


	class ID
	{
	public:
		int id;
		ID(int i) : id(i) {} //this class got no default constructor
	};

	class Inventory
	{
	public:
		int gold;

		const int slots; //constants must be initialized via initializer list!

		Inventory(int g = 0, int s = 10) : gold(g), slots(s) {} //initializer list with default value //the order does not matter, it takes the order they appear in the class

		int getGold() const { return gold; }
	};


	class Hero
	{
	public:

		int health;

		const int size;

		int &refID; //reference values cant have default values

		ID ID;

		Inventory inventory;

		Hero(int &ref, int id, int h = 100, int s = 1) : 
			health(h), 
			inventory(10000, 10), //calls default constructor of inventory
			size(s), //non static consts can only be set in list
			refID(ref), //references must be initialized in list
			ID(id) {} //classes without default construcor must be initialized in list


	};

}