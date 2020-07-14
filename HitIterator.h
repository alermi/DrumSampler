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
#include "TriggerInformation.h"
class HitIterator {
public:
	HitIterator::HitIterator(AudioProcessor* processor, std::map<String, std::map<int, AudioSampleBuffer*>> micMap, std::map<String, AudioSampleBuffer*> *micOutputs);
	bool hasEnded();
	void trigger(TriggerInformation triggerInfo);
	void iterate(int startSample, int endSample, bool fadeOut);
	int timeStamp;
	void reset();

	static const int NUM_OF_SAME_SAMPLE = 5;

private:
	std::map<String, BufferIterator> bufferIterators;
	std::map<String, std::map<int, AudioSampleBuffer*>> micMap;
	AudioProcessor* processor;
	const std::vector<String> micNames = MicController::getMicNames();
	std::map<String, AudioSampleBuffer*>* micOutputs;
};