#pragma once

#include <string>
#include "include_IO.h"

using namespace std;

namespace exercise_interview
{
	//http://www.cplusplus.com/doc/tutorial/ntcs/
	//https://stackoverflow.com/questions/16511706/simple-string-implementation-in-c
	//https://stackoverflow.com/questions/18693866/how-to-interpret-operator-const-char-in-operator-overloading



	//Boilerplate code, could pull out the whole char assignment stuff into a helper function

	class CharString 
	{
	private:
		char* chars;

	public:

		//default constructor
		CharString()
		{
			chars = new char[1];
			chars[0] = '\0';
		}

		//constructor that gets passed a string literal
		CharString(char* text)
		{
			int length = strlen(text)+1;  // +1 for the \0
			chars = new char[length];
			strcpy(chars, text);
		}

		//Copy Constructor
		CharString(const CharString& other)
		{
			delete[] this->chars; //delete old value
			int length = strlen(other.chars)+1; //can actually access private members in copy constructor!
			chars = new char[length];
			strcpy(chars, other.chars);
		}

		
		//destructor
		~CharString()
		{
			if (chars != nullptr)
			{
				if (strlen(chars) > 1) delete[] chars;
				else delete chars;
			}
		}
		

		//implicit conversion operator (explicit keyword for explicit)
		//this can cause issues eg with a = b, both are treated as char* pointer and a points to the same obejct as b afterwards
		operator const char *()
		{
			return (this->chars);
		}

		// the existence of the = operator prevents a = b becoming char* = char* due to implicit conversion
		CharString& operator =(const CharString& other)
		{

			if (this != &other) //compare with adress of other
			{
				delete[] this->chars; //delete old value
				int length = strlen(other.chars) + 1; //can actually access private members in copy constructor!
				chars = new char[length];
				strcpy(chars, other.chars);
			}
			return *this; //return dereference of this
		}

		// b = "byebye" could cause a memory leak, so i ovearload the assigment to char* to do the cleanup too
		CharString& operator =(const char* other)
		{
			delete[] this->chars; //delete old value
			int length = strlen(other) + 1; //can actually access private members in copy constructor!
			chars = new char[length];
			strcpy(chars, other);
			return *this; //return dereference of this
		}
	};


	void testCharstring()
	{
		cout << "----- custom string class based on char*, strlen and strcopy -----" << endl;

		cout << "CharString a, b(hello):" << endl;
		CharString a, b("hello"); //this passes a inplicitly created char*, like above
		cout << "a: " << a << ", b: " << b << endl << endl;

		cout << "a = b:" << endl;
		a = b; //if i dont overlad = opeator those two point to the same, which causes issues with destructor!
		cout << "a: " << a << ", b: " << b << endl << endl;

		cout << "CharString c(a):" << endl;
		CharString c(a);
		cout << "c: " << c << endl << endl;

		//check if i truly copied the chars and do not point to the same stuff
		cout << "b = byebye:" << endl;
		b = "byebye"; //this might cause a memory leak since i dont destroy the old char* object, i just set a new one
		cout << "b: " << b << endl << endl;

		cout << "printf(a): ";
		printf(a);
		cout << endl << endl;

		cout << "Result:" << endl;
		cout << "a: " << a << ", b: " << b << ", c: " << c << endl << endl;

		cout << "-------------------------" << endl;

		//this can only be done on initialization
		char word[] = "abc";
		cout << "strlen ignores \\0, size of 'abc' = " << strlen(word) << endl;
	}


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