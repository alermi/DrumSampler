/*
  ==============================================================================

	OutputManager.cpp
	Created: 13 Jul 2020 10:27:39pm
	Author:  Ani

  ==============================================================================
*/

#include "OutputManager.h"
#include "MicController.h"
OutputManager::OutputManager(int fadeOutSamples, AudioProcessorValueTreeState* treeState) {
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
	this->treeState = treeState;
	this->fadeOutSamples = fadeOutSamples;
	this->outputBlockSize = 0;
	this->samplingBlockSize = 0;
}

void OutputManager::prepareToPlay(int newSamplingBlockSize, int newOutputBlockSize) {
	//for (int i = 0; i < NUM_OUTPUT_CHANNELS_EXCLUDING_MAIN; i++) {
	//	this->outputBuffers[i].setSize(2, blockSize);
	//}
	this->outputBlockSize = newOutputBlockSize;
	this->samplingBlockSize = newSamplingBlockSize;
	resamplingBuffer.setSize(2, newOutputBlockSize);
	summingBuffer.setSize(2, newSamplingBlockSize);
	panningBuffer.setSize(2, newSamplingBlockSize);
	//ResamplingAudioSource resampling = ResamplingAudioSource(outputBuffers[0], false, 2);
}

void OutputManager::processBlock(AudioProcessor * processor, AudioSampleBuffer *outputBuffer, std::map<String, AudioSampleBuffer*> *micOutputs) {
	const AudioSampleBuffer &mainBuffer = processor->getBusBuffer(*outputBuffer, false, 0);
	//mainBuffer.getWritePointer(0)[0] = 1.0f;
	jassert(outputBlockSize == mainBuffer.getNumSamples());
	// Loop for each mic
	for (auto const& micOutput : *micOutputs) {
		String currMicName = micOutput.first;
		AudioSampleBuffer &currMicOutput = *micOutput.second;
		AudioSampleBuffer &currOverflowBuffer = overflowBuffers[currMicName];
		jassert(currMicOutput.getNumChannels() == 2);
		jassert(currOverflowBuffer.getNumChannels() == 2);
		jassert(currMicOutput.getNumSamples() == samplingBlockSize + fadeOutSamples);

		int numSamplesToCopy = std::min(samplingBlockSize, fadeOutSamples);
		int samplesLeftInOverflow = fadeOutSamples - numSamplesToCopy;
		jassert(samplesLeftInOverflow >= 0);

		resamplingBuffer.clear();
		summingBuffer.clear();
		panningBuffer.clear();
		int extraChannelNum = MicController::getMicExtraChannelMap()[currMicName];
		const AudioSampleBuffer &extraBuffer = processor->getBusBuffer(*outputBuffer, false, extraChannelNum);
		// Sum the necessary samples from both micOutputs and overflowBuffers into the summingBuffer
		for (int i = 0; i < 2; i++) {
			summingBuffer.copyFrom(i, 0, currOverflowBuffer, i, 0, numSamplesToCopy);
			summingBuffer.addFrom(i, 0, currMicOutput, i, 0, samplingBlockSize);
		}
		// Pan the left and right channel into panningBuffer's channels
		for (int i = 0; i < 2; i++) {
			float panValue = getPanValue(currMicName, i);
			float leftOutGain = sin((juce::float_Pi * 0.5f) * (1 - panValue)) ;
			float rightOutGain = sin((juce::float_Pi * 0.5f) * (panValue));

			panningBuffer.addFrom(0, 0, summingBuffer, i, 0, samplingBlockSize, leftOutGain);
			panningBuffer.addFrom(1, 0, summingBuffer, i, 0, samplingBlockSize, rightOutGain);
		}

		// Resample (into resamplingBuffer) the samples we got from audio files into the size of the 
		//output buffer in case they have different sample rates
		resample(panningBuffer, 0, samplingBlockSize, resamplingBuffer, 0, outputBlockSize, &interpolators[currMicName].first, 0);
		resample(panningBuffer, 0, samplingBlockSize, resamplingBuffer, 0, outputBlockSize, &interpolators[currMicName].second, 1);
		
		for (auto currOutputBuffer : { mainBuffer, extraBuffer }) {
			int currBufferChannelCount = currOutputBuffer.getNumChannels();
			jassert(currBufferChannelCount == 0 || currBufferChannelCount == 2);
			// If the output channel is available, add the sounds into the output channel.
			if (currBufferChannelCount == 2) {
				//TODO: Get the pan values from panManager and multiply these
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
				jassert(currOverflowBuffer.getNumSamples() == samplingBlockSize + samplesLeftInOverflow);
				currMicOutput.addFrom(i, samplingBlockSize, currOverflowBuffer, i, samplingBlockSize, samplesLeftInOverflow);

				//currOverflowBuffer.copyFrom(0, 0, currOverflowBuffer, 0, numSamplesToCopy, samplesLeftInOverflow);
			}
			// Copy from micOutput with all the non-used data into the overflow buffer
			currOverflowBuffer.copyFrom(i, 0, currMicOutput, i, samplingBlockSize, fadeOutSamples);
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



float OutputManager::getPanValue(String micName, int channelNum)
{
	if (channelNum == 0) {
		return *this->treeState->getRawParameterValue(micName + " Left Pan");
	}
	else if (channelNum == 1){
		return *this->treeState->getRawParameterValue(micName + " Right Pan");
	}
	else {
		jassertfalse;
		return 0.5f;
	}
}