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
	File * samplesFolder;
	std::map<int, std::pair<String, int>> MidiMap;
	AudioFormatManager* formatManager;

	void findSamplesFolder();
	void fillMidiMap();
	File *getSamplesFolder();
	AudioSampleBuffer* readBuffer(String pathName);
	~FileManager();

};




