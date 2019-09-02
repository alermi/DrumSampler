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
const double PI = 3.141592653589793238462643383279502884;


const int MIC_COUNT = 12;
const String MIC_NAMES[MIC_COUNT] = { "kick_in", "kick_out", "snare_bottom", "snare_top", "tom1", "tom2", "tom3", "ride", "room_mono", "room_main",
			"room_wide", "overhead" };
Instrument::Instrument(String instrumentName, int velocityCount, AudioFormatManager* formatManager, SampleManager* sampleManager) {
	this->velocityCount = velocityCount;
	this->instrumentName = instrumentName;
	//TODO: remove processor and just pass in the format manager
	this->formatManager = formatManager;
	this->sampleManager = sampleManager;
	iterators = new list<IteratorPack>();


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
					AudioSampleBuffer *newBuffer = new AudioSampleBuffer(reader->numChannels, reader->lengthInSamples);
					reader->read(newBuffer, 0, reader->lengthInSamples, 0, true, true);

					//TODO: Normalize again
					Range<float> range1 = newBuffer->findMinMax(0, 0, reader->lengthInSamples);
					float max1 = std::max(abs(range1.getStart()), abs(range1.getEnd()));
					newBuffer->applyGain(0, 0, newBuffer->getNumSamples(), 1 / max1);
					newBuffer->applyGainRamp(0, 0, 10, 0, 1);

					if (newBuffer->getNumChannels() == 2) {
						Range<float> range2 = newBuffer->findMinMax(1, 0, reader->lengthInSamples);
						float max2 = std::max(abs(range2.getStart()), abs(range2.getEnd()));
						newBuffer->applyGain(1, 0, newBuffer->getNumSamples(), 1 / max2);
						newBuffer->applyGainRamp(1, 0, 10, 0, 1);
					}
					//else {
					//	max = max1;
					//}
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
(AudioBuffer<float> *bufferToFill, AudioSampleBuffer*** instrumentSamples, std::vector<float> micGains, int numLevels, float noteVelocity, int timeStamp, int numOutputChannels, int blockSize, float monoPan, float stereoPan[2]) {
	//float monoPan = 0.1;
	//float stereoPan[2] = { 0.1,0.9 };

	//TODO:Mix in the room sound and other mics
	// Change 5
	//AudioSampleBuffer *newArray = instrumentSamples[5];

	//Calculate which hardness level of each sample top play based on velocity of the note and 
	//the number of available velocities.
	int levelNumber = 128 * noteVelocity*float(numLevels) / 129;
	//Vector to hold the read pointers of each sample to be played.
	std::vector<AudioSampleBuffer*> inVector;
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
			inVector.push_back(sample);
			//Add the number of samples to be played to another vector
			sampleCountVector.push_back(tempMic[index]->getNumSamples());
		}// Push nulls for empty buffers so that the indices dont get messed up
		else {
			inVector.push_back(0);
			sampleCountVector.push_back(NULL);
		}

	}

	//TODO: Fix the boolean of if this is a hi hat open

	//TODO:Set Stereo gain levels
	//Write the samples to the output buffer and store the remaining in iteratorPack.

	//vector<float> pans = { float(0.5) , float(0.5) };
	//vector<std::array<float, 2>> panValues;
	//for (int i = 0; i < size(pans); i++) {
	//	float pan = pans.at(i);
	//	std::array<float, 2> tempPanArray = { sin(pan*(PI / 2)) ,sin((PI / 2) * (1 - pan)) };
	//	panValues.push_back(tempPanArray);
	//}

	std::array<float, 2> monoPanValues = { sin(monoPan*(PI / 2)) ,sin((PI / 2) * (1 - monoPan)) };
	vector<std::array<float, 2>> stereoPanValues;
	std::array<float, 2> tempArray1 = { sin(stereoPan[0] * (PI / 2)) ,sin((PI / 2) * (1 - stereoPan[0])) };
	stereoPanValues.push_back(tempArray1);
	std::array<float, 2> tempArray2 = { sin(stereoPan[1] * (PI / 2)), sin((PI / 2) * (1 - stereoPan[1])) };
	stereoPanValues.push_back(tempArray2);


	for (int j = 0; j < 9; j++) {
		AudioSampleBuffer* currBuffer = inVector.at(j);
		if (currBuffer == 0) {
			continue;
		}
		jassert(currBuffer->getNumChannels() == 1);
		for (int sourceChannel = 0; sourceChannel < 1; sourceChannel++) {
			for (int destChannel = 0; destChannel < 2; ++destChannel) {

				float panValue = monoPanValues[0 + destChannel] * stereoPanValues[0 + destChannel][0 + destChannel]
					+ monoPanValues[1 - destChannel] * stereoPanValues[1 - destChannel][0 + destChannel];
				IteratorPack newPack(currBuffer, noteVelocity*micGains.at(j)*panValue, sampleCountVector.at(j), (false), destChannel, timeStamp);
				iterators->push_back(newPack);
			}
		}
	}
	for (int j = 9; j < inVector.size(); j++) {
		AudioSampleBuffer* currBuffer = inVector.at(j);
		if (currBuffer == 0) {
			continue;
		}
		jassert(currBuffer->getNumChannels() == 2);
		for (int sourceChannel = 0; sourceChannel < 2; sourceChannel++) {
			for (int destChannel = 0; destChannel < 2; ++destChannel) {
				float panValue = stereoPanValues[sourceChannel][destChannel];
				IteratorPack newPack(currBuffer, noteVelocity*micGains.at(j)*panValue, sampleCountVector.at(j), (false), destChannel, timeStamp);
				iterators->push_back(newPack);
			}
		}
	}

	//for (int channel = 0; channel < 3; ++channel) {
	//	//float *out = bufferToFill->getWritePointer(channel);

	//	for (int j = 0; j < inVector.size(); j++) {
	//		if (inVector.at(j) == 0) {
	//			continue;
	//		}
	//		int samplesToCopy = std::min(sampleCountVector.at(j), blockSize - timeStamp);

	//		// Fix source channel and gain applied

	//		bufferToFill->addFrom(channel, timeStamp, *inVector.at(j), 0, 0, samplesToCopy, noteVelocity*micGains.at(j));
	//		//LEFT OFF: ADD A INT TO THE IteratorPack TO TELL YOU WHERE YOU LEFT OFF INSTEAD OF CREATING ANOTHER AUDIOSAMPLEBUFFER EVERY TIME
	//		if ((samplesToCopy + timeStamp >= blockSize)) {
	//			//TODO: Fix the boolean of if this is a hi hat open
	//			//IteratorPack newPack(((float*)(inVector.at(j) + i)), noteVelocity*micGains.at(j), sampleCountVector.at(j) - i, (instrumentSamples == hi_hat_openSampleBuffers));

	//			//IteratorPack newPack(((float*)(inVector.at(j) + samplesToCopy)), noteVelocity*micGains.at(j), sampleCountVector.at(j) - samplesToCopy, (false), channel);

	//			IteratorPack newPack(inVector.at(j), noteVelocity*micGains.at(j), sampleCountVector.at(j) - samplesToCopy, (false), channel);

	//			newPack.sampleLeftAt = samplesToCopy;
	//			iterators->push_back(newPack);
	//		}
	//	}

	//}

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
void Instrument::panMono(AudioSampleBuffer* input, int inputChannel, AudioSampleBuffer* output, float pan) {
	jassert(output->getNumChannels() == 2);
	jassert(input->getNumChannels() > inputChannel);


}

