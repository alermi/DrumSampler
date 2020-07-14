/*
  ==============================================================================

    VelocityLevelPlayer.cpp
    Created: 5 Jul 2020 1:07:58am
    Author:  Ani

  ==============================================================================
*/

#include "VelocityLevelPlayer.h"

VelocityLevelPlayer::VelocityLevelPlayer(AudioProcessor * processor, FileManager* fileManager, NoteProperties* noteProperties, int numHitIterators, int levelNum, std::map<String, AudioSampleBuffer*>* micOutputs)
  {
	this->processor = processor;
	this->blockSize = blockSize;
	//this->micMap = micMap;
	this->levelNum = levelNum;
	this->newTriggers.reserve(MAX_NUM_TRIGGERS_IN_BLOCK_PER_VELOCITY_LEVEL);
	this->newKills.reserve(MAX_NUM_KILLS_IN_BLOCK_PER_VELOCITY_LEVEL);
	this->stopPoints.reserve(MAX_NUM_TRIGGERS_IN_BLOCK_PER_VELOCITY_LEVEL + MAX_NUM_KILLS_IN_BLOCK_PER_VELOCITY_LEVEL);

	createBuffers(fileManager, noteProperties);
	for (int i = 0; i < numHitIterators; i++) {
		this->hitIterators.push_back(HitIterator(processor, micMap, micOutputs));
	}
  }

void VelocityLevelPlayer::trigger(TriggerInformation triggerInfo) {


	//TODO: Make sure there isnt already a trigger for the same timestamp value

	if (newTriggers.size() < MAX_NUM_TRIGGERS_IN_BLOCK_PER_VELOCITY_LEVEL) {
		newTriggers.push_back(triggerInfo);
	}
	else {
		jassertfalse;
	}
	//if (hitIterators.at(0).hasEnded()) {
	//	hitIterators.at(0).trigger(triggerInfo);
	//}
	//else {
	//	jassert(hitIterators.at(1).hasEnded());
	//	hitIterators.at(1).trigger(triggerInfo);
	//}

}
void VelocityLevelPlayer::kill(int timeStamp)
{
	if (newKills.size() < MAX_NUM_KILLS_IN_BLOCK_PER_VELOCITY_LEVEL) {
		newKills.push_back(timeStamp);
	}
	else {
		jassertfalse;
	}
}
void VelocityLevelPlayer::processBlock()
{
	for (TriggerInformation newTriggerInfo : newTriggers) {
		if (stopPoints.size() < MAX_NUM_TRIGGERS_IN_BLOCK_PER_VELOCITY_LEVEL + MAX_NUM_KILLS_IN_BLOCK_PER_VELOCITY_LEVEL) {
			if (std::find(stopPoints.begin(), stopPoints.end(), newTriggerInfo.timeStamp) == stopPoints.end())
			{
				stopPoints.push_back(newTriggerInfo.timeStamp);
			}
			else {
				// The stop point is already in the vector.
				jassertfalse;
			}
		}
		else {
			// The stopPoints vector has reached maximum size
			jassertfalse;
		}
	}
	for (int newKill : newKills) {
		if (stopPoints.size() < MAX_NUM_TRIGGERS_IN_BLOCK_PER_VELOCITY_LEVEL + MAX_NUM_KILLS_IN_BLOCK_PER_VELOCITY_LEVEL) {
			if (std::find(stopPoints.begin(), stopPoints.end(), newKill) == stopPoints.end())
			{
				stopPoints.push_back(newKill);
			}
			else {
				// The stop point is already in the vector.
				jassertfalse;
			}
		}
		else {
			// The stopPoints vector has reached maximum size
			jassertfalse;
		}
	}
	std::sort(newKills.begin(), newKills.end());
	std::sort(stopPoints.begin(), stopPoints.end());
	std::sort(newTriggers.begin(), newTriggers.end(), TriggerInformation::compare);

	// No new triggers or kills
	//if (stopPoints.size() == 0) {
		std::vector<HitIterator>::iterator it;
		std::vector<HitIterator>::iterator end;
		it = hitIterators.begin();
		end = hitIterators.end();

		//Loop through the iterators left from previous blocks and fill the current block
		while (it != end) {
			// Iterate wether or not it has ended.
			// TODO: Check if this actually does not cause problems
			it->iterate(0, this->blockSize, false);
			it++;
		}
	//}
	if (newTriggers.size() == 1) {
		//TODO: Mute earlier active iterators
		HitIterator* newHitIterator = findAvailableHitIterator();
		if (newHitIterator != nullptr) {
			newHitIterator->trigger(newTriggers.at(0));
			newHitIterator->iterate(newTriggers.at(0).timeStamp, this->blockSize, false);

			newTriggers.erase(newTriggers.begin());
		}
	}


	//TODO: REMOVE, DEVELOPING
	newKills.clear();
	newTriggers.clear();
	stopPoints.clear();

	jassert(newKills.size() == 0);
	jassert(newTriggers.size() == 0);
	jassert(stopPoints.size() == 0);

	//hitIterators.at(0).iterate(output, false);
	//hitIterators.at(1).iterate(output, false);

}

void VelocityLevelPlayer::setBlockSize(int blockSize)
{
	this->blockSize = blockSize;
}

HitIterator* VelocityLevelPlayer::findAvailableHitIterator() {

	std::vector<HitIterator>::iterator it;
	std::vector<HitIterator>::iterator end;
	it = hitIterators.begin();
	end = hitIterators.end();

	//Loop through the iterators left from previous blocks and fill the current block
	while (it != end) {
		if (it->hasEnded()) {
			jassert(it->timeStamp == -1);
			return &*it;
		}
		it++;
	}
	jassertfalse;
	//TODO: Change this into a more error friendly option
	return nullptr;
}


void VelocityLevelPlayer::createBuffers(FileManager* fileManager, NoteProperties* noteProperties) {

	this->micMap = std::map<String, std::map<int, AudioSampleBuffer*>>();

	std::vector<String> micNames = MicController::getMicNames();
	std::map<String, int> micChannelMap = MicController::getMicChannelMap();

	for (int micNumber = 0; micNumber < micNames.size(); micNumber++) {
		String micName = micNames[micNumber];
		bool arrayCreated = 0;


		//this->micMap[micName] = std::map<String, AudioSampleBuffer*>();

		std::map<int, AudioSampleBuffer*> velocityMicMap = micMap[micName];
		//for (int velocityNumber = 0; velocityNumber < this->noteProperties->velocityCount; velocityNumber++) {

			String velocityName;
			//velocityName.append("v", 1);
			velocityName.append(String(levelNum + 1), 1);

			for (int versionNumber = 0; versionNumber < HitIterator::NUM_OF_SAME_SAMPLE; versionNumber++) {

				String version;
				version.append(String(versionNumber + 1), 1);
				// TODO: Adjust for real samples
				//String pathName = fileManager->getSamplesFolder()->getFullPathName() + "\\" + noteProperties->instrumentName + " " + micName + " " + velocityName + " " + version + ".wav";
				String pathName = fileManager->getSamplesFolder()->getFullPathName() + "\\" + noteProperties->instrumentName + "_" + micName + "_v1_r1" + ".wav";
				auto buffer = fileManager->readBuffer(pathName);

				// If the file exists, make sure that you get the right amount of channels
				int wantedChannelNum = micChannelMap[micName];
				int receivedChanelNum = buffer->getNumChannels();
				if (receivedChanelNum != 0) {
					jassert(wantedChannelNum == receivedChanelNum);
				}
				micMap[micName][versionNumber] = buffer;
			}
		//}
	}
}