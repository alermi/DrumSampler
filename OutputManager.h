/*
  ==============================================================================

    OutputManager.h
    Created: 13 Jul 2020 10:27:39pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#define NUM_OUTPUT_CHANNELS_EXCLUDING_MAIN 7
class OutputManager {
public:
	OutputManager(int fadeOutSamples);
	void processBlock(AudioProcessor * processor, AudioSampleBuffer *outputBuffer, std::map<String, AudioSampleBuffer*> *micOutputs);
	void prepareToPlay(int blockSize);
private:
	void resample(AudioSampleBuffer& source, int sourceStartSample, int sourceNumSamples, AudioSampleBuffer& output, int destStartSample, int destNumSamples);
	LinearInterpolator interpolator;
	AudioSampleBuffer resamplingBuffer;
	AudioSampleBuffer outputBuffers[NUM_OUTPUT_CHANNELS_EXCLUDING_MAIN];
	std::map<String, AudioSampleBuffer> overflowBuffers;
	int fadeOutSamples;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OutputManager)
};