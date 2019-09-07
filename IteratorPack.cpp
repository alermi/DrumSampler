/*
  ==============================================================================

    IteratorPack.cpp
    Created: 16 Aug 2019 10:22:09pm
    Author:  Ani

  ==============================================================================
*/

#include "IteratorPack.h"

IteratorPack::IteratorPack(AudioSampleBuffer* address, float velocity, int samplesLeft, int channelNum, int timestamp) {
	this->address = address;
	this->velocity = velocity;
	this->samplesLeft = samplesLeft;
	this->channelNum = channelNum;
	this->sampleLeftAt = 0;
	this->timestamp = timestamp;
	this->hasEnded = false;
}

void IteratorPack::iterate(AudioSampleBuffer output) {
	jassert(this->hasEnded==false);
	int samplesToCopy = std::min(samplesLeft, output.getNumSamples() - timestamp);
	output.addFrom(channelNum, timestamp, *address, 0, sampleLeftAt, samplesToCopy, velocity);
	//If the iterator has reached the end, update the boolean.
	if (samplesToCopy == samplesLeft) {
		hasEnded = true;
	}
	//Else update the remaining numbers.
	else {
		sampleLeftAt += samplesToCopy;
		samplesLeft -= samplesToCopy;
		timestamp = 0;
	}
}