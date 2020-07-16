/*
  ==============================================================================

    BlockEvents.cpp
    Created: 13 Jul 2020 11:42:44pm
    Author:  Ani

  ==============================================================================
*/

#include "BlockEvents.h"

BlockEvents::Event::Event()
{
	this->timeStamp = -1;
	this->isNoteOn = false;
}

BlockEvents::Event::Event(int timeStamp, bool isNoteOn)
  {
	this->timeStamp = timeStamp;
	this->isNoteOn = isNoteOn;
  }


BlockEvents::BlockEvents()
{
	this->isProcessingHits = true;
	this->blockSize = 0;
}

void BlockEvents::setBlockSize(int blockSize)
{
	this->isProcessingHits = true;
	this->events.clear();
	this->blockSize = blockSize;
	// TODO: reconsider the events size
	this->events.reserve(blockSize / 2);

}

void BlockEvents::processEvent(int timeStamp, bool isNoteOn)
{
	jassert(this->isProcessingHits);
	
	if (isFull() || timeStamp >= blockSize || timeStamp < 0) {
		jassertfalse;
		return;
	}
	
	events.push_back(Event(timeStamp, isNoteOn));
}



void BlockEvents::startProcessingHits()
{
	jassert(!this->isProcessingHits);
	jassert(this->isEmpty());
	events.clear();
	jassert(events.capacity() == (blockSize / 2));
	this->isProcessingHits = true;
}

bool compareKillGreater(const BlockEvents::Event& first, const BlockEvents::Event& second)
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


void BlockEvents::finishProcessingHits()
{
	jassert(this->isProcessingHits);
	this->isProcessingHits = false;
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
		it++;
	}
	this->it = events.begin();
	this->end = events.end();
}

// Has to be checked before if the BlockEevents is not empty.
BlockEvents::Event BlockEvents::getNextEvent()
{
	jassert(isProcessingHits == false);
	jassert(hasMoreEvents());

	Event nextEvent = Event(it->timeStamp, it->isNoteOn);
	//if (it != end) {
	//	events.erase(it);
	//}
	it++;
	return nextEvent;
}

bool BlockEvents::hasMoreEvents()
{
	return !isEmpty();
}

bool BlockEvents::isFull() {
	jassert(events.capacity() == (blockSize / 2));
	return (events.size() >= (blockSize / 2));
}

bool BlockEvents::isEmpty() {
	jassert(!isProcessingHits);
	return it == end;
}

void BlockEvents::clear() {
	isProcessingHits = true;
	blockSize = 0;
	events.clear();
}