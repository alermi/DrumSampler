/*
  ==============================================================================

    IteratorPack.cpp
    Created: 16 Aug 2019 10:22:09pm
    Author:  Ani

  ==============================================================================
*/

#include "IteratorPack.h"

IteratorPack::IteratorPack(AudioSampleBuffer* address, float velocity, int samplesLeft, bool isHiHatOpen, int channelNum) {
	this->address = address;
	this->velocity = velocity;
	this->samplesLeft = samplesLeft;
	this->isHiHatOpen = isHiHatOpen;
	this->channelNum = channelNum;
	this->sampleLeftAt = 0;
}