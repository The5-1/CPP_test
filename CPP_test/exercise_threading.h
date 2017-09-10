#pragma once
#include <iostream>
#include <thread>

/***********************************************************
Avoid Threads if you do not need them.

Basics:
- create and start with: std::thread(function, parameters)
- end thread with mythread.join();
http://thispointer.com/c-11-multithreading-part-1-three-different-ways-to-create-threads/
------------------------------------------------------------

Passing by referece with std::ref()
- std::thread(function, std::ref(param))
- this handles what happens when the reference is gone while the thread acesses it
https://stackoverflow.com/questions/34078208/passing-object-by-reference-to-stdthread-in-c11/34078246
------------------------------------------------------------

https://stackoverflow.com/questions/266168/simple-example-of-threading-in-c

https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/

https://www.quantstart.com/articles/Function-Objects-Functors-in-C-Part-1

http://thispointer.com/c-11-multithreading-part-1-three-different-ways-to-create-threads/


***********************************************************/


using namespace std;


namespace exercise_threading
{

	void call_function(int &x, string threadname)
	{
		for (int i = 0; i < 100; i++)
		{
			if(i%10 == 0) cout << "A. function thread: " << to_string(i) << endl;
			x++;
		}
		printf("Threat via function completed: %s \n", threadname.c_str());
	}

	struct call_functor
	{
		static int totalCount; //statics are 0 by default, you cant change the default in the class

		int count = 0;

		void operator()(int &x, string threadname) //enable this to be a Functor (Function Object) by implementing the () operator
		{
			for (int i = 0; i < 100; i++)
			{
				if (i % 10 == 0) cout << "B. functor thread: " << count << endl;
				count++;
				x++;
			}
			printf("Threat via functor completed: %s \n", threadname.c_str());
		}

	};

	void test_threads01()
	{
		int x = 0;

		cout << "INFO: Hardware supports " << std::thread::hardware_concurrency() << " threads." << endl;


		//-----------------------------------------------------------------
		
		// Constructs the new thread and runs it. Does not block execution.
		std::thread t_function1(call_function, std::ref(x), "t_function1"); //thread with function pointer
		std::thread t_functor1(call_functor(), std::ref(x), "t_functor1"); //thread with functor //if the functor takes no parameters it needs double braces
		std::thread t_function2(call_function, std::ref(x), "t_function2"); //references need to be passed with std::ref() so the thread can handle if the ref does not exist anymore
		std::thread t_functor2(call_functor(), std::ref(x), "t_functor2");

		std::thread t_lambda1(
			[&x]() { //no std::ref() needed here?
				for (int i = 0; i < 100; i++)
				{
					if (i % 10 == 0) cout << "C. lambda thread: " << i << endl;
					x++;
				}
				printf("Threat via lambda completed: t_lambda1\n");
			}
		);

		//-----------------------------------------------------------------
		
		cout << "ThreatID - main: " << std::this_thread::get_id() << endl;
		cout << "ThreatID - t_function1: " << t_function1.get_id() << endl;
		cout << "ThreatID - t_function2: " << t_function2.get_id() << endl;
		cout << "ThreatID - t_functor1: " << t_functor1.get_id() << endl;
		cout << "ThreatID - t_functor2: " << t_functor2.get_id() << endl;
		cout << "ThreatID - t_lambda1: " << t_lambda1.get_id() << endl;

		//-----------------------------------------------------------------

		for (int i = 0; i < 100; i++)
		{
			//cout << "main thread" << endl;
			x++;
		}
		cout << "main thread loop done" << endl;

		//-----------------------------------------------------------------

		// Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
		t_function1.join();
		t_function2.join();
		t_functor1.join();
		t_functor2.join();
		t_lambda1.join();

		cout << "x = " << x << endl;
	}

	void test()
	{
		test_threads01();
	}
}