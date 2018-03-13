#pragma once

#include <string>
#include "include_IO.h"

using namespace std;

namespace exercise_interview
{
	class Mstring
	{

	private:

		string name;

	public:

		Mstring() :name("default name")
		{}

		Mstring(string name) :name(name)
		{}

		void setname(string name)
		{
			this->name = name;
		}

		//assigment operator
		void operator = (const Mstring& m)  //const ref = readonly reference, no cost of copying //reference is const, not content (content should be as well i guess)
		{
			name = m.name;

			/*
			// The C way: https://stackoverflow.com/a/18299183
			int src[] = { 1, 2, 3, 4 };
			int dest[4];
			memcpy(dest, src, 4*sizeof(int)); // int is a POD

			// char* example: https://stackoverflow.com/a/24350094
			// deleting old char* https://stackoverflow.com/a/1408608
			*/

			/*
			//something like

			void operator = (const char* newName)
			{
				delete[] this.myName;
				int length = std::strlen(newName); //strlen is really for char*! //might need +1
				this.myName = new char[length];
				memcpy(this.myName, newName, length*sizeof(char)); //sizeof(char) = 1, so its technically not needed
			}
			*/

		}

		//stream operator, returns ostream
		friend ostream& operator<<(ostream& os, const Mstring& ms) 
		{
			os << ms.name; //ostream can only acces classes private member because declared as "friend"
			return os;
		}

		//conversion to string
		operator std::string() const
		{
			return name;
		}

	};

	void testMstring()
	{
		std::cout << __FUNCTION__ << std::endl;
		Mstring a, b("hello");
		std::cout << "a: " << a << std::endl;
		std::cout << "b: " << b << std::endl;

		a = b;
		std::cout << "a: " << a << std::endl;
		std::cout << "b: " << b << std::endl;

		a.setname("new name");
		std::cout << "a: " << a << std::endl;

		b.setname(a); //uses string conversion operator
		std::cout << "b: " << b << std::endl;

		Mstring c(a); 
		std::cout << "c: " << c << std::endl;

		//printf(c); //printf cant be overloaded!
	}

	/*
	//Interview Notes

	class mystring {
	private:
		string s;

	public:

		string getstring() { return s; }

		mystring() { s = "empty"; }

		mystring(string m) { s = m; }

		mystring(const mystring &m) { s = m.getstring(); }

		void operator =(const mystring &m)
		{
			s = m.getstring();
		}

		operator std::string() const { return s; }

	};

	void testmystring()
	{
		mystring a, b("hello");

		a = b;

		mystring c(a);

		//printf(c);
	}

	*/
}