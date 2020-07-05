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

HitIterator::HitIterator(AudioProcessor* processor) {
	this->processor = processor;
	this->bufferIterators = new std::list<BufferIterator>();
	for (int i = 0; i < micNames.size(); i++) {
		BufferIterator newPack;
		bufferIterators->push_back(newPack);
	}
	timeStamp = -1;
}

void HitIterator::trigger(std::map<String, std::map<String, AudioSampleBuffer*>> micMap, std::map<String, float> micGains, String indexString, float noteVelocity, int timeStamp, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues) {
	//Kill the previous playing sounds
	//kill(timeStamp);
	//Create an iterator to be played for each microphone
	this->timeStamp = timeStamp;
	//TODO: DELETE, TESTING
	if (timeStamp != 0) {
		DBG("Hi");
	}
	std::list<BufferIterator>::iterator it;
	std::list<BufferIterator>::iterator end;
	it = bufferIterators->begin();
	end = bufferIterators->end();
	for (int i = 0; i < micNames.size(); i++) {
		jassert(it != end);
		String micName = micNames[i];
		AudioSampleBuffer* currBuffer = micMap[micName][indexString];
		if (currBuffer->getNumChannels() > 0) {
			//BufferIterator currPack = bufferIterators[i];

			it->trigger(currBuffer, noteVelocity*micGains[micName], monoPanValues, stereoPanValues, micToExtraChannelMap[i]);
			//bufferIterators->push_back(newPack);
		}
		it++;
	}
}

void HitIterator::kill(int killTimeStamp)
{
	//std::list<BufferIterator>::iterator it;
	//std::list<BufferIterator>::iterator end;
	//it = bufferIterators->begin();
	//end = bufferIterators->end();

	////Loop through the iterators left from previous blocks and fill the current block
	//while (it != end) {
	//	// If this comparison was strictly less, there may be issues when both are 0
	//	// This is also checked in the kill function. If this is going to be changed, both must be changed.
	//	if (it->timestamp <= killTimeStamp) {
	//		it->kill(killTimeStamp);
	//	}
	//	it++;
	//}
}

bool HitIterator::hasEnded()
{
	bool ended = true;
	for (BufferIterator iterator : *bufferIterators) {
		ended = ended && iterator.hasEnded;
	}
	return ended;
}

void HitIterator::iterate(AudioSampleBuffer output, bool fadeOut)
{

	std::list<BufferIterator>::iterator it;
	std::list<BufferIterator>::iterator end;
	it = bufferIterators->begin();
	end = bufferIterators->end();

	//Loop through the iterators left from previous blocks and fill the current block
	while (it != end) {
		BufferIterator currPack = *it;

		if (it->hasEnded) {
			it->reset();
			it++;
			//it = bufferIterators->erase(it);
		}
		else {
			jassert(processor->getBus(false, 0)->isEnabled());
			//jassert(processor->getBus(false, currPack.extraBusNumber)->isEnabled());

			AudioSampleBuffer mainBuffer = processor->getBusBuffer(output, false, 0);
			AudioSampleBuffer extraBuffer = processor->getBusBuffer(output, false, currPack.extraBusNumber);
			std::array<AudioSampleBuffer*, 2> outputs = { &mainBuffer ,&extraBuffer };
			jassert(timeStamp != -1);

			it->iterate(outputs, timeStamp, output.getNumSamples(), fadeOut);
			it++;
		}
	}
	if (timeStamp > 0) {
		timeStamp = 0;
	}
}
