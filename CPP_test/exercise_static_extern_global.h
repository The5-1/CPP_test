#pragma once

/******************************************************************************
**** LNK2001 Unresolved External Symbol [member variable of static class]  ****
******************************************************************************/
/* >>>>> The definition for a static data member shall appear in a namespace scope enclosing the member’s class definition. <<<<< */

//in IComponentProcessor.h we __declare__
class IComponentProcessor
{
public:
	static std::vector<IComponent*> mComponentPointers;
}

//then in the IComponentProcessor.cpp you MUST __define__ (and should __initialize__) it!
std::vector<IComponent*> IComponentProcessor::mComponentPointers = std::vector<IComponent*>();


//Global VS Static VS Sigleton, why is none of it really good?
//https://stackoverflow.com/questions/365261/ok-global-variable-is-condemned-singleton-is-despised-whats-the-alternative
//--> there is nothing wrong with globals if it fits the purpose
//--> static classes are just like globals but more "politically correct"
//--> singleton just makes it more complex, pretending to be OOP conform
//The truly OOP conform way is:
//-- if something is global, like a Logging function, make it global!
//-- Instead of your class accessing some static (global) variable somewhere, pass the data to its constructor.
//-- It makes the dependencies for the class explicit. There are no magic dependencies on classes other than what's passed directly to the object.
//-- Thread safety gets easier to manage because you no longer have all your objects communicating with the same global instance. Instead, they can be passed separate instances of the class.

//static members must be defined and optionally initialized in the cpp!
//https://stackoverflow.com/questions/16049306/error-lnk2001-unresolved-external-symbol-private-static-class

//extern members are declared in headers
//but must be defined in one cpp file
//https://stackoverflow.com/questions/10422034/when-to-use-extern-in-c

//Static object initialization is undefined
//https://isocpp.org/wiki/faq/ctors#static-init-order

//use a namespace-global object instead of singleton or statics? https://www.ics.com/designpatterns/book/namespace-example.html