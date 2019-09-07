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
using namespace std;

class Instrument {
public:
	String instrumentName;
	int velocityCount;
	AudioSampleBuffer*** micPointers;
	FileManager* fileManager;
	list<IteratorPack>* iterators;

	//~Instrument();
	void createBuffers();
	void fillBuffer(int velocity, AudioSampleBuffer* bufferToFill);
	void triggerInstrument(AudioBuffer<float>* bufferToFill, std::vector<float> micGains, float noteVelocity, int timeStamp, int numOutputChannels, int blockSize, float monoPan, float stereoPan[2]);
	Instrument(String instrumentName, int velocityCount, FileManager* fileManager);
	void Instrument::fillFromIterators(AudioSampleBuffer output);
	~Instrument();
};