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
#include <ctime>

class HitIterator {
public:
	HitIterator::HitIterator(AudioProcessor* processor, std::map<String, std::map<int, AudioSampleBuffer*>> micMap, std::map<String, AudioSampleBuffer*> *micOutputs, std::map<String, bool> bleedMap, int roundRobinCount);
	bool hasEnded();
	void trigger(TriggerInformation triggerInfo);
	void iterate(int startSample, int endSample, bool fadeOut);
	int timeStamp;
	void reset();

private:
	std::map<String, BufferIterator> bufferIterators;
	std::map<String, std::map<int, AudioSampleBuffer*>> micMap;
	AudioProcessor* processor;
	std::vector<String> micNames = MicController::getMicNames();
	std::map<String, AudioSampleBuffer*>* micOutputs;

	std::map<String, bool> bleedMap;
	int roundRobinCount;
	int previousHitRobinNum;
	Random randomGenerator;
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HitIterator)
	JUCE_LEAK_DETECTOR(HitIterator)
};