void Instrument::fillFromIterators(AudioSampleBuffer output) {
	std::list<IteratorPack>::iterator it;
	std::list<IteratorPack>::iterator end;
	it = iterators->begin();
	end = iterators->end();

	//Loop through the iterators left from previous blocks and fill the current block
	while (it != end) {
		IteratorPack currPack = *it;
		//int i=0;
		//for (int channel = 0; channel < 1; ++channel){
		//float *out = buffer.getWritePointer(currPack.channelNum);
		int samplesToCopy = std::min(currPack.samplesLeft, output.getNumSamples()- currPack.timestamp);
		//bufferToFill->addFrom(channel, timeStamp, *inVector.at(j), 0, 0, samplesToCopy, noteVelocity*micGains.at(j));
		output.addFrom(currPack.channelNum, currPack.timestamp, *currPack.address, 0, currPack.sampleLeftAt, samplesToCopy, currPack.velocity);
		//buffer.addFrom(,,)

		//}
		//If the iterator has reached the end, erase the element.
		if (samplesToCopy == currPack.samplesLeft) {
			it = iterators->erase(it);
		}
		//Else update the remaining numbers.
		else {
			it->sampleLeftAt += samplesToCopy;
			it->samplesLeft -= samplesToCopy;
			it->timestamp = 0;
			//it->address += i;
			it++;
		}
	}
}