#pragma once

//=======================================
//=   Forward Declarations & Typedefs   =
//=======================================
//https://stackoverflow.com/questions/2356548/header-file-best-practices-for-typedefs
//https://stackoverflow.com/questions/10469531/forward-declaration-when-best-to-include-headers
//----------------------------------------------------------
// -- you can make one header with all class definitions! --
//----------------------------------------------------------
// -- you can also add all typedefs in there!             --
//----------------------------------------------------------
// -- use forward declarations, they reduce compile time  --
//----------------------------------------------------------




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