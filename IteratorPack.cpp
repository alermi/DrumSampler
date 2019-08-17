/*
  ==============================================================================

    IteratorPack.cpp
    Created: 16 Aug 2019 10:22:09pm
    Author:  Ani

  ==============================================================================
*/

#include "IteratorPack.h"

IteratorPack::IteratorPack(float* address, float velocity, int samplesLeft, bool isHiHatOpen) {
	this->address = address;
	this->velocity = velocity;
	this->samplesLeft = samplesLeft;
	this->isHiHatOpen = isHiHatOpen;
}