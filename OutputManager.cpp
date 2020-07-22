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
	//for (int i = 0; i < NUM_OUTPUT_CHANNELS_EXCLUDING_MAIN; i++) {
	//	this->outputBuffers[i] = AudioSampleBuffer(2, 0);
	//}
	for (String micName : MicController::getMicNames()) {
		//TODO: Reconsider the initial number of samples.
		interpolators[micName].first.reset();
		interpolators[micName].second.reset();
	}

	this->fadeOutSamples = fadeOutSamples;
}

void OutputManager::prepareToPlay(int blockSize) {
	//for (int i = 0; i < NUM_OUTPUT_CHANNELS_EXCLUDING_MAIN; i++) {
	//	this->outputBuffers[i].setSize(2, blockSize);
	//}
	resamplingBuffer.setSize(2, blockSize);
	summingBuffer.setSize(2, blockSize);
	//ResamplingAudioSource resampling = ResamplingAudioSource(outputBuffers[0], false, 2);
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

		int extraChannelNum = MicController::getMicExtraChannelMap()[currMicName];
		AudioSampleBuffer &extraBuffer = processor->getBusBuffer(*outputBuffer, false, extraChannelNum);
		//resamplingBuffer.clear();
		for (int i = 0; i < 2; i++) {
			// Copy the necessary samples from both micOutputs and overflowBuffers into the mainBuffer
			summingBuffer.copyFrom(i, 0, currOverflowBuffer, i, 0, numSamplesToCopy);
			summingBuffer.addFrom(i, 0, currMicOutput, i, 0, outputBlockSize);
		}
		//resample(currOverflowBuffer, 0, numSamplesToCopy, resamplingBuffer, 0, numSamplesToCopy);
		resample(summingBuffer, 0, outputBlockSize, resamplingBuffer, 0, outputBlockSize, &interpolators[currMicName].first, 0);
		resample(summingBuffer, 0, outputBlockSize, resamplingBuffer, 0, outputBlockSize, &interpolators[currMicName].second, 1);
		for (auto currOutputBuffer : { mainBuffer, extraBuffer }) {
			int currBufferChannelCount = currOutputBuffer.getNumChannels();
			jassert(currBufferChannelCount == 0 || currBufferChannelCount == 2);
			// If the output channel is available, do all the rest of the stuff
			if (currBufferChannelCount == 2) {
				currOutputBuffer.addFrom(0, 0, resamplingBuffer, 0, 0, resamplingBuffer.getNumSamples());
				currOutputBuffer.addFrom(1, 0, resamplingBuffer, 1, 0, resamplingBuffer.getNumSamples());
			}
			else {
				continue;
			}
		}
		// Loop for each channel
		for (int i = 0; i < 2; i++) {
			// Copy the necessary samples from both micOutputs and overflowBuffers into the mainBuffer
			//mainBuffer.addFrom(i, 0, currOverflowBuffer, i, 0, numSamplesToCopy);
			//mainBuffer.addFrom(i, 0, currMicOutput, i, 0, outputBlockSize);
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

void OutputManager::resample(AudioSampleBuffer& source, int sourceStartSample, int sourceNumSamples, AudioSampleBuffer& output, int destStartSample, int destNumSamples, LinearInterpolator* interpolator, int channelNum) {
	//this->interpolator.reset();
	double speedRatio = ((double)sourceNumSamples) / ((double) destNumSamples);
	interpolator->process(speedRatio, source.getReadPointer(channelNum), output.getWritePointer(channelNum), destNumSamples);
	//this->interpolator.reset();
	//int b = interpolator.processAdding(speedRatio, source.getReadPointer(1), output.getWritePointer(1), destNumSamples, 1.0f);
	return;
}