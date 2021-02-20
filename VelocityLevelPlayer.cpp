/*
  ==============================================================================

    VelocityLevelPlayer.cpp
    Created: 5 Jul 2020 1:07:58am
    Author:  Ani

  ==============================================================================
*/

#include "VelocityLevelPlayer.h"

VelocityLevelPlayer::VelocityLevelPlayer(AudioProcessor * processor, FileManager* fileManager, NoteProperties* noteProperties, int levelNum, std::map<String, AudioSampleBuffer*>* micOutputs, std::map<String, bool> bleedMap, int roundRobinCount)
  {
	this->processor = processor;
	//this->blockSize = blockSize;
	//this->micMap = micMap;
	this->levelNum = levelNum;
	this->newTriggers.reserve(MAX_NUM_TRIGGERS_IN_BLOCK_PER_VELOCITY_LEVEL);
	this->newKills.reserve(MAX_NUM_KILLS_IN_BLOCK_PER_VELOCITY_LEVEL);
	this->stopPoints.reserve(MAX_NUM_TRIGGERS_IN_BLOCK_PER_VELOCITY_LEVEL + MAX_NUM_KILLS_IN_BLOCK_PER_VELOCITY_LEVEL);
	this -> roundRobinCount = roundRobinCount;
	createBuffers(fileManager, noteProperties);
	//for (int i = 0; i < numHitIterators; i++) {
	//	this->hitIterators.push_back(HitIterator(processor, micMap, micOutputs));
	//}
	blockEvents.clear();

	hitIterator = std::make_unique<HitIterator>(processor, micMap, micOutputs, bleedMap, roundRobinCount);
}

void VelocityLevelPlayer::trigger(TriggerInformation triggerInfo) {

	blockEvents.processEvent(triggerInfo);
}
void VelocityLevelPlayer::kill(int timeStamp)
{
	blockEvents.processEvent(KillInformation(timeStamp));
}
void VelocityLevelPlayer::processBlock(bool isMutingBleeds)
{

	blockEvents.finishReceivingHits();

	int copyUntil= 0;
	int sampleAt = 0;

	while (copyUntil < blockSize) {
		if (blockEvents.hasMoreEvents()) {
			copyUntil = blockEvents.peekAtNextEventTimeStamp();
			jassert(copyUntil < blockSize);
		}
		else {
			copyUntil = blockSize;
		}
  		bool hasEnded = hitIterator->hasEnded();

		if (!hasEnded && (sampleAt < copyUntil)) {
			hitIterator->iterate(sampleAt, copyUntil, false);
		}
		sampleAt = copyUntil;
		
		if (blockEvents.hasMoreEvents()) {
			EventInformation nextEvent = blockEvents.getNextEvent();

			//currSample = nextEvent.timeStamp;
			if (!hitIterator->hasEnded()) {
				hitIterator->iterate(nextEvent.timeStamp, nextEvent.timeStamp + FADE_OUT_SAMPLES, true);
				jassert(hitIterator->hasEnded());
				hitIterator->reset();
			}

			if (nextEvent.isNoteOn) {
				TriggerInformation *triggerInfo = (TriggerInformation*)&nextEvent;
				hitIterator->trigger(*triggerInfo, isMutingBleeds);
			}
		}
	}

	blockEvents.startReceivingHits();

}

void VelocityLevelPlayer::setBlockSize(int newBlockSize)
{
	this->blockSize = newBlockSize;
	blockEvents.clear();
	this->blockEvents.setBlockSize(newBlockSize);
	//this->blockEvents.startReceivingHits();
}


void VelocityLevelPlayer::createBuffers(FileManager* fileManager, NoteProperties* noteProperties) {

	this->micMap = std::map<String, std::map<int, AudioSampleBuffer*>>();

	std::vector<String> micNames = MicController::getMicNames();
	std::map<String, int> micChannelMap = MicController::getMicChannelCountMap();

	for (int micNumber = 0; micNumber < micNames.size(); micNumber++) {
		String micName = micNames[micNumber];
		//bool arrayCreated = 0;


		//this->micMap[micName] = std::map<String, AudioSampleBuffer*>();

		std::map<int, AudioSampleBuffer*> velocityMicMap = micMap[micName];
		//for (int velocityNumber = 0; velocityNumber < this->noteProperties->velocityCount; velocityNumber++) {

			String velocityName;
			//velocityName.append("v", 1);
			velocityName.append(String(levelNum + 1), 1);

			for (int versionNumber = 0; versionNumber < this->roundRobinCount; versionNumber++) {

				String version;
				version.append(String(versionNumber + 1), 1);
				// TODO: Adjust for real samples
				//String pathName = fileManager->getSamplesFolder()->getFullPathName() + "\\" + noteProperties->instrumentName + " " + micName + " " + velocityName + " " + version + ".wav";
				//String pathName = fileManager->getSamplesFolder()->getFullPathName() + "\\" + noteProperties->instrumentName + "_" + micName + "_v" + velocityName + "_r1" + ".wav";
				
				String pathName = fileManager->getSamplesFolder()->getFullPathName() + "\\" + noteProperties->instrumentName + "_" + micName + "_v" + velocityName + "_r" + version + ".wav";
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

VelocityLevelPlayer::~VelocityLevelPlayer()
{

	//TODO: Figure out why the free works well here but not when freeing the samples of BufferIterators.
	//delete hitIterator;
	std::vector<String> micNames = MicController::getMicNames();
	auto it = micMap.begin();
	auto end = micMap.end();

	while (it != end) {

		for (int versionNumber = 0; versionNumber < this->roundRobinCount; versionNumber++) {

			delete it->second[versionNumber];

		}
		it++;
		//}
	}
}
