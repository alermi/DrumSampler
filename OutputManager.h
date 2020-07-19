/*
  ==============================================================================

    OutputManager.h
    Created: 13 Jul 2020 10:27:39pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class OutputManager {
public:
	OutputManager(int fadeOutSamples);
	void processBlock(AudioProcessor * processor, AudioSampleBuffer *outputBuffer, std::map<String, AudioSampleBuffer*> *micOutputs);
private:
	std::map<String, AudioSampleBuffer> overflowBuffers;
	int fadeOutSamples;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OutputManager)
};