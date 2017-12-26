#pragma once

#include <vector>
#include <deque> //queue with append and prepend functionality
#include <iostream>
#include <memory>
#include <bitset> //for component bitmask
#include <functional> //for std::function //should i want function pointers
#include <iterator> //for implementing a custom iterator for my scene

/*
https://www.gamedev.net/articles/programming/general-and-gameplay-programming/understanding-component-entity-systems-r3013/


*/



namespace Test_ECS_Inheritance01
{

	const unsigned int ComponentNumber = 2;
	enum ComponentType { none, Renderable, Moveable };

	class ComponentBitmask
	{
	public:
		std::bitset<ComponentNumber> mask;

		void addComponentType(ComponentType type)
		{
			mask.set(type - 1);
		}

		void removeComponentType(ComponentType type)
		{
			mask.reset(type - 1);
		}

		static std::bitset<ComponentNumber> getComponentTypeMask(ComponentType type)
		{
			std::bitset<ComponentNumber> mask;
			
			if (type == ComponentType::none)
			{
				return mask;
			}
			else
			{
				mask.set(type - 1);
				return mask;
			}
		}

		bool compare(const ComponentBitmask& other)
		{
			return (this->mask == other.mask);
		}


		ComponentBitmask& operator|(const ComponentType type)
		{
			this->addComponentType(type);
			return *this;
		}

		bool operator==(const ComponentBitmask& other)
		{	
			return this->compare(other);
		}

	};

	class IComponent
	{
	public:
		std::string name;
		//https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c
		virtual ComponentType getType() { return ComponentType::none; }; 

		IComponent(std::string name) : name(name) {}

	};


	class Entity
	{
	public:
		std::string name;
		ComponentBitmask mask;

		Entity* createChild(std::string name)
		{
			Entity* e = new Entity(name, this);
			childs.push_back(e);
			return e;
		}

		void addComponent(IComponent* component)
		{
			components.push_back(component);
			mask = mask | component->getType();
		}

	private:
		friend class Scene; //scene may call the constructor to generate the root Entity
		Entity(std::string name, Entity* parent) : name(name), parent(parent){}

		Entity* parent;
		std::vector<Entity*> childs;

		std::vector<IComponent*> components;
	};

	class Scene
	{
	public:
		Scene()
		{
			root = new Entity("root", nullptr);
		}

		Entity* createChild(std::string name)
		{
			return root->createChild(name);
		}

		Entity* root;

		void iterate() //pass a component mask and a function pointer that does something when the mask hits
		{
			//https://stackoverflow.com/questions/5278580/non-recursive-depth-first-search-algorithm

			std::deque<Entity*> nodesToVisit;
			nodesToVisit.push_back(root);

			while (!nodesToVisit.empty()) {

				Entity* current = nodesToVisit.front(); //take first
				nodesToVisit.pop_front(); //and delete it

				if(searchMode == 0)
				{
					//depth first = prepend
					nodesToVisit.insert(nodesToVisit.begin(), current->childs.begin(), current->childs.end());
				}
				else if (searchMode == 1)
				{
					//breadth first = append
					nodesToVisit.insert(nodesToVisit.end(), current->childs.begin(), current->childs.end());
				}

				processEntity(current);
			}
		}

		std::vector<Entity*> getEntities()
		{
			std::vector<Entity*> outList;

			std::deque<Entity*> nodesToVisit;
			nodesToVisit.push_back(root);

			while (!nodesToVisit.empty()) {

				Entity* current = nodesToVisit.front(); //take first
				nodesToVisit.pop_front(); //and delete it

				if (searchMode == 0)
				{
					//depth first = prepend
					nodesToVisit.insert(nodesToVisit.begin(), current->childs.begin(), current->childs.end());
				}
				else if (searchMode == 1)
				{
					//breadth first = append
					nodesToVisit.insert(nodesToVisit.end(), current->childs.begin(), current->childs.end());
				}

				outList.push_back(current);
			}
			return outList;
		}

		//void processEntity(Entity* entity, std::function<void()> processingFunction)
		void processEntity(Entity* entity)
		{
			std::cout << entity->name << std::endl;
		}

		Entity* begin()
		{
			return root;
		}

		Entity* end()
		{
			return nullptr;
		}

		Entity* operator++()
		{

		}

	private:
		unsigned int searchMode = 0; //0=DFS, 1=BFS

	};


	class System
	{
	public:
		//not sure if Systems got anything in common
		std::string name;
		ComponentBitmask mask;
		virtual void update() {};

		System(std::string name) : name(name) {}
		bool checkBitmask(Entity* entity)
		{
			return (this->mask == entity->mask);
		}
	};


	class RenderableC : public IComponent
	{
	public:
		RenderableC() :IComponent("Renderable") {}

		ComponentType getType() override //override is "optional" makes the compiler fail if the function does not have the same signature
		{
			return ComponentType::Renderable;
		}

		std::string model;
	};

	class Renderer : public System
	{
	public:
		Renderer() :System("Renderer")
		{
			mask = mask|ComponentType::Renderable;
		}

		void renderScene(Scene* scene)
		{
			std::cout << "Renderer: " << std::endl;
			for (Entity* e : scene->getEntities())
			{
				if (checkBitmask(e))
				{
					std::cout << " render: " << e->name << std::endl;
				}
			}
		}
	};


	void test()
	{
		Scene* scene = new Scene();
		Entity* A = scene->createChild("A");
		Entity* AA = A->createChild("AA");
		Entity* AB = A->createChild("AB");
		Entity* AC = A->createChild("AC");
		Entity* B = scene->createChild("B");
		Entity* BA = B->createChild("BA");
		Entity* BB = B->createChild("BB");
		Entity* BBA = BB->createChild("BBA");
		Entity* BBB = BB->createChild("BBB");
		Entity* BBC = BB->createChild("BBC");
		//scene->iterate();

		RenderableC* rc = new RenderableC();
		AA->addComponent(rc);


		Renderer* renderer = new Renderer();
		renderer->renderScene(scene);

	};
}