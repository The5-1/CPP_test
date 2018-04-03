#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "include_IO.h"

using namespace std;

namespace exercise_Stack_Heap
{
	/* See LGDV C++ Tutorium Slides! */


	void allocateOnStack()
	{
		/* Stack memory
		** * Automatic deletion when scope ends
		** * can handle arrays
		** * can not be of dynamic size!
		*/

		char buffer[1024];
		buffer[5] = 'a'; // a single character needs single quotes
		cout << "buffer1[0] = " << buffer[0] << endl;
		cout << "buffer1[5] = " << buffer[5] << endl;
		//delete[] buffer; //this would throw an exception! No deletion required on stack

		char arr[3] = { 'a','b','c' };
		char* a = arr;
		cout << "Acces Array on stack via pointer! " << a[0] << a[1] << a[2] << endl;

		{
			char buffer2[1024];		
		} //automatic, deleted here

#if 0
		int bufferSize = rand();
		char buffer3[bufferSize]; //Stack cant be dynamically allocated!
		char* buffer3 = new char[bufferSize]; //Heap can!
		delete[] buffer3;
#endif

	}


	void allocateOnHeap()
	{
		char *buffer = new char[1024];

		//delete pBuffer; //may only delete first pointer
		delete[] buffer; //correct!

	}

	void arrays()
	{

		//Multidimensional Arrrays: (make them 1D)
		// https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
		cout << "--- Arrays ---" << endl;

		cout << "Multidimensional Arrays on stack are easy!" << endl;
		int buffer2D_stack[2][2] = { { 1,2 },{ 3,4 } };

		cout << "Multidimensional Arrays on heap are hard." << endl;
#if 0
		char* buffer2D_heap_doesNotWork = new char[4][4]; //this does not compile, sadly
#endif

		cout << "Making a 2D heap array in c++ is a bit more complicated..." << endl;
		int sizeX = 4;
		int sizeY = 4;

		char** buffer2D = new char*[sizeY]; //first, create a array of pointers
		for (int i = 0; i < sizeY; ++i) {
			buffer2D[i] = new char[sizeX]; //then create arrays for those pointers
		}

		cout << "... and you need to delete it in a complicated way too..." << endl;
		for (int i = 0; i< sizeY; i++) {
			delete[] buffer2D[i];
		}

		cout << "... thats why it is usually handled 1D, it's in one continous block of memory too then!" << endl;
		char* buffer2D1D = new char[sizeX*sizeY];
		buffer2D1D[2 * sizeY + 1] = 'a'; // = [2][1]

		delete[] buffer2D1D;
	}


	void pointers()
	{
		int a = 4;
		cout << "value a = " << a << endl;

		int* b = &a; 
		cout << "adress b = " << b << endl;

		int c = *b; 
		cout << "value behind adress *b = " << c << endl;

		*b = 5;
		cout << "*b is NOT a copy = " << *b << endl;

		int h = (int)&a; //interpret the adress as int
		cout << "adress cast to int = " << h << endl;
	}

	void references()
	{
		/*Refrences are Syntactic Suggar for pointers with extra simplification
		** must be initialized, can not be null
		** can not be changed to point to something else (ref = b; just copies b´s value!)
		** implicitly dereferenced when used "cout << ref;" outputs the value
		*/
		int a = 5, b = 3;

		int* ptr = nullptr; //pointer to null = uninitialized
		ptr = &a; //pointer set

		int &ref = a; //Reference can not be NULL --> must be initialized
		cout << "Reference c is like a pointer to a: c = " << ref << endl; // ref is implicitly dereferenced
		ref = 2;
		cout << "changed value of a via reference: a = " << a << endl;
		*ptr = 6;
		cout << "changed value of a via derefenced pointer: a = " << a << endl;

		ref = b; //!!! does NOT point to b now, copy b into a!
		ref = 2;
		cout << "Value of b copied to a: ref = " << ref << ", b = " << b << endl;
	}

	void pointerArithmetic()
	{
		cout << "--- Pointer Arithmetic ---" << endl;

		char arr[3] = { 'a','b','c' };
		char* a = arr;

		//dereference incremented pointers
		cout << "incremet pointer: "<< *a << ","<< *(a++) << "," << *(a + 1) << endl;

	}


	void test0()
	{

		allocateOnStack();
		allocateOnHeap();

		pointers();
		references();

		pointerArithmetic();
		arrays();
	}
}