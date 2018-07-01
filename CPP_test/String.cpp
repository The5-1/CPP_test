#include "String.h"



String::String()
{
	this->string = new char[1];
	string[0] = '\0';
}

String::String(const char * arg)
{
	int size = 0;
	while (arg[size] != '\0') {
		size++;
	}

	this->string = new char[size + 1];

	for (int i = 0; i < size; i++) {
		string[i] = arg[i];
	}

	string[size] = '\0';
}

String::String(const String & arg)
{
	unsigned int size = arg.getSize();
	this->string = new char[size + 1];

	for (int i = 0; i < size + 1; i++) {
		string[i] = arg.string[i];
	}
}


String::~String()
{
	delete[] string;
}

unsigned int String::getSize() const
{
	//This does not work because the datatype of this->string is a pointer, gives the size of a pointer in bytes
	//int sizeWront = sizeof(this->string) / sizeof(char);

	int i = 0;
	while (this->string[i] != '\0') {
		i++;
	}

	return i;
}


String& String::operator=(const String& other)
{
	int otherSize = other.getSize()+1;
	char* tmp_cstring = new char[otherSize];

	//This prints garbage till it hits the first '\0' in memory
	//std::cout << "tmp = " << tmp_cstring << "(" << otherSize << ")"<< std::endl;

	for (int i = 0; i < otherSize; i++) {
		tmp_cstring[i] = other.string[i];
	}
	tmp_cstring[otherSize] = '\0';

	delete[] this->string;
	this->string = tmp_cstring;
	return *this;
}

std::ostream & operator<<(std::ostream & os, const String & st)
{
	os << st.string;
	return os;
}
