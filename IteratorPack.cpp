/*
  ==============================================================================

    IteratorPack.cpp
    Created: 16 Aug 2019 10:22:09pm
    Author:  Ani

  ==============================================================================
*/

#include "IteratorPack.h"

IteratorPack::IteratorPack(AudioSampleBuffer* address, float velocity, int samplesLeft, int timestamp, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues, int extraBusNumber) {
	this->address = address;
	this->velocity = velocity;
	// Samples left at the origin buffer to copy
	this->samplesLeft = samplesLeft;
	// Sample that we last left at in the origin buffer
	this->sampleLeftAt = 0;
	this->hasEnded = false;
	this->monoPanValues = monoPanValues;
	this->stereoPanValues = stereoPanValues;
	this->extraBusNumber = extraBusNumber;
	// Sample in current block that we it start writing.
	this->timestamp = timestamp;
	// The sample in current block that it will start ramping down.
	// Has to be less than timestamp + samplesLeft.
	this->killTimeStamp = -1;

}

void IteratorPack::iterate(std::array<AudioSampleBuffer*,2> outputs) {
	jassert(hasEnded == false);
	//AudioSampleBuffer* output = mainOutput;
	int samplesToCopy = getSamplesToCopy(outputs);
	for (AudioSampleBuffer* output : outputs) {
		if (output == NULL) continue;
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

				if (this->killTimeStamp != -1) {
					// TODO: This assertion that the kill time stamp is greater than timestamp will have to change when we are 
					// reusing iteratorpacks.
					jassert(this->killTimeStamp >= timestamp);
					jassert(this->killTimeStamp < timestamp + samplesToCopy);
					output->addFrom(destChannel, timestamp, *address, sourceChannel, sampleLeftAt, this->killTimeStamp - timestamp, velocity*panValue);
					//output->addFromWithRamp(destChannel, killTimeStamp, address->getReadPointer(sourceChannel), SAMPLES_TO_KILL, 1.0f, 0.0f);

				}
				else {
					output->addFrom(destChannel, timestamp, *address, sourceChannel, sampleLeftAt, samplesToCopy, velocity*panValue);
				}

			}
		}
	}
	// TODO: The killTimeStamp condition will not hold when we add the ramp down.
	// we will have to check if it is spilling to the next buffer.
	if (samplesToCopy == samplesLeft || killTimeStamp != -1) {
		hasEnded = true;
	}
	//Else update the remaining numbers.
	else {
		sampleLeftAt += samplesToCopy;
		samplesLeft -= samplesToCopy;
		timestamp = 0;
		//if(killTimeStamp < 0){
		//	killTimeStamp
		//}
	}
}

int IteratorPack::getSamplesToCopy(std::array<AudioSampleBuffer*, 2> outputs) {
	//TODO: jassert if mainbus numsamples == extrabus numsamples
	int samplesToCopy = std::min(samplesLeft, outputs[0]->getNumSamples() - timestamp);
	jassert(samplesToCopy == std::min(samplesLeft, outputs[1]->getNumSamples() - timestamp));
	return samplesToCopy;
}
void IteratorPack::kill(int killTimeStamp)
{
	//TODO: killTimeStamp < timestamp will not work when we are reusing iteratorPacks.
	if (samplesLeft + timestamp <= killTimeStamp || killTimeStamp < timestamp) {
		return;
	}
	this->killTimeStamp = killTimeStamp;
}

