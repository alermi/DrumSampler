/*
  ==============================================================================

    NoteSound.cpp
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/

#include "NoteSound.h"

NoteSound::NoteSound(NoteProperties *noteProperties, FileManager* fileManager, AudioProcessor* processor, std::map<String, AudioSampleBuffer*>* micOutputs) : velocityLevelPlayer(processor, fileManager, noteProperties, 2, 0, micOutputs) {
	this->noteProperties = noteProperties;
	this->fileManager = fileManager;
	this->processor = processor;
}

void NoteSound::triggerSound
(std::map<String, float> micGains, float noteVelocity, int timeStamp, AudioProcessor* processor) {

	//Calculate which hardness level of each sample top play based on velocity of the note and 
	//the number of available velocities.
	int levelNumber = 128 * noteVelocity*float(noteProperties->velocityCount) / 129;

	velocityLevelPlayer.trigger(TriggerInformation(micGains, noteVelocity, timeStamp));

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