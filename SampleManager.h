/*
  ==============================================================================

    SampleManager.h
    Created: 13 Aug 2019 9:47:50pm
    Author:  Ani

  ==============================================================================
*/
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class SampleManager {
public:
	SampleManager();
	File * samplesFolder;

	void findSamplesFolder();
	void fillMidiMap();
	File *getSamplesFolder();
	std::map<int, std::pair<String,int>> MidiMap;
};




