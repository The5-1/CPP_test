#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

using namespace std;


namespace exercise_forLoops_Functors
{
/********************************************
https://stackoverflow.com/questions/2047414/advantages-of-stdfor-each-over-for-loop
https://stackoverflow.com/questions/11956374/for-loop-vs-stdfor-each-with-lambda
https://stackoverflow.com/questions/9994421/preferred-standard-use-range-based-for-or-stdfor-each

Range-Based for:
for(auto x : list){}
- readable, easy
- continue and break are available
- iterates over the whole list

ForEach:
std::for_each(begin,end,functor);
- returns the functor object, so you can return the state gathered inside the loop
--> you dont have to create variables outside the loop, they are part of the functor object
- since the loop body can be a functor class, you can reuse the implementation
--> BUT: #include <algorithm> got plenty of iterating algorithms already anyways
- variable range to iterate over
- can be overloaded to be more efficient with custom, multi-dimensional containers
--> see: https://stackoverflow.com/questions/11956374/for-loop-vs-stdfor-each-with-lambda
- CON: no continue and break from loop because it needs a functor (return breaks, workarrounds for continue)
- CON: debugging breakpoint can not be set (would be inside functor)

Other <algorithm> iterators to consider:
- find, sort, partition, copy_replace_if
- parallel execution


Functors:
https://stackoverflow.com/questions/317450/why-override-operator
- implement "operator()"
- is a function-object that holds state
- e.g. count sum in for_each loops


********************************************/



	class Hero
	{
	public:
		string name;
		int health;

		Hero(string s = "none", int h = 100) :name(s), health(h) {}
	};


	void test_rangeBasedFor()
	{

		int x[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		for (auto y : x) { //auto is good style, but using a copy is not
			cout << y << " ";
		}
		cout << endl;

		for (const auto &y : x) { //readonly reference instead of copy
			cout << y << " ";
		}
		cout << endl;


		vector<Hero> Heroes;
		for (int i = 0; i <= 10; i++)
		{
			Heroes.push_back(Hero(string("hero" + to_string(i)),100+10*i));
		}

		for (const auto &h : Heroes) //pass by reference
		{
			cout << h.name << ": " << h.health << endl;
		}
	}

	void test_forEach()
	{
		vector<Hero> Heroes;
		for (int i = 0; i <= 10; i++)
		{
			Heroes.push_back(Hero(string("hero" + to_string(i)), 100 + 10 * i));
		}


		//functor object can hold state!
		//https://stackoverflow.com/questions/9994421/preferred-standard-use-range-based-for-or-stdfor-each
		struct myFunctor
		{
			int sum = 0;

			void operator()(const Hero &h) { sum += h.health; } //overloading () creates the functor

		};

		//std::for_each returns the functor and the state it gathered during the loop!
		auto returnedFunctor = std::for_each(Heroes.begin(), Heroes.end(), myFunctor());
		cout << "returned Functor sumed health: " << returnedFunctor.sum << endl;

		//not sure what happens for lambdas...
		auto returnedLambda = std::for_each(Heroes.begin(), Heroes.end(), 
			[](Hero h) {
				int i = 0;
				i++;
			}
		);



	}

	void test()
	{
		test_rangeBasedFor();
		test_forEach();
	}
}