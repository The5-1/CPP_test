#pragma once


//circular dependency
//https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes
//the compiler allocates space for object A
//object A holds object B
//object B holds object A ---> ERROR

//1.) A may not hold an object of B if B holds one of A
//--> A must hold a pointer to B, not an object

//forward Declaration
//https://stackoverflow.com/questions/4757565/what-are-forward-declarations-in-c/4757718#4757718

//2.) A.h must not include B.h if you declare a class B in it
//--> manually declare class B; in A.h, A.cpp then can #include "B.h"