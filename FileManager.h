/*
  ==============================================================================

    SampleManager.h
    Created: 13 Aug 2019 9:47:50pm
    Author:  Ani

  ==============================================================================
*/
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "NoteProperties.h"


class FileManager {
public:
	FileManager();
	File samplesFolder;
	File loadedFolder;
	File midiMappingFolder;
	std::map<int, NoteProperties> MidiMap;
	AudioFormatManager* formatManager;

	void findLoadedFolder();
	void fillMidiMap();
	File *getSamplesFolder();
	AudioSampleBuffer* readBuffer(String pathName);
	~FileManager();

};




