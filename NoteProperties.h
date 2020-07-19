/*
  ==============================================================================

    NoteProperties.h
    Created: 14 Jun 2020 8:01:49am
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class NoteProperties{
public:
	int noteNum;
	int velocityCount;
	int robinCount;
	int isInstrument;
	String instrumentName;
	String generalControllerName;
	String specificControllerName;

	NoteProperties(int noteNum, int velocityCount, int robinCount, int isInstrument, String generalControllerName, String specificControllerName, String instrumentName) {
		this->noteNum = noteNum;
		this->velocityCount = velocityCount;
		this->robinCount = robinCount;
		this->isInstrument = isInstrument;
		this->generalControllerName = generalControllerName;
		this->specificControllerName = specificControllerName;
		this->instrumentName = instrumentName;
	}
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoteProperties)
	JUCE_LEAK_DETECTOR(NoteProperties)
};