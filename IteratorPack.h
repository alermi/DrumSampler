/*
  ==============================================================================

    IteratorPack.h
    Created: 16 Aug 2019 9:59:19pm
    Author:  Ani

  ==============================================================================
*/

#pragma once

class IteratorPack {
public:
	float* address;
	float velocity;
	int samplesLeft;
	bool isHiHatOpen;
	int channelNum;

	IteratorPack(float* address, float velocity, int samplesLeft, bool isHiHatOpen, int channelNum);
};