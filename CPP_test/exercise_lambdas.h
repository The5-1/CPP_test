#pragma once


#include <iostream>
#include <vector>
#include <algorithm> // for "for_each"
#include <stdlib.h> // for rand
#include <time.h> // for time


using namespace std;
using std::cout; //only skip the std:: prefix for cout and endl, cleaner than for whole std
using std::endl;

/****************************************************
https://arne-mertz.de/2015/10/new-c-features-lambdas/
-----------------------------------------------------
Use Case 1:
- function that is only needed once
- one-liner functions
- nested/local functions (capsuling of related stuff)
- hold state like function object
==========================================
Function Pointer:
- function needs to be defined outside the current scope
- does not hold state within the whole scope where it is called
- a function only holds state while called and then loses it at the end
------------------------------------------
Function Object:
- can hold state
- have to put a whole struct/class definition inside the scope where you need it
------------------------------------------
Lambda: 
- can hold state 
- no struct/class needed
--> generate function object on the fly (a "closure")
------------------------------------------

Lambda:
- starts with: []  //if here is no name before a [] pair, its a lambda
- parameters: (auto a, auto b)
- return type: -> int
Lambda with State:
- starts with: [&goldTreshold] //make a exterior variable accessible inside the lambda, e.g. as reference, or as copy


****************************************************/

namespace exercise_lambdas 
{

	class Hero
	{
	public:
		int gold;

		Hero() :gold(0) {}

		Hero(int g) :gold(g) {}

	};

	//function pointer: it's a normal function that will be pointed to
	//--> needs to be defined outside the actual scope you want to use it
	bool hasMoreGold(Hero const& h1, Hero const& h2)
	{
		return h1.gold < h2.gold;
	}

	void functionPointer01()
	{
		vector<Hero> heroes;
		for (int i = 1; i < 10; ++i) {
			auto h = Hero(i);
			heroes.push_back(h);
		}

		//use a function pointer to pass to the sort function
		sort(heroes.begin(), heroes.end(), &hasMoreGold);
	}
	


	void functionObject01()
	{
		//a function object that can hold state (like any object does)
		struct HasLessGoldThan {
			unsigned threshold;

			HasLessGoldThan(unsigned ui) : threshold(ui) {}

			bool operator()(Hero const& hero) {
				return hero.gold < threshold;
			}

		};

		vector<Hero> heroes;
		for (int i = 1; i < 10; ++i) {
			auto h = Hero(i);
			heroes.push_back(h);
		}

		//use the function object and set its state
		vector<Hero>::iterator newEnd = std::remove_if(heroes.begin(), heroes.end(), HasLessGoldThan(5u));

		heroes.erase(newEnd, heroes.end());

	}



	void lambda_basic()
	{
		//use a lambda in-place, no state here yet!
		vector<Hero> heroes;
		for (int i = 1; i < 10; ++i) {
			auto h = Hero(i);
			heroes.push_back(h);
		}

		std::sort(heroes.begin(), heroes.end(),

			//Lambda
			//the whole lambda is defined directly in the sort() call
			[](Hero const& h1, Hero const& h2) -> bool {
				return h1.gold < h2.gold;
			}

		);

	}


	void lambda_scope()
	{
		//Now a lambda that acutally holds state
		vector<Hero> heroes;
		for (int i = 1; i < 10; ++i) {
			auto h = Hero(i);
			heroes.push_back(h);
		}

		unsigned goldThreshold = 5u; //something we calculated

		auto newEnd = remove_if(begin(heroes), end(heroes),
			[goldThreshold] //here we make the external variable accessible by the lambda! It's a copy, but could be a reference too!
				(Hero const& hero) 
			{
				return hero.gold < goldThreshold;
			}
		);

		heroes.erase(newEnd, heroes.end());
	}


	void lambda_reference()
	{
		//Now a lambda that gets references passed and actually modifies the state within the entire scope!
		vector<Hero> heroes;
		for (int i = 1; i <= 100; ++i) {
			auto h = Hero(i*i);
			heroes.push_back(h);
		}
		//cout << heroes.size() << endl;

		unsigned richCounter = 0;
		unsigned poorCounter = 0;

		for_each(begin(heroes), end(heroes),
			// capture both counters by reference
			[&richCounter, &poorCounter](Hero const& hero) 
			{
				auto const& gold = hero.gold;
				if (gold > 1000) {
					++richCounter; //modify the state of the outside scope!
				}
				else if (gold < 10) {
					++poorCounter;  //modify the state of the outside scope!
				}
			}
		);

		cout << richCounter << " rich heroes and "
			<< poorCounter << " poor heroes found!\n";
	}



	/*
	void lambda02()
	{
		// Create a vector object that contains 10 elements.  
		vector<int> v;
		for (int i = 1; i < 10; ++i) {
			v.push_back(i);
		}

		// Count the number of even numbers in the vector by   
		// using the for_each function and a lambda.  
		int evenCount = 0;
		for_each(v.begin(), v.end(), 
				[&evenCount](int n) //lambda start
				{
					cout << n;
					if (n % 2 == 0) {
						cout << " is even " << endl;
						++evenCount;
					}
					else {
						cout << " is odd " << endl;
					}
				} //lambad end
		); //end of for loop definition

		// Print the count of even numbers to the console.  
		cout << "There are " << evenCount
			<< " even numbers in the vector." << endl;
	}


	class FunctorClass
	{
	public:
		// The required constructor for this example.  
		explicit FunctorClass(int& evenCount)
			: m_evenCount(evenCount) { }

		// The function-call operator prints whether the number is  
		// even or odd. If the number is even, this method updates  
		// the counter.  
		void operator()(int n) const {
			cout << n;

			if (n % 2 == 0) {
				cout << " is even " << endl;
				++m_evenCount;
			}
			else {
				cout << " is odd " << endl;
			}
		}

	private:
		// Default assignment operator to silence warning C4512.  
		FunctorClass& operator=(const FunctorClass&);

		int& m_evenCount; // the number of even variables in the vector.  
	};

	void function_class01()
	{
		// Create a vector object that contains 10 elements.  
		vector<int> v;
		for (int i = 1; i < 10; ++i) {
			v.push_back(i);
		}

		// Count the number of even numbers in the vector by   
		// using the for_each function and a function object.  
		int evenCount = 0;
		for_each(v.begin(), v.end(), FunctorClass(evenCount));

		// Print the count of even numbers to the console.  
		cout << "There are " << evenCount
			<< " even numbers in the vector." << endl;
	}
	*/


	void test()
	{
		functionPointer01();
		functionObject01();

		lambda_basic();
		lambda_scope();
		lambda_reference();
	}

}
