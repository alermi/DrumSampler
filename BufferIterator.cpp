/*
  ==============================================================================

    BufferIterator.cpp
    Created: 16 Aug 2019 10:22:09pm
    Author:  Ani

  ==============================================================================
*/

#include "BufferIterator.h"

BufferIterator::BufferIterator() {
	this->sample = nullptr;
	this->extraBusNumber = -1;
	this->velocity = -1;
	// Samples left at the origin buffer to copy
	this->samplesLeft = -1;
	// Sample that we last left at in the origin buffer
	this->sampleLeftAt = -1;
	this->hasEnded = true;
}

BufferIterator::~BufferIterator()
{
	//return;
	//delete sample;
}

void BufferIterator::trigger(AudioSampleBuffer* sample, float velocity, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues, int extraBusNumber) {
	this->sample = sample;
	this->extraBusNumber = extraBusNumber;
	jassert(hasEnded == true);
	this->velocity = velocity;
	// Samples left at the origin buffer to copy
	this->samplesLeft = sample->getNumSamples();
	// Sample that we last left at in the origin buffer
	this->sampleLeftAt = 0;
	this->hasEnded = false;
	this->monoPanValues = monoPanValues;
	this->stereoPanValues = stereoPanValues;
}

void BufferIterator::reset() {
	this->sample = nullptr;
	this->extraBusNumber = -1;
	this->velocity = -1;
	// Samples left at the origin buffer to copy
	this->samplesLeft = -1;
	// Sample that we last left at in the origin buffer
	this->sampleLeftAt = -1;
	hasEnded = true;
	//jassert(hasEnded == true);
	//this->monoPanValues = std::vector<>;
	//this->stereoPanValues = NULL;
}
void BufferIterator::iterate(AudioSampleBuffer* output, int startSample, int endSample, bool fadeOut) {
	jassert(extraBusNumber != -1);
	jassert(velocity != -1);
	jassert(sampleLeftAt != -1);
	jassert(samplesLeft != -1);
	jassert(hasEnded == false);

	int samplesToCopy = getSamplesToCopy(startSample, endSample);
	//for (AudioSampleBuffer* output : outputs) {
		//if (output == NULL) continue;
		for (int sourceChannel = 0; sourceChannel < sample->getNumChannels(); sourceChannel++) {
			for (int destChannel = 0; destChannel < output->getNumChannels(); ++destChannel) {
				float panValue;
				if (output->getNumChannels() == 1) {
					panValue = 1;
				}
				else if (sample->getNumChannels() == 1) {
					panValue = monoPanValues[0 + destChannel] * stereoPanValues[0 + destChannel][0 + destChannel]
						+ monoPanValues[1 - destChannel] * stereoPanValues[1 - destChannel][0 + destChannel];
				}
				else {
					jassert(sample->getNumChannels() == 2);
					panValue = stereoPanValues[sourceChannel][destChannel];
				}

				if (fadeOut) {
					output->addFromWithRamp(destChannel, startSample, sample->getReadPointer(sourceChannel) + sampleLeftAt, samplesToCopy, velocity*panValue, 0.0f);
				}
				else {
					output->addFrom(destChannel, startSample, *sample, sourceChannel, sampleLeftAt, samplesToCopy, velocity*panValue);
				}
				//}

			}
		}
	//}
	// TODO: The killTimeStamp condition will not hold when we add the ramp down.
	// we will have to check if it is spilling to the next buffer.
	if (samplesToCopy == samplesLeft) {
		hasEnded = true;
	}
	//Else update the remaining numbers.
	else {
		sampleLeftAt += samplesToCopy;
		samplesLeft -= samplesToCopy;
		//if(killTimeStamp < 0){
		//	killTimeStamp
		//}
	}
}

int BufferIterator::getSamplesToCopy(int startSample, int endSample) {
	//TODO: jassert if mainbus numsamples == extrabus numsamples
	jassert(endSample > startSample);
	int samplesToCopy = std::min(samplesLeft, endSample - startSample);
	//jassert(samplesToCopy == std::min(samplesLeft, outputs[1]->getNumSamples() - startSample));
	return samplesToCopy;
}

