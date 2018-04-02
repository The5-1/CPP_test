#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "include_IO.h"

/*
** Custom Smartpointer implementation + question for it on stackoverflow
** https://www.codeproject.com/Articles/15351/Implementing-a-simple-smart-pointer-in-c
** https://stackoverflow.com/questions/21569483/c-overloading-dereference-operators
*/


namespace exercise_implement_smartPointer
{
	using namespace std;

	class Person
	{
		int age;
		char* pName;

	public:
		Person() : pName(0), age(0)
		{
		}
		Person(char* pName, int age) : pName(pName), age(age)
		{
		}
		~Person()
		{
		}

		void Display()
		{
			printf("Name = %s Age = %d \n", pName, age);
		}

		void Shout()
		{
			printf("Heeellooo!");
		}
	};

	class PersonSP
	{
	private:
		Person * pData;
	
	public:
		PersonSP(Person* pValue) : pData(pValue)
		{

		}

		~PersonSP()
		{
			delete pData;
		}

		Person& operator* ()
		{
			return *pData;
		}

		Person* operator-> ()
		{
			return pData;
		}
	};


	/* Custom Smart Pointer ! */
	template < typename T > class SmartPointer
	{
		/* Goals:
		** 1.) Delete the object automatically
		** 2.) Allow direct access of the object
		** Problem:
		** - what if multiple SmartPointers use the same object?
		*/

	private:
		T * pData; // Generic pointer to be stored

	public:

		/* 1.) Delete the object automatically: */

		//Constructor takes a new person object
		SmartPointer(T* pValue) : pData(pValue)
		{

		}

		// destructor handles deletion
		~SmartPointer()
		{
			delete pData;
		}


		/* 2.) Direct access: Define the same operators a normal pointer has */

		/* dereferencing operator ( * )
		** returns the object in a way that it can be modified -> return a non-const ref!
		*/
		T& operator* ()
		{
			return *pData;
		}

		/* "structure dereference" operator ( -> )
		** Even though you would think myObject->prop does not return a pointer, the operator needs to return T*
		** The operator works in some special way, so this is just how it needs to be.
		*/
		T* operator-> ()
		{
			return pData;
		}
	};


	/* Reference Counting Helper Class */
	class RC
	{
	private:
		int count; // Reference count

	public:
		void AddRef()
		{
			// Increment the rc count
			count++;
		}

		int Release()
		{
			// Decrement the rc count and
			// return the rc count.
			return --count;
		}
	};


	/* Custom Shared Pointer ! */
	template < typename T > class SharedPointer
	{
	private:
		T * pData;       // pointer
		RC* rc; // Reference count

	public:
		// empty SharedPointer
		SharedPointer() : pData(0), rc(0)
		{			
			rc = new RC(); // Create a new rc 		
			rc->AddRef(); // Increment the rc count
		}

		// SharedPointer from some object
		SharedPointer(T* pValue) : pData(pValue), rc(0)
		{		
			rc = new RC(); // Create a new rc 	
			rc->AddRef(); // Increment the rc count
		}

		// Copy constructor
		SharedPointer(const SharedPointer<T>& sp) :
			pData(sp.pData), rc(sp.rc) // Copy the data and rc pointer
		{
			rc->AddRef(); // and increment the rc count
		}

		// Assignment operator
		SharedPointer<T>& operator = (const SharedPointer<T>& other)
		{
			if (this != &other) // Avoid self assignment
			{
				//Take care of the data currently in this shared pointer, since it will be overriden!

				// Since this data will be overriden, decrement the rc count
				if (this.rc->Release() == 0)
				{
					//and if rc become zero and nobody points at this anymore, delete this old data
					delete this.pData;
					delete this.rc;
				}

				this.pData = other.pData; // Copy the data and rc pointer
				this.rc = other.rc;
				this.rc->AddRef(); // and increment the rc count
			}
			return *this;
		}


		// Destructor
		~SharedPointer()
		{
			// Decrement the rc count, and if rc become zero delete the data
			if (rc->Release() == 0)
			{
				delete pData;
				delete rc;
			}
		}

		//derefence operator rentuns non-const ref
		T& operator* ()
		{
			return *pData;
		}

		//indirection must return T* 
		T* operator-> ()
		{
			return pData;
		}

	};


	void test0()
	{
		printf("1.) Manually delete object.\n");
		Person* pPerson = new Person("Scott", 25);
		pPerson->Display();
		delete pPerson;

		printf("2.) Special Smart-Pointer wrapper for Person.\n");
		PersonSP psp(new Person("Scott", 25));
		psp->Display(); //you can access person just like with a normal pointer!

		printf("3.) Generic Smart-Pointer holding a Person object.\n");
		SmartPointer<Person> sp(new Person("Scott", 25));
		sp->Display(); //you can access person just like with a normal pointer!


		printf("4.) Generic Smart-Pointer fails when two of them reference the same object.\n");
#if 0
		SmartPointer<Person> p1(new Person("Scott", 25));
		p1->Display();
		{
			SmartPointer<Person> p2 = p1;
			p2->Display();
			// Destructor of pw will be called since the scope ends...
		}
		printf("p1->Display() could not be called since the object was already deleted by p2.\n");
		p1->Display(); //the object p1 points to is gone, dangling pointer!	
#endif

		printf("5.) Shared Pointer.\n");
		SharedPointer<Person> p(new Person("Scott", 25));
		p->Display();
		{
			SharedPointer<Person> q = p;
			q->Display();
			// Destructor of q will be called here..

			SharedPointer<Person> r;
			r = p;
			r->Display();
			// Destructor of r will be called here..
		}
		p->Display();
		// Destructor of p will be called here 
		// and person pointer will be deleted

	}

}