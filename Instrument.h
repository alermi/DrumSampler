/*
  ==============================================================================

    Instrument.h
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/
//#include "../JuceLibraryCode/JuceHeader.h"
#pragma once
#include "SampleManager.h"
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
	AudioSampleBuffer* tempBuffer;
	SampleManager* sampleManager;
	AudioFormatManager* formatManager;

	list<IteratorPack>* iterators;

	void createBuffers();
	void fillBuffer(int velocity, AudioSampleBuffer* bufferToFill);
	void triggerInstrument(AudioBuffer<float>* bufferToFill, AudioSampleBuffer *** instrumentSamples, std::vector<float> micGains, int numLevels, float noteVelocity, int timeStamp, int numOutputChannels, int blockSize);
	//void triggerInstrument(AudioBuffer<float>* bufferToFill, AudioSampleBuffer ** instrumentSamples, std::vector<float> micGains, int numLevels, float noteVelocity, int timeStamp, int numOutputChannels, int blockSize);
	AudioSampleBuffer getBuffer();
	Instrument(String instrumentName, int velocityCount, AudioFormatManager* formatManager, SampleManager* sampleManager, list<IteratorPack>* iterators);



};