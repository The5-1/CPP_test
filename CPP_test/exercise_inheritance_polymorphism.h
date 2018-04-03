#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "include_IO.h"

using namespace std;

namespace exercise_inheritance_polymorphism
{


	//https://stackoverflow.com/questions/1563765/use-of-public-in-a-derived-class-declaration
	//nothing = D "makes use of" Base (inherited members turn private)
	//public = D "is a" Base --> enables casting


	class B { };

	class D1 : B { }; //all members of B are turned to private, casting is not possible -> "D1 makes use of B"

	class D2 : public B { }; //all members of B remain -> "D2 is a B"

	void foo(B* baseArgument) {};


	void test()
	{
#if 0
		foo(new D1); //ERROR: conversion to inacessible base class
#endif
		foo(new D2); //this works
	}


//         Virtual
//===========================
// if a object is polymorphic, it calls the base classes method when they are not virtual
// this is dangerous for destructors!!!

	class Counter
	{
	public:
		int value = 0;
		void incr() { value++; } //non-virtual
	};

	class BinCounter : public Counter
	{
	public:
		void incr() { value += 2; } //this is not called when stored in a Counter object, the base class is called (wrong "binding")
	};

	class CounterV
	{
	public:
		int value = 0;
		virtual void incr() { value++; } //virtual tells to use the inherited classes method!
	};

	class BinCounterV : public CounterV
	{
	public:
		void incr() { value += 2; }
	};

	class CounterPV
	{
	public:
		int value = 0;
		virtual void incr() = 0; //Pure virtual, this MUST be overridden by a child!
	};

	class BinCounterPV : public CounterPV
	{
	public:
		void incr() { value += 2; }
	};

	void testVirtual()
	{
		cout << "---------- Virtual -----------" << endl;
		BinCounterV *bc = new BinCounterV(); // We again store it in a Counter object!
		bc->incr(); // This actually calls BinCounter now!
		cout << "If the object is not polymorphic, the proper +2 is called: bc.value = " << bc->value << endl;

		Counter *c = new BinCounter(); // We store it in a Counter object!
		c->incr(); //... and it calls the Counter classes method
		cout << "If it is polymorphic and not virtual, the base class method was called: c.value = " << c->value << endl;
		cout << "This is dangerous for destructors! Imagine the base classes destructor is called rather than the childs!" << endl;

		CounterV *cv = new BinCounterV(); // We again store it in a Counter object!
		cv->incr(); // but this actually calls the BinCounter method now!
		cout << "If it is polymorphic and it is virtual, the child is called correctly: cv.value = " << cv->value << endl;

	}




//Virtual functions & unresolved external symbol ERROR
//====================================================
//https://www.gamedev.net/forums/topic/518288-cwierd-problem---abstract-function-is-unresolved-external-symbol/?do=findComment&comment=4367433
//Calling virtual functions in the constructor / destructor is usually a bad idea. Because you're calling the unload() function from your destructor,
//the vtable would have been destroyed, meaning the only version function you can call would be that in SIResource - which is pure virtual and therefore undefined.
//https://stackoverflow.com/questions/9529083/calling-pure-virtual-function



}