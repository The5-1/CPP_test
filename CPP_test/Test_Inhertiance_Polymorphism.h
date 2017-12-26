#pragma once

#include <vector>
#include <iostream>
#include <memory>

namespace Test_Inheritance_Polymorphism
{
	enum AnimalType { none, ElephantType, GiraffeType };

	class Animal;

	template<typename T> //Class derived from Animal goes here
	class Zookeeper
	{
	public:

		std::vector<T*> animals;

		void assignAnimalToMe(T* animal)
		{
			animals.push_back(animal);
		}

		void removeAnimalFromMe(T* animal)
		{
			animals.erase(std::remove(animals.begin(), animals.end(), animal), animals.end());
		}

	};


	//**** Goal: get all the funcitons shared by all animal-types into this abstract base class ****//
	class Animal
	{
	public:
		Animal(std::string name, Zookeeper<Animal>* keeper) : name(name) //!!! it seems here is a issue Zookeeper<Animal>*, since in the derived classes i want e.g. Zookeeper<Elephant>*
		{
			assignToZookeper(keeper);
		};

		~Animal()
		{
			removeFromZookeper(); //!!!When animal is destroyed by its owning Zoo, clean the ZooKepers list too
		}


		std::string name;

		virtual AnimalType getType() { return AnimalType::none; }; //not pure virtual since i will have a vector of base type pointers

		Zookeeper<Animal>* keeper; //!!! will this generic <Animal> work with polymorphism? Or https://stackoverflow.com/questions/4030224/whats-the-use-of-the-derived-class-as-a-template-parameter


		void assignToZookeper(Zookeeper<Animal>* keeper)
		{
			this->keeper = keeper;
			keeper->assignAnimalToMe(this);
		}

		void removeFromZookeper()
		{
			this->keeper->removeAnimalFromMe(this);
			this->keeper = nullptr;
		}

	};


	class Elephant : public Animal
	{
	public:

		Elephant(std::string name, Zookeeper<Elephant>* keeper, float height) :Animal(name, (Zookeeper<Animal>*)keeper), maxJumpHeight(height) {}; //Animal constructor expects a Zookeeper<Animal>*

		AnimalType getType() override
		{
			return AnimalType::ElephantType;
		}

		float maxJumpHeight;

		void jumpTheLoop()
		{
			std::cout << name << " jumps the Loop." << std::endl;
		}

	};


	class Giraffe : public Animal
	{
	public:

		Giraffe(std::string name, Zookeeper<Giraffe>* keeper, float duration) :Animal(name, (Zookeeper<Animal>*)keeper), maxHandstandDuration(duration) {}; //Animal constructor expects a Zookeeper<Animal>*

		AnimalType getType() override
		{
			return AnimalType::GiraffeType;
		}

		float maxHandstandDuration;

		void doHandstand()
		{
			std::cout << name << " does a handstand." << std::endl;
		}

	};


	class ElephantKeeper : public Zookeeper<Elephant>
	{
	public:

		void makeElephantsJump()
		{
			for (int i = 0; i < animals.size(); i++)
			{
				Elephant* e = animals.at(i);
				std::cout <<e->name << " jumps "<< e->maxJumpHeight << " meters high." << std::endl;
			}
		}

	};

	class GiraffeKeeper : public Zookeeper<Giraffe>
	{
	public:

		void makeGiraffesHandstand()
		{
			for (auto& a : animals)
			{
				std::cout << a->name << " does a Handstand for " << a->maxHandstandDuration << " minutes." << std::endl;
			}
		}

	};

	class Zoo
	{
	public:
		std::vector<std::unique_ptr<Animal>> animals; //the zoo owns the animals

		std::unique_ptr<ElephantKeeper> elephantKeeper;
		std::unique_ptr<GiraffeKeeper> giraffeKeeper;

		Zoo()
		{
			animals = std::vector<std::unique_ptr<Animal>>();

			elephantKeeper = std::unique_ptr<ElephantKeeper>(new ElephantKeeper());
			giraffeKeeper = std::unique_ptr<GiraffeKeeper>(new GiraffeKeeper());
		}

		Elephant* buyElephant(std::string name, float height)
		{
			Elephant* e = new Elephant(name, elephantKeeper.get(), height);
			animals.push_back(std::unique_ptr<Elephant>(e)); //!!! type <Elephant> pushed back into vector of type <Animal>
			elephantKeeper.get()->animals.push_back(e);
			return e;
		}

		Giraffe* buyGiraffe(std::string name, float duration)
		{
			Giraffe* g = new Giraffe(name, giraffeKeeper.get(), duration);
			animals.push_back(std::unique_ptr<Giraffe>(g)); //!!! type <Elephant> pushed back into vector of type <Animal>
			giraffeKeeper.get()->animals.push_back(g);
			return g;
		}

	};


	void test()
	{
		Zoo* z = new Zoo();
		Elephant* e1 = z->buyElephant("Dotty", 10.0f);
		Elephant* e2 = z->buyElephant("Betty", 1.5f);
		Giraffe* g1 = z->buyGiraffe("Bernd", 32.5f);
		Giraffe* g2 = z->buyGiraffe("Gunther", 42.0f);
		
		z->elephantKeeper.get()->makeElephantsJump();

		//z->giraffeKeeper.get()->makeGiraffesHandstand();

		delete(z);
	}
}