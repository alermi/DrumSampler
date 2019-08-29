/*
  ==============================================================================

    Instrument.cpp
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/

#include "Instrument.h"
const int KICK_MIC_COUNT = 2;
const int KICK_VELOCITY_COUNT = 3;
const int SNARE_MIC_COUNT = 3;
const int SNARE_RIM_MIC_COUNT = 3;
const int SNARE_VELOCITY_COUNT = 4;
const int SNARE_RIM_VELOCITY_COUNT = 1;
const int FLOOR_TOM_MIC_COUNT = 2;
const int FLOOR_TOM_VELOCITY_COUNT = 3;
const int HI_HAT_CLOSED_MIC_COUNT = 2;
const int HI_HAT_CLOSED_VELOCITY_COUNT = 3;
const int HI_HAT_OPEN_MIC_COUNT = 2;
const int HI_HAT_OPEN_VELOCITY_COUNT = 2;
const int RACK_TOM_MIC_COUNT = 2;
const int RACK_TOM_VELOCITY_COUNT = 3;
const int CRASH_ALT_MIC_COUNT = 1;
const int CRASH_ALT_VELOCITY_COUNT = 1;
const int CHINA_MIC_COUNT = 1;
const int CHINA_VELOCITY_COUNT = 1;
const int CRASH_MAIN_MIC_COUNT = 1;
const int CRASH_MAIN_VELOCITY_COUNT = 2;
const int RIDE_MIC_COUNT = 1;
const int RIDE_VELOCITY_COUNT = 2;
const int STACK_MIC_COUNT = 1;
const int STACK_VELOCITY_COUNT = 1;

const int MAX_MIC_COUNT = 3;
const int MAX_VELOCITY_COUNT = 4;
const int NUM_OF_SAME_SAMPLE = 5;

const int HI_HAT_SAMPLE_OFFSET = 32;



const int MIC_COUNT = 12;
const String MIC_NAMES[MIC_COUNT] = { "kick_in", "kick_out", "snare_bottom", "snare_top", "tom1", "tom2", "tom3", "ride", "overhead", "room_main",
			"room_mono", "room_wide"};
Instrument::Instrument(String instrumentName, int velocityCount, AudioFormatManager* formatManager, SampleManager* sampleManager, list<IteratorPack>* iterators) {
	this->velocityCount = velocityCount;
	this->instrumentName = instrumentName;
	//TODO: remove processor and just pass in the format manager
	this->formatManager = formatManager;
	this->sampleManager = sampleManager;
	this->iterators = iterators;


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

				std::unique_ptr<AudioFormatReaderSource> readerSource;
				File newFile(String(sampleManager->getSamplesFolder()->getFullPathName() + "\\" + instrumentName + " " + MIC_NAMES[micNumber] + " " + velocityName + " " + version + ".wav"));

				if (newFile.existsAsFile()) {
					std::unique_ptr<AudioFormatReader> reader(this->formatManager->createReaderFor(newFile));
					AudioSampleBuffer *newBuffer = new AudioSampleBuffer(1, reader->lengthInSamples);
					reader->read(newBuffer, 0, reader->lengthInSamples, 0, true, false);
					Range<float> range = newBuffer->findMinMax(0, 0, reader->lengthInSamples);
					float max = std::max(abs(range.getStart()), abs(range.getEnd()));
					newBuffer->applyGain(1 / max);
					newBuffer->applyGainRamp(0, 10, 0, 1);
					//TODO:Delete testint
					//int index = (version + levelNumber * NUM_OF_SAME_SAMPLE);//Place of the sample in array of buffers

					int testint = (velocityNumber*NUM_OF_SAME_SAMPLE) + (versionNumber);
					micPointers[micNumber][(velocityNumber*NUM_OF_SAME_SAMPLE) + (versionNumber)] = newBuffer;
				}
				else {
/*					//TODO: Find out what this block was doing and fix
					if (velocityNumber == 0 && versionNumber == 0) {
						delete this->micPointers[micNumber];
						this->micPointers[micNumber] = 0;
						break;
					}
					else {*/
						micPointers[micNumber][(velocityNumber*NUM_OF_SAME_SAMPLE) + (versionNumber)] = new AudioSampleBuffer();
					/*}*/
				}
				//if (micPointers[micNumber] == 0) break;
			}
			//if (micPointers[micNumber] == 0) break;
		}
	}
}

