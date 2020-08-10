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
#include <cmath>
//TODO: Remove all namespace stds
using namespace std;

class NoteSound {

public:
	//String instrumentName;
	//int velocityCount;
	NoteProperties *noteProperties;
	FileManager* fileManager;
	AudioProcessor* processor;
	void triggerSound(std::map<String, float> micGains, float noteVelocity, int timeStamp, AudioProcessor *processor);
	void killSound(int killTimeStamp);
	NoteSound(NoteProperties* noteProperties, FileManager* fileManager, AudioProcessor* processor, std::map<String, AudioSampleBuffer*>* micOutputs, std::map<String, bool> bleedMap, int velocityCount, int roundRobinCount);
	void fillFromIterators(bool isMutingBleeds);
	void setBlockSize(int blockSize);
	~NoteSound();

private:

	//TODO: Find a way to make this non pointer
	std::vector<VelocityLevelPlayer*> velocityLevelPlayers;
	//VelocityLevelPlayer velocityLevelPlayer;
	int blockSize;
	int roundRobinCount;

public:
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoteSound)
	JUCE_LEAK_DETECTOR(NoteSound)
};