#pragma once

#include <vector>
#include <iostream>

#include "Component.h"

//http://gameprogrammingpatterns.com/component.html


namespace ArchitectureTest
{

	class Entity
	{
	public:

		void send(int message)
		{
			for (auto &component: Components)
			{
				component.receive(message);
			}
		}

	private:
		std::vector<Component> Components;
	};

}