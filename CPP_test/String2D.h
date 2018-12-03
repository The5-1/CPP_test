#pragma once

#include <iostream>
#include <thread>
#include <chrono>

namespace String2Dtest {

	class MyString2D {
		
	public:
		char** m_stringList;

	public:
		MyString2D(int count = 1) {
			m_stringList = new char*[count+1];
			for (int i = 0; i < count; i++) {
				m_stringList[i] = new char[1];
				m_stringList[i][0] = '\0';
			}
			m_stringList[count] = nullptr;
		}

		MyString2D(char* text) {
			int length = strlen(text) + 1;  // +1 for the "\0" C-String terminator ("null-character")
			m_stringList = new char*[2];
			m_stringList[0] = new char[length];
			strcpy(m_stringList[0], text);
			m_stringList[1] = nullptr;
		}

		~MyString2D() {
			int i = 0;
			while (m_stringList[i] != nullptr) {
				delete[] m_stringList[i];
				i++;
			}
			delete[] m_stringList;
			m_stringList = nullptr;
		}

		MyString2D(const MyString2D& other) {

			if (&other == this) return;
			int s = 0;
			while (other.m_stringList[s] != nullptr) s++;
			
			m_stringList = new char*[s + 1];
			m_stringList[s] = nullptr;

			for (int i = 0; i < s; i++) {
				int length = strlen(other.m_stringList[i]) + 1;
				m_stringList[i] = new char[length];
				strcpy(m_stringList[i], other.m_stringList[i]);
			}

		
		}
	
	
		MyString2D& operator=(const MyString2D& other) {
			if (&other == this) return *this;
			int i = 0;
			while (m_stringList[i] != nullptr) {
				delete[] m_stringList[i];
				i++;
			}
			delete[] m_stringList;

			int s = 0;
			while (other.m_stringList[s] != nullptr) s++;

			m_stringList = new char*[s + 1];
			m_stringList[s] = nullptr;

			for (int i = 0; i < s; i++) {
				int length = strlen(other.m_stringList[i]) + 1;
				m_stringList[i] = new char[length];
				strcpy(m_stringList[i], other.m_stringList[i]);
			}

			return *this;
		}

	};


	void test01() {

		printf("creating a ton of mystring and deleting them\n");
		for (uint32_t i = 0; i < 10000; i++) {
			MyString2D* ms = new MyString2D(100);	
			this_thread::sleep_for(chrono::microseconds(1));
			delete ms;
		}

		printf("done!\n");


		printf("copy constructor\n");
		MyString2D* ms1 = new MyString2D("Hello from ms1");

		MyString2D* ms2 = new MyString2D(*ms1);

		MyString2D* ms3 = new MyString2D("Old");

		*ms3 = *ms2;

		printf("done!\n");

	}

}
