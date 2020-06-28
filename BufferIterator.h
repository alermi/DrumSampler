/*
  ==============================================================================

    BufferIterator.h
    Created: 16 Aug 2019 9:59:19pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include <array>
#include <iterator>

#define SAMPLES_TO_KILL 100

class BufferIterator {
public:
	AudioSampleBuffer *address;
	int sampleLeftAt;
	int timestamp;
	float velocity;
	int samplesLeft;
	int channelNum;
	bool hasEnded;
	int extraBusNumber;
	int killTimeStamp;
	//AudioSampleBuffer *mainBuffer;
	std::array<float, 2> monoPanValues;
	std::vector<std::array<float, 2>> stereoPanValues;

	BufferIterator(AudioSampleBuffer *address, float velocity, int samplesLeft, int timestamp, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues, int extraBusNumber);
	//void iterate(AudioSampleBuffer output);
	void iterate(std::array<AudioSampleBuffer*, 2> outputs);
	void kill(int killTimeStamp);
private:
	int getSamplesToCopy(std::array<AudioSampleBuffer*, 2> outputs);
};