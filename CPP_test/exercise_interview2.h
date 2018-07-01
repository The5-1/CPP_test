#pragma once

#include "String.h"
#include "include_IO.h"

using namespace std;

namespace exercise_interview2
{

	/* Other questions:
	Q: Determine side of a point to a plane defined by a point and normal:
	A: Dot-Product of point-to-point and normal.

	Q: Invert toration matrix:
	A: Transpose = Iverse (since rotations are orthogonal-matrices).

	Q: Phong:
	A: Ambient = constant, diffuse = dot(N,L), specular = dot(N,normalize(L+V))^e

	Q: Phong VS Blinn:
	A: Blinn uses halfway vector (which is not just faster than reflection but physically more accurate)

	Q: Inster point into Octree:
	A: Bounding box min/max, half dimensions of that, compare bigger or smaller than those hales, this gives the octree cell

	Q: KD-tree:
	A: Boxes are halfed so that halfe of the points os distributed per cell. Axis of the "cut" is chosen e.g. at random

	Q: Interpolate rotations:
	A: Use Spherical interpolation based on quaternions (quaternion is mat4 instead of mat3)

	Other Stuff:
	SVM: Linear divider for data set with 2 types
	Kernel Trick: bring data in higher dimension to enable linear division
	ICP: Procrustes, transform CoG, scale BB, rotation via Singular-Value-Decomposition. 

	*/

	
	/*
	https://stackoverflow.com/questions/4955198/what-does-dereferencing-a-pointer-mean
	"The definition of the subscript operator [] is that E1[E2] is identical to (*((E1)+(E2)))."
	*/
	void copy_C_style(char*** to, char** from) {

		int fromSize = 0;

		while (from[fromSize] != nullptr) {
			fromSize++;
		}
		fromSize++; //Because we have a nullptr to see where the array ends

		to[0] = (char**)malloc(sizeof(char*) * fromSize);

		for (int i = 0; i < fromSize - 1; i++) {
			to[0][i] = (char *)malloc(sizeof(std::strlen(from[i]) + 1));
			std::strcpy(to[0][i], from[i]);
		}

		*to[fromSize - 1] = nullptr;
	}

	void copy_C_styleAlternative(char*** to, char** from) {

		int fromSize = 0;

		while (from[fromSize] != nullptr) {
			fromSize++;
		}
		fromSize++; //Because we have a nullptr to see where the array ends

		(*to) = (char**)malloc(sizeof(char*) * fromSize);

		for (int i = 0; i < fromSize - 1; i++) {
			(*to)[i] = (char *)malloc(sizeof(std::strlen(from[i]) + 1));
			std::strcpy((*to)[i], from[i]);
		}

		(*to)[fromSize - 1] = nullptr;
	}


	void test_CustomString() {

		std::cout << "------ ExerciseInterview2: Custom String ------" << std::endl;

		// C++ String Class Test (Rule of Three)
		String test("Hello");
		String copytest("World");

		std::cout << "Initiate: " << std::endl;
		std::cout << "test: " << test.string << " with size " << test.getSize() << std::endl;
		//Can NOT print copytest, it has not been initiated yet
		//std::cout << "copyTest: " << copytest.string << " with size " << copytest.getSize() << std::endl;

		std::cout << "Copy: " << std::endl;
		copytest = test;
		std::cout << "test: " << test.string << " with size " << test.getSize() << std::endl;
		std::cout << "copyTest: " << copytest.string << " with size " << copytest.getSize() << std::endl;

		std::cout << "Change original: " << std::endl;
		test.string[0] = 'F';
		std::cout << "test: " << test.string << " with size " << test.getSize() << std::endl;
		std::cout << "copyTest: " << copytest.string << " with size " << copytest.getSize() << std::endl;

		std::cout << "Ostream test: " << test << std::endl;

		std::cout << "------------" << std::endl;
	}
	
	void test_C_Pointer() {
		// C Pointer 

		std::cout << "------ ExerciseInterview2: C Pointers ------" << std::endl;

		//Variables
		char** copyFrom;
		char*** copyTo;

		//Size
		int size = 5; //without nullptr end

					  ///////////////////
					  //Initialize copyFrom**
					  ///////////////////
		copyFrom = (char**)malloc(sizeof(char*) * (size + 1));

		for (int i = 0; i < size; i++) {
			copyFrom[i] = (char*)malloc(sizeof(char) * 3);

			copyFrom[i][0] = 'a' + std::rand() % 26;
			copyFrom[i][1] = 'a' + std::rand() % 26;
			copyFrom[i][2] = '\0';
		}

		copyFrom[size] = nullptr;


		std::cout << "copyFrom: ";
		for (int i = 0; i < size; i++) {
			std::cout << copyFrom[i] << ", ";
		}
		std::cout << std::endl;



		///////////////////
		//Initialize copyTo***
		///////////////////
		copyTo = (char***)malloc(sizeof(char**));
		//copy_C_style(copyTo, copyFrom);
		copy_C_styleAlternative(copyTo, copyFrom);

		///////////////////
		//Print copyTo***
		///////////////////
		std::cout << "copyTo: ";
		for (int i = 0; i < size; i++) {
			std::cout << copyTo[0][i] << ", ";
			std::cout << (*copyTo + 0)[i] << ", ";
			std::cout << (*copyTo)[i] << ", ";
		}
		std::cout << std::endl;

	}

}