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

class BlockEvents {

public:
	class Event {
	public:
		Event();
		Event(int timeStamp, bool isNoteOn);
		int timeStamp;
		bool isNoteOn;
	};

	BlockEvents();
	void setBlockSize(int blockSize);
	void processEvent(int timeStamp, bool isNoteOn);
	void startProcessingHits();
	void finishProcessingHits();
	bool isFull();
	bool isEmpty();

	Event getNextEvent();
	bool hasMoreEvents();
	void clear();
private:
	int blockSize;
	bool isProcessingHits;
	std::vector<Event>::iterator it;
	std::vector<Event>::iterator end;
	std::vector<Event> events;

};