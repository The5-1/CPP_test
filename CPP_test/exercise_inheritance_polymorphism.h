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
		foo(new D1); //conversion to inacessible base class
		foo(new D2); //this works
	}

}