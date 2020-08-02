/*
  ==============================================================================

    NoteSound.cpp
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/

#include "NoteSound.h"

const int HI_HAT_SAMPLE_OFFSET = 32;
const double PI = 3.141592653589793238462643383279502884;
NoteSound::NoteSound(NoteProperties *noteProperties, FileManager* fileManager, AudioProcessor* processor, std::map<String, AudioSampleBuffer*>* micOutputs) : velocityLevelPlayer(processor, fileManager, noteProperties, 2, 0, micOutputs) {
	this->noteProperties = noteProperties;
	this->fileManager = fileManager;
	this->processor = processor;
	//createBuffers();
	//TODO: This duplicate can be removed when the createBuffers is moved within the velocityLevelPlayer;
	//velocityLevelPlayer = VelocityLevelPlayer(processor, fileManager, noteProperties, 2, 0);
	//this->hitIterator1 = new HitIterator(processor, micMap);
	//this->hitIterator2 = new HitIterator(processor, micMap);
}

void NoteSound::triggerSound
(std::map<String, float> micGains, float noteVelocity, int timeStamp, AudioProcessor* processor) {

	//Calculate which hardness level of each sample top play based on velocity of the note and 
	//the number of available velocities.
	int levelNumber = 128 * noteVelocity*float(noteProperties->velocityCount) / 129;
	//TODO: DELETE, TESTING
	if (timeStamp != 0) {
		DBG("Hi");
	}



	//HitIterator newIterator(this->processor, micMap, micGains, indexString, noteVelocity, timeStamp, monoPanValues, stereoPanValues);
	//HitIterator newIterator(micMap, noteVelocity*micGains[micName], currBuffer->getNumSamples(), timeStamp, monoPanValues, stereoPanValues, micToExtraChannelMap[i]);
	//iterators->push_back(newIterator);

	velocityLevelPlayer.trigger(TriggerInformation(micGains, noteVelocity, timeStamp));
	//if (hitIterator1->hasEnded()) {
	//	hitIterator2->kill(timeStamp);
	//	hitIterator1->trigger(micGains, indexString, noteVelocity, timeStamp, monoPanValues, stereoPanValues);
	//}
	//else {
	//	hitIterator1->kill(timeStamp);
	//	jassert(hitIterator2->hasEnded());
	//	hitIterator2->trigger(micGains, indexString, noteVelocity, timeStamp, monoPanValues, stereoPanValues);
	//}
}



void NoteSound::fillFromIterators() {

	//TODO: Loop through all velocityLevelPlayers in the future.
	this->velocityLevelPlayer.processBlock();
}

void NoteSound::setBlockSize(int blockSize)
{
	this->blockSize = blockSize;

	//TODO: Loop through all velocityLevelPlayers in the future.
	velocityLevelPlayer.setBlockSize(blockSize);
}

void NoteSound::killSound(int killTimeStamp)
{

	//TODO: Loop through all velocityLevelPlayers in the future.
	this->velocityLevelPlayer.kill(killTimeStamp);

}

NoteSound::~NoteSound() {

}