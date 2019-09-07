/*
  ==============================================================================

    IteratorPack.h
    Created: 16 Aug 2019 9:59:19pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class IteratorPack {
public:
	AudioSampleBuffer *address;
	int sampleLeftAt;
	int timestamp;
	float velocity;
	int samplesLeft;
	int channelNum;
	bool hasEnded;

	IteratorPack(AudioSampleBuffer *address, float velocity, int samplesLeft, int channelNum, int timestamp);
	void iterate(AudioSampleBuffer output);
};