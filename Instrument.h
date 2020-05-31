/*
  ==============================================================================

    Instrument.h
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/
//#include "../JuceLibraryCode/JuceHeader.h"
#pragma once
#include "FileManager.h"
#include "IteratorPack.h"
#include <vector>
#include <list>
#include <iterator>
#include <array>

//TODO: Remove all namespace stds
using namespace std;

class Instrument {
public:
	String instrumentName;
	int velocityCount;
	AudioSampleBuffer*** micPointers;
	FileManager* fileManager;
	list<IteratorPack>* iterators;
	AudioProcessor* processor;
	//AudioSampleBuffer mainBuffer;
	//static const int micToExtraChannelMap[7];
	int createBuffers();
	void triggerInstrument(std::vector<float> micGains, float noteVelocity, int timeStamp, float monoPan, float stereoPan[2], AudioProcessor *processor);
	Instrument(String instrumentName, int velocityCount, FileManager* fileManager, AudioProcessor* processor);
	void fillFromIterators(AudioSampleBuffer output);
	~Instrument();
};