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

HitIterator::HitIterator(AudioProcessor* processor, std::map<String, std::map<int, AudioSampleBuffer*>> micMap) {
	this->processor = processor;
	this->micMap = micMap;
	this->bufferIterators = new std::list<BufferIterator>();
	for (int i = 0; i < micNames.size(); i++) {
		BufferIterator newPack;
		bufferIterators->push_back(newPack);
	}
	timeStamp = -1;
}

void HitIterator::trigger(TriggerInformation triggerInfo) {
	//Kill the previous playing sounds
	//kill(timeStamp);
	//Create an iterator to be played for each microphone
	this->timeStamp = triggerInfo.timeStamp;

	std::list<BufferIterator>::iterator it;
	std::list<BufferIterator>::iterator end;
	it = bufferIterators->begin();
	end = bufferIterators->end();

	int version = rand() % NUM_OF_SAME_SAMPLE;

	for (int i = 0; i < micNames.size(); i++) {
		jassert(it != end);
		String micName = micNames[i];
		AudioSampleBuffer* currBuffer = micMap[micName][version];
		if (currBuffer->getNumChannels() > 0) {
			//BufferIterator currPack = bufferIterators[i];

			it->trigger(currBuffer, triggerInfo.noteVelocity*triggerInfo.micGains[micName], triggerInfo.monoPanValues, triggerInfo.stereoPanValues, micToExtraChannelMap[i]);
			//bufferIterators->push_back(newPack);
		}
		it++;
	}
}

bool HitIterator::hasEnded()
{
	bool ended = true;
	for (BufferIterator iterator : *bufferIterators) {
		ended = ended && iterator.hasEnded;
	}
	return ended;
}
void HitIterator::reset()
{
	std::list<BufferIterator>::iterator it;
	std::list<BufferIterator>::iterator end;
	it = bufferIterators->begin();
	end = bufferIterators->end();

	while (it != end) {
		BufferIterator currPack = *it;
		it->reset();
		it++;
	}
	timeStamp = -1;
	
}



void HitIterator::iterate(AudioSampleBuffer output, int startSample, int endSample, bool fadeOut)
{

	std::list<BufferIterator>::iterator it;
	std::list<BufferIterator>::iterator end;
	it = bufferIterators->begin();
	end = bufferIterators->end();

	//Loop through the iterators left from previous blocks and fill the current block
	while (it != end) {
		BufferIterator currPack = *it;


		if (it->hasEnded) {
			//TODO: This reset can be moved right after iterate probably?
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

			it->iterate(outputs, startSample, endSample, fadeOut);
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
