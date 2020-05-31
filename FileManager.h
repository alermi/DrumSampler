/*
  ==============================================================================

    SampleManager.h
    Created: 13 Aug 2019 9:47:50pm
    Author:  Ani

  ==============================================================================
*/
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class FileManager {
public:
	FileManager();
	std::map<int, std::pair<String, int>> MidiMap;
	AudioFormatManager* formatManager;

	void fillMidiMap();
	AudioSampleBuffer* readBuffer(String pathName);
	~FileManager();

};




