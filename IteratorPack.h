/*
  ==============================================================================

    IteratorPack.h
    Created: 16 Aug 2019 9:59:19pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include <array>
#include <iterator>

class IteratorPack {
public:
	AudioSampleBuffer *address;
	int sampleLeftAt;
	int timestamp;
	float velocity;
	int samplesLeft;
	int channelNum;
	bool hasEnded;
	int extraBusNumber;
	//AudioSampleBuffer *mainBuffer;
	std::array<float, 2> monoPanValues;
	std::vector<std::array<float, 2>> stereoPanValues;

	IteratorPack(AudioSampleBuffer *address, float velocity, int samplesLeft, int channelNum, int timestamp, AudioSampleBuffer *mainBuffer, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues);
	//void iterate(AudioSampleBuffer output);
	void iterate(std::array<AudioSampleBuffer*, 2> outputs);
};