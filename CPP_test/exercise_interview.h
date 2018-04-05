#pragma once

#include <string>
#include "include_IO.h"

using namespace std;

namespace exercise_interview
{
	//This whole string class example is the go-to example for the Rule of Three
	// http://en.cppreference.com/w/cpp/language/rule_of_three
	// https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)#Example_in_C++ C++ code for custom string class with rule of five


	//Custom String Class Exercise
	//http://www.cplusplus.com/doc/tutorial/ntcs/
	//https://stackoverflow.com/questions/16511706/simple-string-implementation-in-c
	//https://stackoverflow.com/questions/18693866/how-to-interpret-operator-const-char-in-operator-overloading

	// Rule of Three
	// https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)
	// https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three
	// Destructor, Copy Constructor, Copy Assingment Operatro (=)

	// Copy and Swap idiom (Rule of Three and a half)
	// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom !!!
	// std::swap since c++98
	// Make the assignment operator re-use copy constructor and destructor!
	// * create a copy via copy constructor (use inplicit copy by pass-by-value)
	// * create a "swap()" function to change out your data with the copy
	// * destruct the copy


	// Move Semantics (C++11, MoveConstructor)  (Rule of 5 in C++11)
	//string example: https://stackoverflow.com/questions/3106110/what-are-move-semantics

	//Friend VS Static Method
	//https://stackoverflow.com/questions/2315166/where-would-you-use-a-friend-function-vs-a-static-member-function



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

		//destructor
		~CharString()
		{
			delete[] chars;
		}

		//constructor that gets passed a string literal
		CharString(char* text)
		{
			int length = strlen(text)+1;  // +1 for the "\0" C-String terminator ("null-character")
			chars = new char[length];
			strcpy(chars, text);
		}

		//Copy Constructor
		CharString(const CharString& other)
		{
			int length = strlen(other.chars)+1; //can actually access private members in copy constructor!
			chars = new char[length];
			strcpy(chars, other.chars); //strcpy is like memcpy but it ends at \0 automatically instead of expecting a length parameter
		}

		//implicit conversion operator (explicit keyword for explicit)
		//this can cause issues eg with a = b, both are treated as char* pointer and a points to the same obejct as b afterwards
		operator const char *()
		{
			return (this->chars);
		}

		//Rule of Three and a Half, (Copy and Swap Idiom)
		friend void swap(CharString& first, CharString& second) //friend defines a function outside this class that got access to private members still (like static, but not scoped to the class at all)
		{
			//swap the members
			std::swap(first.chars, second.chars); //using
		}

		// Copy Assigment Operator
		// the existence of the = operator prevents a = b becoming char* = char* due to implicit conversion
#if 0
		//Copy Assigment Operator (brute force implementation)
		CharString& operator =(const CharString& other)
		{


			if (this != &other) //compare with adress of other
			{
				delete[] this->chars; //delete old value //!at this moment we geta problem if an exception occurs in the following code
				int length = strlen(other.chars) + 1; //can actually access private members in copy constructor!
				chars = new char[length]; //if an exception occurs here, we have already deleted our current data :(
				strcpy(chars, other.chars);
			}
			return *this; //return dereference of this
		}
#elif 0
		//Copy Assignment via "Copy and Swap" (done naively)
		CharString& operator = (const CharString& other) //pass by reference
		{
			CharString tmp(other); //utilize copy constructor to make a copy
			swap(*this, tmp); //swap with the copy
			return *this;
			//local copy is deleted at end of scope
		}
#else

		//Copy Assignment via "Copy and Swap" (optimized with automatic copy)
		CharString& operator = (CharString other) //pass by value directly --> compiler creates copy! 
		{
			swap(*this, other); //friend void swap is not a member function, but technically a global one with private access
			return *this;
		}

#endif


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


	class MyString_RuleOfFive
	{
	public:
		//source: https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)#Example_in_C++

		/** Default constructor */
		MyString_RuleOfFive() :
			data(new char[14])
		{
			std::strcpy(data, "Hello, World!");
		}

		/** Copy constructor */
		MyString_RuleOfFive(const MyString_RuleOfFive& other) :
			data(new char[std::strlen(other.data) + 1])
		{
			std::strcpy(data, other.data);
		}

		/** Move constructor */
		MyString_RuleOfFive(MyString_RuleOfFive&& other) noexcept : /* noexcept needed to enable optimizations in containers */
		data(other.data)
		{
			other.data = nullptr;
		}

		/** Destructor */
		~MyString_RuleOfFive() noexcept /* explicitly specified destructors should be annotated noexcept as best-practice */
		{
			delete[] data;
		}

		/** Copy assignment operator */
		MyString_RuleOfFive& operator= (const MyString_RuleOfFive& other)
		{
			MyString_RuleOfFive tmp(other);         // re-use copy-constructor
			*this = std::move(tmp); // re-use move-assignment
			return *this;
		}

		/** Move assignment operator */
		MyString_RuleOfFive& operator= (MyString_RuleOfFive&& other) noexcept
		{
			if (this == &other)
			{
				// take precautions against `foo = std::move(foo)`
				return *this;
			}
			delete[] data;
			data = other.data;
			other.data = nullptr;
			return *this;
		}

	private:
		friend std::ostream& operator<< (std::ostream& os, const MyString_RuleOfFive& foo)
		{
			os << foo.data;
			return os;
		}

		char* data;
	};



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