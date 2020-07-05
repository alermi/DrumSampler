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
	HitIterator::HitIterator(AudioProcessor* processor);
	void kill(int killTimeStamp);
	bool hasEnded();
	void trigger(std::map<String, std::map<String, AudioSampleBuffer*>> micMap, std::map<String, float> micGains, String indexString, float noteVelocity, int timeStamp, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues);
	void iterate(AudioSampleBuffer output, bool fadeOut);
	int timeStamp;


private:
	std::list<BufferIterator>* bufferIterators;

	AudioProcessor* processor;
	const std::vector<String> micNames = MicController::getMicNames();
};