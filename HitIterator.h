/*
  ==============================================================================

    HitIterator.h
    Created: 27 Jun 2020 5:22:10pm
    Author:  Ani

  ==============================================================================
*/

#pragma once

#include "BufferIterator.h"
#include "MicController.h"
class HitIterator {
public:
	HitIterator::HitIterator(AudioProcessor* processor, std::map<String, std::map<String, AudioSampleBuffer*>> micMap, std::map<String, float> micGains, String indexString, float noteVelocity, int timeStamp, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues);
	void kill(int killTimeStamp);
	bool hasEnded();
	void iterate(AudioSampleBuffer output);

	int timestamp;
private:
	std::list<BufferIterator>* bufferIterators;

	AudioProcessor* processor;
	const std::vector<String> micNames = MicController::getMicNames();
};