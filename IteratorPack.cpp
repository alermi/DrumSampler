/*
  ==============================================================================

    IteratorPack.cpp
    Created: 16 Aug 2019 10:22:09pm
    Author:  Ani

  ==============================================================================
*/

#include "IteratorPack.h"

IteratorPack::IteratorPack(AudioSampleBuffer* address, float velocity, int samplesLeft, int channelNum, int timestamp, AudioSampleBuffer *mainBuffer, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues) {
	//this->mainBuffer = mainBuffer;
	this->address = address;
	this->velocity = velocity;
	this->samplesLeft = samplesLeft;
	this->channelNum = channelNum;
	this->sampleLeftAt = 0;
	this->timestamp = timestamp;
	this->hasEnded = false;
	this->monoPanValues = monoPanValues;
	this->stereoPanValues = stereoPanValues;
	//jassert(mainBuffer->getNumChannels() == 2);

}
//
//void IteratorPack::iterate(AudioSampleBuffer output) {
//	jassert(this->hasEnded==false);
//	int samplesToCopy = std::min(samplesLeft, output.getNumSamples() - timestamp);
//	output.addFrom(channelNum, timestamp, *address, 0, sampleLeftAt, samplesToCopy, velocity);
//	//If the iterator has reached the end, update the boolean.
//	if (samplesToCopy == samplesLeft) {
//		hasEnded = true;
//	}
//	//Else update the remaining numbers.
//	else {
//		sampleLeftAt += samplesToCopy;
//		samplesLeft -= samplesToCopy;
//		timestamp = 0;
//	}
//}
void IteratorPack::iterate(std::array<AudioSampleBuffer*,2> outputs) {
	jassert(hasEnded == false);
	//AudioSampleBuffer* output = mainOutput;
	//TODO: jassert if mainbus numsamples == extrabus numsamples
	int samplesToCopy = std::min(samplesLeft, outputs[0]->getNumSamples() - timestamp);
	for (AudioSampleBuffer* output : outputs) {
		jassert(output != NULL);
		jassert(samplesToCopy == std::min(samplesLeft, output->getNumSamples() - timestamp));
		for (int sourceChannel = 0; sourceChannel < address->getNumChannels(); sourceChannel++) {
			for (int destChannel = 0; destChannel < output->getNumChannels(); ++destChannel) {
				float panValue;
				if (output->getNumChannels() == 1) {
					panValue = 1;
				}
				else if (address->getNumChannels() == 1) {
					panValue = monoPanValues[0 + destChannel] * stereoPanValues[0 + destChannel][0 + destChannel]
						+ monoPanValues[1 - destChannel] * stereoPanValues[1 - destChannel][0 + destChannel];
				}
				else {
					jassert(address->getNumChannels() == 2);
					panValue = stereoPanValues[sourceChannel][destChannel];
				}
				output->addFrom(destChannel, timestamp, *address, sourceChannel, sampleLeftAt, samplesToCopy, velocity*panValue);

			}
		}
	}

	if (samplesToCopy == samplesLeft) {
		hasEnded = true;
	}
	//Else update the remaining numbers.
	else {
		sampleLeftAt += samplesToCopy;
		samplesLeft -= samplesToCopy;
		timestamp = 0;
	}
}