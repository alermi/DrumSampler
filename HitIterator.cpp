/*
  ==============================================================================

    HitIterator.cpp
    Created: 27 Jun 2020 5:22:10pm
    Author:  Ani

  ==============================================================================
*/

#include "HitIterator.h"

// TODO: Fix the ride mic extra channel map
const int micToExtraChannelMap[] = { 3,3,4,4,5,6,7,1,1,1,1,2,3,1,1,1,1 };

HitIterator::HitIterator(AudioProcessor* processor, std::map<String, std::map<int, AudioSampleBuffer*>> micMap, std::map<String, AudioSampleBuffer*>* micOutputs) {
	this->processor = processor;
	this->micMap = micMap;
	for (int i = 0; i < micNames.size(); i++) {
		String micName = micNames[i];
		bufferIterators[micName];
	}
	timeStamp = -1;
	this->micOutputs = micOutputs;
}

void HitIterator::trigger(TriggerInformation triggerInfo) {
	this->timeStamp = triggerInfo.timeStamp;

	int version = rand() % NUM_OF_SAME_SAMPLE;

	for (int i = 0; i < micNames.size(); i++) {
		//jassert(it != end);
		String micName = micNames[i];
		AudioSampleBuffer* currBuffer = micMap[micName][version];
		if (currBuffer->getNumChannels() > 0) {			
			bufferIterators.at(micName).trigger(currBuffer, triggerInfo.noteVelocity*triggerInfo.micGains[micName], micToExtraChannelMap[i]);
		}
	}
}

bool HitIterator::hasEnded()
{
	bool ended = true;
	for (auto const& iterator : bufferIterators) {
		ended = ended && iterator.second.hasEnded;
	}
	return ended;
}
void HitIterator::reset()
{
	std::map<String, BufferIterator>::iterator it;
	std::map<String, BufferIterator>::iterator end;
	it = bufferIterators.begin();
	end = bufferIterators.end();

	while (it != end) {
		it->second.reset();
		it++;
	}
	timeStamp = -1;
	
}



void HitIterator::iterate(int startSample, int endSample, bool fadeOut)
{

	std::map<String, BufferIterator>::iterator it;
	std::map<String, BufferIterator>::iterator end;
	it = bufferIterators.begin();
	end = bufferIterators.end();

	//Loop through the iterators left from previous blocks and fill the current block
	while (it != end) {


		if (it->second.hasEnded) {
			//TODO: This reset can be moved right after iterate probably?
			it->second.reset();
			it++;
			//it = bufferIterators->erase(it);
		}
		else {
			jassert(processor->getBus(false, 0)->isEnabled());
			//jassert(processor->getBus(false, currPack.extraBusNumber)->isEnabled());

			jassert(timeStamp != -1);
			AudioSampleBuffer* someBuffer = micOutputs->at(it->first);
			it->second.iterate(someBuffer, startSample, endSample, fadeOut);
			it++;
		}
	}
	if (timeStamp > 0) {
		timeStamp = 0;
	}
	if (hasEnded() || fadeOut) {
		reset();
	}
}