void Instrument::fillBuffer(int velocity, AudioSampleBuffer* bufferToFill) {

}

void Instrument::triggerInstrument
(AudioBuffer<float> *bufferToFill, AudioSampleBuffer*** instrumentSamples, std::vector<float> micGains, int numLevels, float noteVelocity, int timeStamp, int numOutputChannels, int blockSize) {

	//TODO:Mix in the room sound and other mics
	// Change 5
	//AudioSampleBuffer *newArray = instrumentSamples[5];

	//Calculate which hardness level of each sample top play based on velocity of the note and 
	//the number of available velocities.
	int levelNumber = 128 * noteVelocity*float(numLevels) / 129;
	//Vector to hold the read pointers of each sample to be played.
	std::vector<const float*> inVector;
	//vector to hold how many sample from each read pointer is going to be played.
	std::vector<int> sampleCountVector;

	//Randomize which version of the same sample it is going to play
	int version = rand() % NUM_OF_SAME_SAMPLE;

	//Create an iterator to be played for each microphone
	for (int i = 0; i < micGains.size(); i++) {
		AudioSampleBuffer** tempMic = instrumentSamples[i];
		//Find the correct index that holds each sample of each room mic.
		int index = (version + levelNumber * NUM_OF_SAME_SAMPLE);//Place of the sample in array of buffers
		//TODO: Fix this hacky fix
		AudioSampleBuffer* sample = tempMic[index];
		if (sample->getNumChannels() > 0) {
			inVector.push_back(sample->getReadPointer(0));
			//Add the number of samples to be played to another vector
			sampleCountVector.push_back(tempMic[index]->getNumSamples());
		}// Push nulls for empty buffers so that the indices dont get messed up
		else {
			inVector.push_back(0);
			sampleCountVector.push_back(NULL);
		}

	}
	//auto in = newArray[5]->getReadPointer(0);
	//int sampleNum = newArray->getNumSamples();

	int i = 0;
	//TODO:Set Stereo gain levels
	//Write the samples to the output buffer and store the remaining in iteratorPack.
	for (int channel = 0; channel < 3; ++channel) {
		float *out = bufferToFill->getWritePointer(channel);

		for (int j = 0; j < inVector.size(); j++) {
			if (inVector.at(j) == 0 ) {
				continue;
			}
			for (i = 0; ((i < sampleCountVector.at(j)) && (i < blockSize - timeStamp)); i++) {

				out[timeStamp + i] += (inVector.at(j)[i] * noteVelocity*micGains.at(j));
			}
			if ((i + timeStamp >= blockSize)) {
				//TODO: Fix the boolean of if this is a hi hat open
				//IteratorPack newPack(((float*)(inVector.at(j) + i)), noteVelocity*micGains.at(j), sampleCountVector.at(j) - i, (instrumentSamples == hi_hat_openSampleBuffers));
				IteratorPack newPack(((float*)(inVector.at(j) + i)), noteVelocity*micGains.at(j), sampleCountVector.at(j) - i, (false), channel);
				iterators->push_back(newPack);
			}
		}

	}
	// TODO: Fix the hi-hat close that broke at refactoring
	//If we triggered a closed hi-hat, mute open hi_hat hits.
	//if (instrumentSamples == hi_hat_closedSampleBuffers) {
	//	for (IteratorPack &currPack : *iterators) {
	//		if (currPack.isHiHatOpen) {
	//			currPack.samplesLeft = timeStamp + HI_HAT_SAMPLE_OFFSET;
	//		}
	//	}
	//}


}
