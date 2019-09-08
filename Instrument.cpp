/*
  ==============================================================================

    Instrument.cpp
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/

#include "Instrument.h"
const int NUM_OF_SAME_SAMPLE = 5;
const int HI_HAT_SAMPLE_OFFSET = 32;
const double PI = 3.141592653589793238462643383279502884;

const int micToExtraChannelMap[] = { 2,2,3,3,4,5,6,8, };
const int MIC_COUNT = 12;
const String MIC_NAMES[MIC_COUNT] = { "kick_in", "kick_out", "snare_bottom", "snare_top", "tom1", "tom2", "tom3", "ride", "room_mono", "room_main",
			"room_wide", "overhead" };
Instrument::Instrument(String instrumentName, int velocityCount, FileManager* fileManager, AudioProcessor* processor) {
	this->velocityCount = velocityCount;
	this->instrumentName = instrumentName;
	this->fileManager = fileManager;
	iterators = new list<IteratorPack>();
	this->processor = processor;

}

void Instrument::createBuffers() {
	this->micPointers = ((AudioSampleBuffer***)calloc(MIC_COUNT, sizeof(AudioSampleBuffer**)));

	for (int micNumber = 0; micNumber < MIC_COUNT; micNumber++) {
		String micName = MIC_NAMES[micNumber];
		bool arrayCreated = 0;

		for (int velocityNumber = 0; velocityNumber < this->velocityCount; velocityNumber++) {
			String velocityName;
			//velocityName.append("v", 1);
			velocityName.append(String(velocityNumber + 1), 1);

			for (int versionNumber = 0; versionNumber < NUM_OF_SAME_SAMPLE; versionNumber++) {
				if (micPointers[micNumber] == 0) {
					micPointers[micNumber] = (AudioSampleBuffer**)calloc(NUM_OF_SAME_SAMPLE*this->velocityCount, sizeof(AudioSampleBuffer*));
				}
				String version;
				version.append(String(versionNumber + 1), 1);
				String pathName = fileManager->getSamplesFolder()->getFullPathName() + "\\" + instrumentName + " " + MIC_NAMES[micNumber] + " " + velocityName + " " + version + ".wav";
				micPointers[micNumber][(velocityNumber*NUM_OF_SAME_SAMPLE) + (versionNumber)] = fileManager->readBuffer(pathName);
			}
		}
	}
}

void Instrument::fillBuffer(int velocity, AudioSampleBuffer* bufferToFill) {

}

void Instrument::triggerInstrument
(AudioBuffer<float> *bufferToFill, std::vector<float> micGains, float noteVelocity, int timeStamp, int numOutputChannels, int blockSize, float monoPan, float stereoPan[2], AudioProcessor* processor) {

	//Calculate which hardness level of each sample top play based on velocity of the note and 
	//the number of available velocities.
	int levelNumber = 128 * noteVelocity*float(velocityCount) / 129;
	//Vector to hold the read pointers of each sample to be played.
	std::vector<AudioSampleBuffer*> inVector;
	//vector to hold how many sample from each read pointer is going to be played.
	std::vector<int> sampleCountVector;

	//Randomize which version of the same sample it is going to play
	int version = rand() % NUM_OF_SAME_SAMPLE;

	//Create an iterator to be played for each microphone
	for (int i = 0; i < micGains.size(); i++) {
		AudioSampleBuffer** tempMic = micPointers[i];
		//Find the correct index that holds each sample of each room mic.
		int index = (version + levelNumber * NUM_OF_SAME_SAMPLE);//Place of the sample in array of buffers
		AudioSampleBuffer* sample = tempMic[index];
		if (sample->getNumChannels() > 0) {
			inVector.push_back(sample);
			//Add the number of samples to be played to another vector
			sampleCountVector.push_back(tempMic[index]->getNumSamples());
		}// Push nulls for empty buffers so that the indices dont get messed up
		else {
			inVector.push_back(0);
			sampleCountVector.push_back(NULL);
		}

	}
// TODO: instead of calculating each time, save these values unless changed.
	std::array<float, 2> monoPanValues = { sin((PI / 2) * (1 - monoPan)) ,sin(monoPan*(PI / 2))};
	vector<std::array<float, 2>> stereoPanValues;
	std::array<float, 2> tempArray1 = {  sin((PI / 2) * (1 - stereoPan[0])) ,sin(stereoPan[0] * (PI / 2)) };
	stereoPanValues.push_back(tempArray1);
	std::array<float, 2> tempArray2 = { sin((PI / 2) * (1 - stereoPan[1])) ,sin(stereoPan[1] * (PI / 2)) };
	stereoPanValues.push_back(tempArray2);

	//for (int micNumber = 0; micNumber < 2; micNumber++) {
	//	AudioSampleBuffer* currBuffer = inVector.at(micNumber);
	//	if (currBuffer == 0) {
	//		continue;
	//	}
	//	jassert(currBuffer->getNumChannels() == 1);
	//	for (int sourceChannel = 0; sourceChannel < 1; sourceChannel++) {
	//		for (int destChannel = 0; destChannel < 2; ++destChannel) {
	//			float panValue = monoPanValues[0 + destChannel] * stereoPanValues[0 + destChannel][0 + destChannel]
	//				+ monoPanValues[1 - destChannel] * stereoPanValues[1 - destChannel][0 + destChannel];
	//			IteratorPack newPack(currBuffer, noteVelocity*micGains.at(micNumber)*panValue, sampleCountVector.at(micNumber), destChannel, timeStamp);
	//			iterators->push_back(newPack);
	//		}
	//		// Put iterator for kick channel
	//		IteratorPack newPack(currBuffer, noteVelocity*micGains.at(micNumber), sampleCountVector.at(micNumber), 2, timeStamp);
	//		iterators->push_back(newPack);
	//	}
	//}



	for (int j = 0; j < 9; j++) {
		AudioSampleBuffer* currBuffer = inVector.at(j);
		if (currBuffer == 0) {
			continue;
		}
		jassert(currBuffer->getNumChannels() == 1);
		//TODO: Change this buffertofill based on different output channels
		//AudioSampleBuffer mainBuffer=processor->getBusBuffer(*bufferToFill, false, 0);
		//AudioSampleBuffer *temp= processor->getBusBuffer(bufferToFill,true,0);
		IteratorPack newPack(currBuffer, noteVelocity*micGains.at(j), sampleCountVector.at(j), -1, timeStamp, NULL, monoPanValues, stereoPanValues);
		iterators->push_back(newPack);
		/*for (int sourceChannel = 0; sourceChannel < 1; sourceChannel++) {
			for (int destChannel = 0; destChannel < 2; ++destChannel) {

				float panValue = monoPanValues[0 + destChannel] * stereoPanValues[0 + destChannel][0 + destChannel]
					+ monoPanValues[1 - destChannel] * stereoPanValues[1 - destChannel][0 + destChannel];
				IteratorPack newPack(currBuffer, noteVelocity*micGains.at(j)*panValue, sampleCountVector.at(j), destChannel, timeStamp, NULL, monoPanValues,stereoPanValues);
				iterators->push_back(newPack);
			}
		}*/
	}
	for (int j = 9; j < inVector.size(); j++) {
		AudioSampleBuffer* currBuffer = inVector.at(j);
		if (currBuffer == 0) {
			continue;
		}
		jassert(currBuffer->getNumChannels() == 2);
		IteratorPack newPack(currBuffer, noteVelocity*micGains.at(j), sampleCountVector.at(j), -1, timeStamp, NULL, monoPanValues, stereoPanValues);
		iterators->push_back(newPack);
		/*for (int sourceChannel = 0; sourceChannel < 2; sourceChannel++) {
			for (int destChannel = 0; destChannel < 2; ++destChannel) {
				float panValue = stereoPanValues[sourceChannel][destChannel];
				IteratorPack newPack(currBuffer, noteVelocity*micGains.at(j)*panValue, sampleCountVector.at(j), destChannel, timeStamp, NULL, NULL, NULL);
				iterators->push_back(newPack);
			}
		}*/
	}

}

void Instrument::fillFromIterators(AudioSampleBuffer output) {
	std::list<IteratorPack>::iterator it;
	std::list<IteratorPack>::iterator end;
	it = iterators->begin();
	end = iterators->end();

	//Loop through the iterators left from previous blocks and fill the current block
	while (it != end) {
		IteratorPack currPack = *it;
		std::array<AudioSampleBuffer*, 2> outputs = { &processor->getBusBuffer(output,false,0) ,&processor->getBusBuffer(output,false,1) };
		it->iterate(outputs);
		if (it->hasEnded) {
			it = iterators->erase(it);
		}
		else {
			it++;
		}
	}
}

Instrument::~Instrument() {
	for (int micNumber = 0; micNumber < MIC_COUNT; micNumber++) {
		for (int velocityNumber = 0; velocityNumber < this->velocityCount; velocityNumber++) {
			for (int versionNumber = 0; versionNumber < NUM_OF_SAME_SAMPLE; versionNumber++) {
				delete micPointers[micNumber][(velocityNumber*NUM_OF_SAME_SAMPLE) + (versionNumber)];
			}
		}
		delete micPointers[micNumber];
	}
	delete micPointers;
	delete iterators;
}