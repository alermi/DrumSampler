/*
  ==============================================================================

    NoteSound.h
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/
//#include "../JuceLibraryCode/JuceHeader.h"
#pragma once
#include "FileManager.h"
//#include "BufferIterator.h"
#include "MicController.h"
#include "HitIterator.h"
#include "VelocityLevelPlayer.h"

#include <vector>
#include <list>
#include <iterator>
#include <array>

//TODO: Remove all namespace stds
using namespace std;

class NoteSound {

public:
	//String instrumentName;
	//int velocityCount;
	NoteProperties *noteProperties;

	std::map<String, std::map<String, AudioSampleBuffer*>> micMap;
	FileManager* fileManager;
	list<HitIterator>* iterators;
	AudioProcessor* processor;
	//AudioSampleBuffer mainBuffer;
	//static const int micToExtraChannelMap[7];S
	//void createBuffers();
	void triggerSound(std::map<String, float> micGains, float noteVelocity, int timeStamp, float monoPan, AudioProcessor *processor);
	void killSound(int killTimeStamp);
	NoteSound(NoteProperties* noteProperties, FileManager* fileManager, AudioProcessor* processor, std::map<String, AudioSampleBuffer*>* micOutputs);
	void fillFromIterators(int blockSize);
	~NoteSound();

private:
	//HitIterator *hitIterator1;
	//HitIterator *hitIterator2;
	VelocityLevelPlayer velocityLevelPlayer;

public:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoteSound)
};