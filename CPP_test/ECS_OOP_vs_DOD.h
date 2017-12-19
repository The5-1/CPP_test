#pragma once
/******************************************

//Great summary!!!
//compares different approaches with sample code
https://github.com/CppCon/CppCon2015/blob/master/Tutorials/Implementation%20of%20a%20component-based%20entity%20system%20in%20modern%20C%2B%2B/Implementation%20of%20a%20component-based%20entity%20system%20in%20modern%20C%2B%2B%20-%20Vittorio%20Romeo%20-%20CppCon%202015.pdf

Video with live coding!!!
https://www.youtube.com/watch?v=NTWSeQtHZ9M

Code:
https://github.com/CppCon/CppCon2015/tree/master/Tutorials/Implementation%20of%20a%20component-based%20entity%20system%20in%20modern%20C%2B%2B/Source%20Code

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
//-- runtime overhead due to runtime Polymorphism
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
//= DOD composition = (Data-Oriented-Design = cache friendly)
//===================
// Components only store data
// Systems handle logic
//-------------------
//++ flexible
//~~ can be more cache friendly if done right
//++ minimal runtime overhead due to compile-time Polymorphism
namespace ECS_DOD_composition
{
	using Entity = std::size_t;
	constexpr std::size_t maxEntities{ 1000 };

	struct BonesComponent {/*...*/ };
	struct AIComponent {/*...*/ };
	struct SpriteComponent {/*...*/ };
	
	struct Manager
	{
		std::array<BonesComponent, maxEntities> bonesComponents;
		std::array<AIComponent, maxEntities> aiComponents;
		std::array<SpriteComponent, maxEntities> spriteComponents;

	};
	
}