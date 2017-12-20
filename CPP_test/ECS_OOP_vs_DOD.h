#pragma once
/******************************************

//Good summary with sample code
https://github.com/CppCon/CppCon2015/blob/master/Tutorials/Implementation%20of%20a%20component-based%20entity%20system%20in%20modern%20C%2B%2B/Implementation%20of%20a%20component-based%20entity%20system%20in%20modern%20C%2B%2B%20-%20Vittorio%20Romeo%20-%20CppCon%202015.pdf
https://www.youtube.com/watch?v=NTWSeQtHZ9M
https://github.com/CppCon/CppCon2015/tree/master/Tutorials/Implementation%20of%20a%20component-based%20entity%20system%20in%20modern%20C%2B%2B/Source%20Code


//About performance and Cache
http://t-machine.org/index.php/2014/03/08/data-structures-for-entity-systems-contiguous-memory/
------------------------------------------------------------------------------------------------------------------------------------------
--  !!! a Approach using maps/dictionaries, like in the OOP composition is slow-er but not "slow" !!!									--
------------------------------------------------------------------------------------------------------------------------------------------
--  std::vector is CONTINUOUS! You just need to acess it with .at(i) rather than directly pointing to it.                               --
------------------------------------------------------------------------------------------------------------------------------------------
--  "To recap: even in 2011, Android phones could run realtime 30 FPS games using Maps. It’s slow – but fast enough for simple games"	--
------------------------------------------------------------------------------------------------------------------------------------------
--  Entity Processors will process continous data in the order it exists in RAM															--
--  So the game objects must be able to ignore the order in which they are processed													--
--  The stuff that happens every frame needs to be as continuous as possible, like Transformations										--
--  Cross references, like packing a item entity into a inventory, happen more rarely and are not that crucial							--
--  It is ok to just optimize cache for the Processor/Components that takes up the most CPU-time!										--
------------------------------------------------------------------------------------------------------------------------------------------
--  Components should be almost Atomic !																								--
--  A Bomberman game has about 12 Component types																						--
--  Dungeon Siege 2003 used about 150 Component types																					--
--  150 comonents, 10k combinations, 100k instances at runtime																			--
--  RAM itself is not the big isssue: Assuming 150 big component types with thousands of instances:										--
--  1 component type * 20k component instances * 50 variables * 8byte each = only 8MB per component * 150 compnent types = only 500MB	--
------------------------------------------------------------------------------------------------------------------------------------------

Ownership and smart_ptrs
------------------------
https://gamedev.stackexchange.com/questions/49525/attribute-ownership-in-entity-component-systems


http://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/




//Dungeon Siege 2003
http://gamedevs.org/uploads/data-driven-game-object-system.pdf

******************************************/

#include <memory>
#include <vector>


//===================
//= OOP composition =
//===================
// Components store data and handle logic
//-------------------
//++ flexible
//-- cache unfriendly (still fast enough for normal games!)
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