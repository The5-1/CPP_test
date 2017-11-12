#pragma once

#include <vector>
#include <iostream>

//http://gameprogrammingpatterns.com/component.html

namespace ArchitectureTest
{
	class Component
	{
	public:
		virtual ~Component() {}
		virtual void receive(int message) = 0;
	};

	class RenderingComponent : Component
	{
	public:
		void receive(int message)
		{
			std::cout << "RenderingComponent recieved message: " << message << std::endl;
		}
	};

}