#pragma once

#include <iostream>


class String
{
public:
	char* string;

public:
	String();
	String(const char* arg);
	String(const String &arg);
	~String();

	unsigned int getSize() const;

	String& operator=(const String& other);
	friend std::ostream& operator<<(std::ostream& os, const String& st);
};

