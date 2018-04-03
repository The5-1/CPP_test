#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "include_IO.h"

using namespace std;

/**
==============================================
=  Templates = compile-time polymorphism!    =
=  Inheritance = runtime polymorphism        =
==============================================
- two classes Processor<ComponentA> and Processor<ComponentB> will be two entirely independent classes after compilation!
- a function wont be able to return/take a Processor<IComponent> and return either, all 3 classes are completely different

template<class T> = template<typename T> //Typename is modern


**/

namespace exercise_templates
{

	//templated class
	template<typename T> class Stack //"typename" or "class", both are the same but typename is modern
	{
	private:
		int index;
		T *array;
	public:
		Stack(int n) : index(0) {
			array = new T[n];
		}

		~Stack() 
		{
			delete[] array;
		}

		void push(T elem) 
		{ 
			array[index++] = elem; 
		}

		T pop() 
		{ 
			return array[--index]; 
		}
	};

	//templated function
	template<typename T> void sort(T *feld, int length) 
	{
		//do stuff with T
		return;
	}

	//specialized template (works for classes too)
	template<> void sort(float *feld, int length)
	{
		//do optimized stuff when T is a float
		return;
	}


	void test0() {

		typedef Stack<int> intStack;

		Stack<double> s(10);
		s.push(20.0);
		double a = s.pop();
		cout << "a = " << a << endl;
	}

}
