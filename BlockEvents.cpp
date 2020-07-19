/*
  ==============================================================================

    BlockEvents.cpp
    Created: 13 Jul 2020 11:42:44pm
    Author:  Ani

  ==============================================================================
*/

#include "BlockEvents.h"

//BlockEvents::Event::Event()
//{
//	this->timeStamp = -1;
//	this->isNoteOn = false;
//}
//
//BlockEvents::Event::Event(int timeStamp, bool isNoteOn)
//  {
//	this->timeStamp = timeStamp;
//	this->isNoteOn = isNoteOn;
//  }


BlockEvents::BlockEvents()
{
	this->isReceivingEvents = true;
	this->blockSize = 0;
}

void BlockEvents::setBlockSize(int blockSize)
{
	this->isReceivingEvents = true;
	this->events.clear();
	this->blockSize = blockSize;
	// TODO: reconsider the events size
	this->events.reserve(blockSize / 2);

}

void BlockEvents::processEvent(EventInformation eventInfo)
{
	jassert(this->isReceivingEvents);
	
	if (isFull() || eventInfo.timeStamp >= blockSize || eventInfo.timeStamp < 0) {
		jassertfalse;
		return;
	}

	events.push_back(eventInfo);
}



void BlockEvents::startReceivingHits()
{
	jassert(!this->isReceivingEvents);
	jassert(this->isEmpty());
	events.clear();
 	jassert(events.capacity() >= (blockSize / 2));
	this->isReceivingEvents = true;
}

bool compareKillGreater(const EventInformation& first, const EventInformation& second)
{
	if (first.timeStamp == second.timeStamp) {
		if (first.isNoteOn && !second.isNoteOn) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return first.timeStamp < second.timeStamp;
	}
}
//bool compareTimeStamp(const BlockEvents::Event& first, const BlockEvents::Event& second)
//{
//	return first.timeStamp < second.timeStamp;
//}


void BlockEvents::finishReceivingHits()
{
	jassert(this->isReceivingEvents);
	this->isReceivingEvents = false;
	//this->events.sort(compareKillGreater);
	//this->events.unique(compareTimeStamp);

	this->it = events.begin();
	this->end = events.end();
	std::sort(it, end, compareKillGreater);
	while (it != end) {
		auto next = (it + 1);

		while ((next != end) && (next->timeStamp == it->timeStamp)) {
			events.erase(next);
			next = it + 1;
			end = events.end();
		}
		//TODO: CHeck if this works properly
		if (!it->isNoteOn) {
			while ((next != end) && (!next->isNoteOn)) {
				events.erase(next);
				next = it + 1;
				end = events.end();
			}
		}
		it++;
	}
	this->it = events.begin();
	this->end = events.end();
}

// Has to be checked before if the BlockEevents is not empty.
EventInformation BlockEvents::getNextEvent()
{
	jassert(isReceivingEvents == false);
	jassert(hasMoreEvents());

	//Event nextEvent = Event(it->timeStamp, it->isNoteOn);
	//if (it != end) {
	//	events.erase(it);
	//}
	EventInformation nextEvent = *it;
	it++;
	return nextEvent;
}

int BlockEvents::peekAtNextEventTimeStamp()
{
	jassert(isReceivingEvents == false);
	jassert(hasMoreEvents());
	return it->timeStamp;
}

bool BlockEvents::hasMoreEvents()
{
	return !isEmpty();
}

bool BlockEvents::isFull() {
 	jassert(events.capacity() >= (blockSize / 2));
	return (events.size() >= (blockSize / 2));
}

bool BlockEvents::isEmpty() {
	jassert(!isReceivingEvents);
	return it == end;
}

void BlockEvents::clear() {
	isReceivingEvents = true;
	blockSize = 0;
	events.clear();
}