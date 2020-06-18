/*
  ==============================================================================

    NoteSound.cpp
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/

#include "NoteSound.h"
#include "MicController.h"
const int NUM_OF_SAME_SAMPLE = 5;
const int HI_HAT_SAMPLE_OFFSET = 32;
const double PI = 3.141592653589793238462643383279502884;
// TODO: Fix the ride mic extra channel map
const int micToExtraChannelMap[] = { 3,3,4,4,5,6,7,1,1,1,1,2 };
const int MIC_COUNT = 12;
const String MIC_NAMES[MIC_COUNT] = { "kickin", "kickout", "snrbot", "snrtop", "tom1", "tom2", "tom3", "ride", "roommono", "roomstereo",
			"roomfar", "oh" };
NoteSound::NoteSound(NoteProperties *noteProperties, FileManager* fileManager, AudioProcessor* processor) {
	//this->velocityCount = velocityCount;
	//this->instrumentName = instrumentName;
	this->noteProperties = noteProperties;
	this->fileManager = fileManager;
	iterators = new list<IteratorPack>();
	this->processor = processor;

}

String NoteSound::getBufferMapKey(int velocityNum, int versionNum)
{
	String indexString = String(velocityNum) + "_" + String(versionNum);
	return indexString;
}

void NoteSound::createBuffers() {
	this->micMap = std::map<String, std::map<String, AudioSampleBuffer*>>();

	vector<String> micNames = MicController::getMicNames();
	std::map<String, int> micChannelMap = MicController::getMicChannelMap();

	for (int micNumber = 0; micNumber < MIC_COUNT; micNumber++) {
		String micName = micNames[micNumber];
		//String micName = MIC_NAMES[micNumber];
		bool arrayCreated = 0;


		//this->micMap.insert({ micName, std::map<String, AudioSampleBuffer*>() });
		this->micMap[micName] = std::map<String, AudioSampleBuffer*>();

		std::map<String, AudioSampleBuffer*> velocityMicMap = micMap[micName];
		for (int velocityNumber = 0; velocityNumber < this->noteProperties->velocityCount; velocityNumber++) {
			String velocityName;
			//velocityName.append("v", 1);
			velocityName.append(String(velocityNumber + 1), 1);

			for (int versionNumber = 0; versionNumber < NUM_OF_SAME_SAMPLE; versionNumber++) {

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
				String indexString = getBufferMapKey(velocityNumber, versionNumber);
				micMap[micName][indexString] = buffer;
			}
		}
	}
}

void NoteSound::triggerSound
( std::vector<float> micGains, float noteVelocity, int timeStamp, float monoPan, float stereoPan[2], AudioProcessor* processor) {

	//Calculate which hardness level of each sample top play based on velocity of the note and 
	//the number of available velocities.
	int levelNumber = 128 * noteVelocity*float(noteProperties->velocityCount) / 129;

	//Randomize which version of the same sample it is going to play
	int version = rand() % NUM_OF_SAME_SAMPLE;

	// TODO: instead of calculating each time, save these values unless changed.
	std::array<float, 2> monoPanValues = { sin((PI / 2) * (1 - monoPan)) ,sin(monoPan*(PI / 2)) };
	vector<std::array<float, 2>> stereoPanValues;
	std::array<float, 2> tempArray1 = { sin((PI / 2) * (1 - stereoPan[0])) ,sin(stereoPan[0] * (PI / 2)) };
	stereoPanValues.push_back(tempArray1);
	std::array<float, 2> tempArray2 = { sin((PI / 2) * (1 - stereoPan[1])) ,sin(stereoPan[1] * (PI / 2)) };
	stereoPanValues.push_back(tempArray2);

	jassert(size(micToExtraChannelMap) >= micGains.size());
	//Create an iterator to be played for each microphone
	for (int i = 0; i < micGains.size(); i++) {
		String micName = MicController::getMicNames()[i];
		String indexString = getBufferMapKey(levelNumber, version);
		AudioSampleBuffer* currBuffer = micMap[micName][indexString];
		if (currBuffer->getNumChannels() > 0) {
			IteratorPack newPack(currBuffer, noteVelocity*micGains.at(i), currBuffer->getNumSamples(), timeStamp, monoPanValues, stereoPanValues, micToExtraChannelMap[i]);
			iterators->push_back(newPack);
		}
	}
}

void NoteSound::fillFromIterators(AudioSampleBuffer output) {
	std::list<IteratorPack>::iterator it;
	std::list<IteratorPack>::iterator end;
	it = iterators->begin();
	end = iterators->end();

	//Loop through the iterators left from previous blocks and fill the current block
	while (it != end) {
		IteratorPack currPack = *it;
		jassert(processor->getBus(false, 0)->isEnabled());
		//jassert(processor->getBus(false, currPack.extraBusNumber)->isEnabled());

		AudioSampleBuffer mainBuffer = processor->getBusBuffer(output, false, 0);
		AudioSampleBuffer extraBuffer = processor->getBusBuffer(output, false, currPack.extraBusNumber);
		std::array<AudioSampleBuffer*, 2> outputs = { &mainBuffer ,&extraBuffer };
		it->iterate(outputs);
		if (it->hasEnded) {
			it = iterators->erase(it);
		}
		else {
			it++;
		}
	}
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
	for (auto const& x : micMap)
	{
		for (auto const& y : x.second) {
			delete y.second;
		}
	}
	delete iterators;
}