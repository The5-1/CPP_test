#pragma once

#include <string>
#include <vector>
#include <queue> //minimal FIFO queue, no iteration, just push and pop
#include <deque> //queue with more, allows arbitary insertion and iteration
#include <set> //unique set
#include <iostream>

#include <algorithm> //std::max




using std::string;

/******************************************************************
Event Queue
==============================================
Common Names:
- Finite State Machine
- PubSub pattern
- Message Queue typcally means between applications

http://gameprogrammingpatterns.com/event-queue.html
http://gameprogrammingpatterns.com/observer.html


Event Queue:
- holds a list of something that ALREADY HAPPENED
- typically globally interesting for a lot of systems
- broadcast

Request Queue / Message Queue:
- hols a list of things that should happen in the future
- typically sent to a single listener, like the audio system
- singlecast: e.g. just call playSound()

Work Queue:
- one queue that multiple systems pop from
- only one system is responsible for a given event
-- or multiple threads of one system
- tpyically complex to schedule


******************************************************************/

namespace ArchitectureTest
{
	struct PlaySoundMessage
	{
		string soundID;
		int volume;

		PlaySoundMessage(string s, int v) :soundID(s), volume(v) {}
	};

	class Audio
	{
	public:

		//it seems queues should be fixed size and cache friendly allocated
		//--> ring buffer
		static std::deque<PlaySoundMessage> queue; //allows iteration and arbitrary insertion

		Audio()
		{
			queue = std::deque<PlaySoundMessage>();
		}

		static void playSound(std::string soundID, int volume)
		{
			auto back = queue.back();

			//keep the queue clean by only pushing relevant messages on it --> more burden when calling playSound()
			//do the cleanup when processing the queue --> more burden when handling the messages

			if (back.soundID == soundID) //e.g. if the last element already is this sound, dont play a duplicate, because that doubles volume
			{				
				queue.push_back(PlaySoundMessage(soundID, std::max(volume, back.volume))); //push the louder one back
			}
		}


		static void processQueue()
		{
			for(int i = 0; i < 5; i++)
			{
				auto msg = queue.pop_back;
				std::cout << "Audio played: ID:" << msg.soundID << " at volume: " << msg.volume << std::endl;
			}
		}

		static void update()
		{
			processQueue();
		}
	};

	class Menu
	{

	public:

		void onSelect(int index)
		{
			Audio::playSound("SOUND_INDEX_" + std::to_string(index), 255);
		}

	};

}