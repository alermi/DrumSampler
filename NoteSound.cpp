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


////TODO: Move this into VelocityLevelPlayer?
//void NoteSound::createBuffers() {
//	this->micMap = std::map<String, std::map<String, AudioSampleBuffer*>>();
//
//	vector<String> micNames = MicController::getMicNames();
//	std::map<String, int> micChannelMap = MicController::getMicChannelMap();
//
//	for (int micNumber = 0; micNumber < micNames.size(); micNumber++) {
//		String micName = micNames[micNumber];
//		bool arrayCreated = 0;
//
//
//		//this->micMap.insert({ micName, std::map<String, AudioSampleBuffer*>() });
//		this->micMap[micName] = std::map<String, AudioSampleBuffer*>();
//
//		std::map<String, AudioSampleBuffer*> velocityMicMap = micMap[micName];
//		for (int velocityNumber = 0; velocityNumber < this->noteProperties->velocityCount; velocityNumber++) {
//			String velocityName;
//			//velocityName.append("v", 1);
//			velocityName.append(String(velocityNumber + 1), 1);
//
//			for (int versionNumber = 0; versionNumber < VelocityLevelPlayer::NUM_OF_SAME_SAMPLE; versionNumber++) {
//
//				String version;
//				version.append(String(versionNumber + 1), 1);
//				// TODO: Adjust for real samples
//				//String pathName = fileManager->getSamplesFolder()->getFullPathName() + "\\" + noteProperties->instrumentName + " " + micName + " " + velocityName + " " + version + ".wav";
//				String pathName = fileManager->getSamplesFolder()->getFullPathName() + "\\" + noteProperties->instrumentName + "_" + micName + "_v1_r1" + ".wav";
//				auto buffer = fileManager->readBuffer(pathName);
//
//				// If the file exists, make sure that you get the right amount of channels
//				int wantedChannelNum = micChannelMap[micName];
//				int receivedChanelNum = buffer->getNumChannels();
//				if (receivedChanelNum != 0) {
//					jassert(wantedChannelNum == receivedChanelNum);
//				}
//				String indexString = VelocityLevelPlayer::getBufferMapKey(velocityNumber, versionNumber);
//				micMap[micName][indexString] = buffer;
//			}
//		}
//	}
//}

void NoteSound::triggerSound
( std::map<String, float> micGains, float noteVelocity, int timeStamp, float monoPan, AudioProcessor* processor) {

	//Calculate which hardness level of each sample top play based on velocity of the note and 
	//the number of available velocities.
	int levelNumber = 128 * noteVelocity*float(noteProperties->velocityCount) / 129;
	//TODO: DELETE, TESTING
	if (timeStamp != 0) {
		DBG("Hi");
	}

	float stereoPan[2];
	if (monoPan < 0.5f) {
		stereoPan[0] = 0;
		stereoPan[1] = 2 * monoPan;
	}
	else {
		stereoPan[0] = monoPan - (1 - monoPan);
		stereoPan[1] = 1;
	}



	// TODO: instead of calculating each time, save these values unless changed.
	std::array<float, 2> monoPanValues = { sin((PI / 2) * (1 - monoPan)) ,sin(monoPan*(PI / 2)) };
	vector<std::array<float, 2>> stereoPanValues;
	std::array<float, 2> tempArray1 = { sin((PI / 2) * (1 - stereoPan[0])) ,sin(stereoPan[0] * (PI / 2)) };
	stereoPanValues.push_back(tempArray1);
	std::array<float, 2> tempArray2 = { sin((PI / 2) * (1 - stereoPan[1])) ,sin(stereoPan[1] * (PI / 2)) };
	stereoPanValues.push_back(tempArray2);

	//HitIterator newIterator(this->processor, micMap, micGains, indexString, noteVelocity, timeStamp, monoPanValues, stereoPanValues);
	//HitIterator newIterator(micMap, noteVelocity*micGains[micName], currBuffer->getNumSamples(), timeStamp, monoPanValues, stereoPanValues, micToExtraChannelMap[i]);
	//iterators->push_back(newIterator);

	velocityLevelPlayer.trigger(TriggerInformation(micGains, noteVelocity, timeStamp, monoPanValues, stereoPanValues));
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
	//std::list<HitIterator>::iterator it;
	//std::list<HitIterator>::iterator end;
	//it = iterators->begin();
	//end = iterators->end();

	////Loop through the iterators left from previous blocks and fill the current block
	//while (it != end) {
	//	HitIterator currPack = *it;
	//	it->iterate(output);
	//	if (it->hasEnded()) {
	//		it = iterators->erase(it);
	//	}
	//	else {
	//		it++;
	//	}
	//}

	this->velocityLevelPlayer.processBlock();
	//hitIterator1->iterate(output, false);
	//hitIterator2->iterate(output, false);
}

void NoteSound::setBlockSize(int blockSize)
{
	this->blockSize = blockSize;

	//TODO: Loop through all velocityLevelPlayers in the future.
	velocityLevelPlayer.setBlockSize(blockSize);
}

void NoteSound::killSound(int killTimeStamp)
{
	//std::list<HitIterator>::iterator it;
	//std::list<HitIterator>::iterator end;
	//it = iterators->begin();
	//end = iterators->end();

	////Loop through the iterators left from previous blocks and fill the current block
	//while (it != end) {
	//	// If this comparison was strictly less, there may be issues when both are 0
	//	// This is also checked in the kill function. If this is going to be changed, both must be changed.
	//	it->kill(killTimeStamp);
	//	
	//	it++;
	//}
	this->velocityLevelPlayer.kill(killTimeStamp);
	//hitIterator1->kill(killTimeStamp);
	//hitIterator2->kill(killTimeStamp);

}

NoteSound::~NoteSound() {
	//for (int micNumber = 0; micNumber < MIC_COUNT; micNumber++) {
	//	for (int velocityNumber = 0; velocityNumber < this->noteProperties->velocityCount; velocityNumber++) {
	//		for (int versionNumber = 0; versionNumber < NUM_OF_SAME_SAMPLE; versionNumber++) {
	//			delete micPointers[micNumber][(velocityNumber*NUM_OF_SAME_SAMPLE) + (versionNumber)];
	//		}
	//	}
	//	delete micPointers[micNumber];
	//}
	//delete micPointers;
	//for (auto const& x : micMap)
	//{
	//	for (auto const& y : x.second) {
	//		delete y.second;
	//	}
	//}
}