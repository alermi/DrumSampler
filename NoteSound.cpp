/*
  ==============================================================================

    NoteSound.cpp
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/

#include "NoteSound.h"

NoteSound::NoteSound(NoteProperties *noteProperties, FileManager* fileManager, AudioProcessor* processor, std::map<String, AudioSampleBuffer*>* micOutputs, std::map<String, bool> bleedMap, int velocityCount, int roundRobinCount) {
	this->noteProperties = noteProperties;
	this->fileManager = fileManager;
	this->processor = processor;
	this->roundRobinCount = roundRobinCount;

	for (int i = 0; i < velocityCount; i++) {
		//velocityLevelPlayers.insert({ processor, fileManager, noteProperties, i, micOutputs, bleedMap });
		//VelocityLevelPlayer newPlayer{ processor, fileManager, noteProperties, i, micOutputs, bleedMap };
		velocityLevelPlayers.push_back(new VelocityLevelPlayer(processor, fileManager, noteProperties, i, micOutputs, bleedMap, roundRobinCount));
	}
}

void NoteSound::triggerSound
(std::map<String, float> micGains, float noteVelocity, int timeStamp) {

	//Calculate which hardness level of each sample top play based on velocity of the note and 
	//the number of available velocities.
	int levelNumber = int(128 * noteVelocity*float(noteProperties->velocityCount) / 129);
	jassert(levelNumber < velocityLevelPlayers.size());
	float modifiedVelocity = pow(0.55f, -noteVelocity) - 0.83f;
	velocityLevelPlayers.at(levelNumber)->trigger(TriggerInformation(micGains, modifiedVelocity, timeStamp));

}



void NoteSound::fillFromIterators(bool isMutingBleeds) {

	for (int i = 0; i < this->velocityLevelPlayers.size(); i++) {
		this->velocityLevelPlayers.at(i)->processBlock(isMutingBleeds);
	}	
}

void NoteSound::setBlockSize(int newBlockSize)
{
	this->blockSize = newBlockSize;

	//TODO: Loop through all velocityLevelPlayers in the future.
	for (int i = 0; i < this->velocityLevelPlayers.size(); i++) {
		this->velocityLevelPlayers.at(i)->setBlockSize(newBlockSize);
	}
}

void NoteSound::killSound(int killTimeStamp)
{

	//TODO: Loop through all velocityLevelPlayers in the future.
	for (int i = 0; i < this->velocityLevelPlayers.size(); i++) {
		this->velocityLevelPlayers.at(i)->kill(killTimeStamp);
	}
}

NoteSound::~NoteSound() {
	for (int i = 0; i < this->velocityLevelPlayers.size(); i++) {
		delete this->velocityLevelPlayers.at(i);
	}
}