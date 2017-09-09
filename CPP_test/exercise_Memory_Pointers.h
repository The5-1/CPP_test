#pragma once
#include <iostream>
#include <memory> //not memory.h (.h is the c header)
#include <vector>

namespace exercise_Memory_Pointers
{

/**************************************************
https://stackoverflow.com/questions/395123/raii-and-smart-pointers-in-c
---------------------------------------------------
Automatic Variables:
- get deleted when out of scope
--> stack variables are automatic
--> class members are automatic (destructor of those members will be called)
But NOT pointer members!
- class members that are pointers, only the pointer itself is deleted
--> the object under the pointer will stay on the heap and block it!!!
- smart pointers take care of such pointer objects and delte them when nothing points to them anymore

//https://stackoverflow.com/questions/10836591/class-members-and-explicit-stack-heap-allocation
Classes: Normal Members and Pointer Members:
- normal members are always in the same memory as their owner
- pointer members are not owned by the class thus are on the heap
- normal members are deleted when the owner is deleted
- pointer members are not deleted, but the pointer to them, making them lost memory zombies

Heap allocation:
- allocate memory on the heap ("new" operator, constructor)
- store the pointer to that memory
- call "delete" on the pointer to execute the destructor
Problem:
- function returns before destructor is called
- function throws exception before destructor is called

RAII Idea:
- wrap a stack allocated object arround your heap one
- the stack-objects destructor calls your heap-objects one
- for simple ressources you do not want to write a wrapper class all the time
--> this is where smart pointers come in


SmartPointers:
- wrap a RAII object arround heap-allocated resources

https://msdn.microsoft.com/en-us/library/hh279674.aspx#Kinds%20of%20Smart%20Pointers
unique_ptr:
- allows only one unique_ptr to the object
- deletes the object when the unique_ptr is delted
- otherwise, more normal pointers can point to that object (no weak_ptr counterpart for it)
- can only be accessed by reference, not by value/copy
- another unique_ptr can be set to the object with move(), the old unique_ptr will be reset to nullprt

shared_ptr:
- e.g. when returning a copy of a pointer from a list/container object
- gets deleted when nothing points to it anymore
- e.g. when you have 2 objects with list with common objects
--> when one is deleted, it also deletes all objects that exclusively were pointed to by itself
--> while the other list still keeps the objects it needs

weak_ptr:
- intended for breaking cyclic references that would increase reference count of shared_ptr infinitely
- point to a shared_ptr object without signing yourself up for owning it
- e.g. for a cache: keep an object arround for access, but don't force its existence





**************************************************/


	void memoryLeak()
	{
		//the OS frees all memory when a process terminates
		//but while a process runs, leaks fill the memory

		std::cout << __FUNCTION__ << std::endl;
		class Dummy
		{
		public:
			long x;
			Dummy() : x(x) {}
			//Dummy() : x(100) {}
			Dummy(double in) : x(in) {} //"member initializer list"
		};

		class DummyA : Dummy
		{
		public:
			int i;
			DummyA(int in = 0) : i(in), Dummy() {}

		};

		fprintf(stdout, "See the RAM filling! (In Task Manager)\n");
		for (int i = 0; i < 1000000; i++)
		{
			Dummy* d = new Dummy(i); //initialize on the heap
			d = nullptr; //bend the pointer elsewhere, we cant go back
			//OR: return here and forget to delete before
			//OR: an exception occurs and exits the loop before delete happens
			delete d; //wont work since we already messed up the pointer
		}
		fprintf(stdout, "Event though the scope of the loop ended, the stuff on the heap is still there.\n");

		fprintf(stdout, "And now without messing up the pointer...\n");
		for (int i = 0; i < 1000000; i++)
		{
			DummyA* da = new DummyA(); //uses DummyA(int in = 0 )
			delete da; //call destructor
			da = nullptr; //set the pointer to null just so everyone knows its not there anymore
		}
		fprintf(stdout, "...RAM did not change this time!\n");

		fprintf(stdout, "Using the Stack rather than the heap...\n");
		for (int i = 0; i < 1000000; i++)
		{
			Dummy s(i); //initialize a class on the stack
		}
		fprintf(stdout, "...frees itself when it goes out of scope!\n");

	}


	void testRAII()
	{
		/*
		Scope Bound Ressource Management
		--------------------------------
		RAII = "Resource Acquisition is Initialisation"
		= RABITS = "Resources are bound irreversibly to scope"
		= SBRM = "Scope Bound Ressource Management"
		http://www.tomdalling.com/blog/software-design/resource-acquisition-is-initialisation-raii-explained/
		When you heap allocate something and a exception is thrown before the destructur, the distructor wont ever be called
		Same for opening a file and never closing it.

		Instead do:
		- allocate on the stack
		- in the constructor, allocate everything, not later (if possible)
		- the destructor releases all resources
		--> when you leave the scope the stack-allocated object calls its destructor automatically
		--> and that destructor calles your heap-objects destructor in turn

		======================================
		Wrap a stack allocated object arround your heap one
		so your destructor gets called when the stack object leaves scope.
		======================================

		---> smart pointers do this for you!
		*/

		class OpenFile {
		public:
			OpenFile(const char* filename) {
				//throws an exception on failure
				_file.open(filename);
			}

			~OpenFile() {
				//free resources
				_file.close();
			}

			std::string readLine() {
				return "hello";
			}

		private:
			std::fstream _file;

		};

		struct local
		{
			static std::string firstLineOf_save(const char* filename) {
				OpenFile f("RAII_example.txt"); //stack allocated
				return f.readLine();
				//File closed here. `f` goes out of scope and destructor is run.
			}

			static std::string firstLineOf_unsave(const char* filename) {
				OpenFile* f = new OpenFile("RAII_example.txt"); //heap allocated
				return f->readLine();
				//DANGER! Destructor is never run, because `f` is never deleted
			}
		};
	}


