/*
  ==============================================================================

    BufferIterator.h
    Created: 16 Aug 2019 9:59:19pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include <array>
#include <iterator>

#define SAMPLES_TO_KILL 100

class BufferIterator {
public:
	AudioSampleBuffer *sample;
	int sampleLeftAt;
	float velocity;
	int samplesLeft;
	int channelNum;
	bool hasEnded;
	int extraBusNumber;
	//AudioSampleBuffer *mainBuffer;
	std::array<float, 2> monoPanValues;
	std::vector<std::array<float, 2>> stereoPanValues;

	BufferIterator();
	~BufferIterator();
	//void iterate(AudioSampleBuffer output);
	void iterate(AudioSampleBuffer* output, int startSample, int endSample, bool fadeOut);
	void trigger(AudioSampleBuffer *sample, float velocity, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues, int extraBusNumber);
	void reset();
private:
	int getSamplesToCopy(int startSample, int endSample);
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BufferIterator)
	JUCE_LEAK_DETECTOR(BufferIterator)
};