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
	float velocity;
	int samplesLeft;
	bool isHiHatOpen;
	int channelNum;

	IteratorPack(AudioSampleBuffer *address, float velocity, int samplesLeft, bool isHiHatOpen, int channelNum);
};