	void stackVSheap()
	{
		//https://stackoverflow.com/questions/395123/raii-and-smart-pointers-in-c

		struct local
		{
		public:
			static std::string returnByCopy() {
				std::cout << __FUNCTION__ << std::endl;
				std::string str("hello"); //string on stack is fine
				return str; //returns the string by value -> creates copy
			}

			static std::string* returnByReferenceToStack() {
				std::cout << __FUNCTION__ << std::endl;
				std::string str("hello"); //string on stack wont live long enough!
				return &str; //!by the time we return the string is gone
			}

			static std::string* returnByPointerToHeap() {
				std::cout << __FUNCTION__ << std::endl;
				std::string* str = new std::string("hello"); //on the heap it lives on
				return str; //we return it properly, but never make sure it is deleted!
			}

		};
		

		std::cout << local::returnByCopy() << std::endl;

		std::cout << local::returnByReferenceToStack() << " <-- the stack-allocated string is gone already!" <<std::endl; //de-referencing here would crash!

		std::cout << *local::returnByPointerToHeap() << std::endl; //de-reference (*) this pointer to get the string!
	}


	class Hero
	{
	public:
		//this member will be in the same memory as the owner, stack or heap
		int health; //members are "automatic variable", get deleted when owner is destroyed
		
		//this object will be on the heap, no matter whether the hero is on the stack itself
		Hero* companion_normal; //the pointer will be delted, but not the object below it! We need to clean it in the destructor.
		unique_ptr<Hero> companion_smart; //the object on heap will delete it once the unique_ptr itself is deleted

		Hero(int health = 100) : health(health) {}
		
		~Hero()
		{
			delete companion_normal; //now when Hero is deleted, the companion will be too
		}

		void makeCompanions()
		{
			companion_normal = new Hero(health / 2);
			companion_smart = make_unique<Hero>(health / 2);
		}
	};



	//factories should always return unique_ptr because its the most efficient
	//unique_ptr is designed to be efficiently converted to shared_ptr
	//the implicit move() return can be assigned to a shared_ptr directly! 
	unique_ptr<Hero> heroFactory(int health)
	{
		return make_unique<Hero>(health); //this implicitly move() the pointer to the variable the return is stored in, be it unique or shared ptr!
	}



	void testUnique_ptr()
	{
		auto hero = make_unique<Hero>(200);
		auto newOwner = move(hero); //this resets the old pointer

		std::wcout << "hero pointer was reset when transfering owernship!" << std::endl;
		std::cout << "new owner: " << newOwner->health << std::endl;

		vector<unique_ptr<Hero>> Heroes;
		Heroes.push_back(heroFactory(50));
		Heroes.push_back(heroFactory(110));
		Heroes.push_back(heroFactory(80));

		//pass by reference, pass by copy would not work with unique_ptr
		for (const auto& hero : Heroes)
		{
			cout << "health: " << hero->health << std::endl;
		}
	}

	void testShared_ptr()
	{
		vector<shared_ptr<Hero>>* EnemySpawner = new vector<shared_ptr<Hero>>();
		EnemySpawner->push_back(heroFactory(50)); //the unique pointer factory seamlessly works with shared poitners too, due to implicit move()
		EnemySpawner->push_back(heroFactory(110));
		EnemySpawner->push_back(heroFactory(80));
		EnemySpawner->push_back(heroFactory(60));
		EnemySpawner->push_back(heroFactory(200));

		cout << "EnemySpawner: " << endl;
		for (const auto& hero : *EnemySpawner)
		{
			cout << "health: " << hero->health << std::endl;
		}

		weak_ptr<Hero> weak = EnemySpawner->at(1); //weak ponter conversion by simple assignment

		vector<shared_ptr<Hero>> PlayerDominatedUnits;
		PlayerDominatedUnits.push_back(EnemySpawner->at(0));
		PlayerDominatedUnits.push_back(EnemySpawner->at(3));

		cout << "weak pointer: " << weak.lock()->health << endl; //weakptr needs to be locked while accessing it, so it cant be deleted just that moment

		cout << PlayerDominatedUnits.at(0).use_count() << " shared_ptr are pointing to hero with health " << PlayerDominatedUnits.at(0)->health << endl;
		delete EnemySpawner; //enemy spawner decayed and is deleted
		cout << PlayerDominatedUnits.at(0).use_count() << " shared_ptr are pointing to hero with health " << PlayerDominatedUnits.at(0)->health << endl;

		if (weak.expired()) cout << "weak pointer does not point to anything anymore" << endl;


		cout << "PlayerDominatedUnits still exist: " << endl;
		for (const auto& hero : PlayerDominatedUnits)
		{
			cout << "health: " << hero->health << std::endl;
		}

	}


	void test()
	{
		testRAII();
		stackVSheap();
		testUnique_ptr();
		testShared_ptr();
	}

}