/*
  ==============================================================================

    OutputManager.cpp
    Created: 13 Jul 2020 10:27:39pm
    Author:  Ani

  ==============================================================================
*/

#include "OutputManager.h"
#include "MicController.h"
OutputManager::OutputManager(int fadeOutSamples) {
	for (String micName : MicController::getMicNames()) {
		this->overflowBuffers[micName].setSize(2, fadeOutSamples);
		this->overflowBuffers[micName].clear();
	}
	this->fadeOutSamples = fadeOutSamples;
}

void OutputManager::processBlock(AudioProcessor * processor, AudioSampleBuffer *outputBuffer, std::map<String, AudioSampleBuffer*> *micOutputs) {
	AudioSampleBuffer &mainBuffer = processor->getBusBuffer(*outputBuffer, false, 0);
	//mainBuffer.getWritePointer(0)[0] = 1.0f;
	int outputBlockSize = mainBuffer.getNumSamples();
	for (auto const& micOutput : *micOutputs) {
		String currMicName = micOutput.first;
		AudioSampleBuffer &currMicOutput = *micOutput.second;
		AudioSampleBuffer &currOverflowBuffer = overflowBuffers[currMicName];
		jassert(currMicOutput.getNumChannels() == 2);
		jassert(currOverflowBuffer.getNumChannels() == 2);
		jassert(currMicOutput.getNumSamples() == outputBlockSize + fadeOutSamples);

		int numSamplesToCopy = std::min(outputBlockSize, fadeOutSamples);
		int samplesLeftInOverflow = fadeOutSamples - numSamplesToCopy;
		jassert(samplesLeftInOverflow >= 0);

		// Loop for each channel
		for (int i = 0; i < 2; i++) {
			// Copy the necessary samples from both micOutputs and overflowBuffers into the mainBuffer
			mainBuffer.addFrom(i, 0, currOverflowBuffer, i, 0, numSamplesToCopy);
			mainBuffer.addFrom(i, 0, currMicOutput, i, 0, outputBlockSize);
			// Preparing the overflow buffer for the next block
			// If the overflowBuffer is bigger than the output buffer, have to shift data
			if (samplesLeftInOverflow > 0) {
				// Shift the non copied data into the micOutput's necessary places
				jassert(currOverflowBuffer.getNumSamples() == outputBlockSize + samplesLeftInOverflow);
				currMicOutput.addFrom(i, outputBlockSize, currOverflowBuffer, i, outputBlockSize, samplesLeftInOverflow);

				//currOverflowBuffer.copyFrom(0, 0, currOverflowBuffer, 0, numSamplesToCopy, samplesLeftInOverflow);
			}
			// Copy from micOutput with all the non-used data into the overflow buffer
			currOverflowBuffer.copyFrom(i, 0, currMicOutput, i, outputBlockSize, fadeOutSamples);
		}

		//TODO: Add extra routings for each mic
	}
}