#pragma once
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
		foo(new D1); //ERROR: conversion to inacessible base class
		foo(new D2); //this works
	}


//Virtual functions & unresolved external symbol ERROR
//====================================================
//https://www.gamedev.net/forums/topic/518288-cwierd-problem---abstract-function-is-unresolved-external-symbol/?do=findComment&comment=4367433
//Calling virtual functions in the constructor / destructor is usually a bad idea. Because you're calling the unload() function from your destructor,
//the vtable would have been destroyed, meaning the only version function you can call would be that in SIResource - which is pure virtual and therefore undefined.
//https://stackoverflow.com/questions/9529083/calling-pure-virtual-function


}