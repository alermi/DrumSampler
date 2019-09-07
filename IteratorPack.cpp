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
}