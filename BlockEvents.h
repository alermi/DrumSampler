/*
  ==============================================================================

    BlockEvents.h
    Created: 13 Jul 2020 11:42:44pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "TriggerInformation.h"
#include "KillInformation.h"

class BlockEvents {

public:

	BlockEvents();
	void setBlockSize(int blockSize);
	void processEvent(EventInformation eventInfo);
	void startReceivingHits();
	void finishReceivingHits();
	bool isFull();
	bool isEmpty();

	EventInformation getNextEvent();
	int peekAtNextEventTimeStamp();
	bool hasMoreEvents();
	void clear();
private:
	int blockSize;
	bool isReceivingEvents;
	std::vector<EventInformation>::iterator it;
	std::vector<EventInformation>::iterator end;
	std::vector<EventInformation> events;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BlockEvents)

};