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

HitIterator::HitIterator(AudioProcessor* processor, std::map<String, std::map<int, AudioSampleBuffer*>> micMap, std::map<String, AudioSampleBuffer*>* micOutputs, std::map<String, bool> bleedMap, int roundRobinCount) {
	this->processor = processor;
	this->micMap = micMap;
	for (int i = 0; i < micNames.size(); i++) {
		String micName = micNames[i];
		bufferIterators[micName];
	}
	timeStamp = -1;
	this->micOutputs = micOutputs;
	this->bleedMap = bleedMap;
	this->roundRobinCount = roundRobinCount;
	this->previousHitRobinNum = -1;
	this->randomGenerator.setSeed(std::time(0));
}

void HitIterator::trigger(TriggerInformation triggerInfo) {
	this->timeStamp = triggerInfo.timeStamp;

	int version;

	if (this->roundRobinCount > 2) {
		int i;
		for (i = 0; i < 50; i++) {
			int newVersion = randomGenerator.nextInt(this->roundRobinCount);
			if (newVersion != this->previousHitRobinNum) {
				this->previousHitRobinNum = newVersion;
				version = newVersion;
				break;
			}
		}

		if (i == 50) {
			DBG("Random seed generator generated the previous value 50 times. Reseeding");
			this->randomGenerator.setSeed(std::time(0));
			version = randomGenerator.nextInt(this->roundRobinCount);
		}
	}
	else if (roundRobinCount == 2) {
		if (previousHitRobinNum == 0) {
			previousHitRobinNum = 1;
			version = 1;
		}
		else {
			previousHitRobinNum = 0;
			version = 0;
		}
	}
	else {
		version = 0;
	}
	
	
	for (int i = 0; i < micNames.size(); i++) {
		//jassert(it != end);
		String micName = micNames[i];
		AudioSampleBuffer* currBuffer = micMap[micName][version];
		if (currBuffer->getNumChannels() > 0) {			
			//TODO: Uncomment when you got the choke samples and figured out tom1-5 mix up
			//jassert(bleedMap[micName] == false);

			bufferIterators.at(micName).trigger(currBuffer, triggerInfo.noteVelocity*triggerInfo.micGains[micName], micToExtraChannelMap[i]);
		}
		else {
			//TODO: Uncomment when you got the choke samples and figured out tom1-5 mix up
			//jassert(bleedMap[micName] == true);
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
