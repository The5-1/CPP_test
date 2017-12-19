#pragma once
/******************************************

//Great summary!!!
//compares different approaches with sample code
https://github.com/CppCon/CppCon2015/blob/master/Tutorials/Implementation%20of%20a%20component-based%20entity%20system%20in%20modern%20C%2B%2B/Implementation%20of%20a%20component-based%20entity%20system%20in%20modern%20C%2B%2B%20-%20Vittorio%20Romeo%20-%20CppCon%202015.pdf

******************************************/

#include <memory>
#include <vector>


//===================
//= OOP composition =
//===================
// Components store data and handle logic
//-------------------
//++ flexible
//-- cache unfriendly
//-- runtime overhead
namespace ECS_OOP_composition
{
	struct Component
	{
		virtual ~Component() {}

		virtual void update() {}
		virtual void draw() {}
	};


	struct Entity
	{
		std::vector<std::unique_ptr<Component>> components;

		void update() {
			for (auto& c : components) c->update();
		}

		void draw() {
			for (auto& c : components) c->draw();
		}
	};

	struct Bone
	{};

	struct BonesComonent : Component
	{
		std::vector<Bone> bones;

		void update() override
		{
			//do stuff
		}
	};

	auto makeSkeletion()
	{
		Entity e;
		e.components.emplace_back(std::make_unique<BonesComonent>()); //emplace_back avoids creating a temporary object
	}
	
}

//===================
//= DOD composition =
//===================
// Components only store data
// Systems handle logic
//-------------------
//++ flexible
//~~ can be more cache friendly if done right
//++ minimal runtime overhead
namespace ECS_DOD_composition
{

}