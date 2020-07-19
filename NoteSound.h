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
	FileManager* fileManager;
	AudioProcessor* processor;
	void triggerSound(std::map<String, float> micGains, float noteVelocity, int timeStamp, float monoPan, AudioProcessor *processor);
	void killSound(int killTimeStamp);
	NoteSound(NoteProperties* noteProperties, FileManager* fileManager, AudioProcessor* processor, std::map<String, AudioSampleBuffer*>* micOutputs);
	void fillFromIterators();
	void setBlockSize(int blockSize);
	~NoteSound();

private:
	//HitIterator *hitIterator1;
	//HitIterator *hitIterator2;
	VelocityLevelPlayer velocityLevelPlayer;
	int blockSize;

public:
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoteSound)
};