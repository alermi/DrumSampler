/*
  ==============================================================================

    SampleManager.cpp
    Created: 13 Aug 2019 9:47:50pm
    Author:  Ani

  ==============================================================================
*/

#include "FileManager.h"
#include <windows.h>
#include <Tchar.h>

const String APPDATA_FOLDER_NAME = "DrumSampler";

FileManager::FileManager() {
	findLoadedFolder();
	MidiMap = std::map<int, std::pair<String, int>>();
	fillMidiMap();
	formatManager = new AudioFormatManager();
	formatManager->registerBasicFormats();
}

void FileManager::findLoadedFolder() {
	File loadedPathFile = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory).getChildFile(APPDATA_FOLDER_NAME);
	String loadedPath = loadedPathFile.getChildFile("installPath").loadFileAsString();
	DBG("Loaded path " + loadedPath);
	loadedFolder = File(loadedPath);
	samplesFolder = (loadedFolder.getChildFile(".\\Samples"));
	DBG("Samples path " + samplesFolder.getFullPathName());
	midiMappingFolder = (loadedFolder.getChildFile(".\\MidiMapping.ini"));
	DBG("Midi mapping path " + midiMappingFolder.getFullPathName());
}


File* FileManager::getSamplesFolder() {
	return &samplesFolder;
}


void FileManager::fillMidiMap() {
	int i;

	String mapname = String(midiMappingFolder.getFullPathName());
	
	LPCTSTR path = _T(mapname.toUTF8());

	for (i = 0; i < 256; i++) {
		LPSTR charArray[50];
		std::string returnString;
		std::string tempStr = std::to_string(i);
		LPCSTR key_ptr = tempStr.c_str();

		GetPrivateProfileString(_T("mapping"), (key_ptr), NULL, (LPSTR)charArray, sizeof(charArray), path);
		returnString = (LPSTR)charArray;

		UINT velocityCount=GetPrivateProfileInt(_T("velocities"), (returnString.c_str()), NULL, path);
		
		MidiMap.insert(std::pair<int, std::pair<String, int>>(i, std::pair<String,int>(returnString, velocityCount)));
	}
}
AudioSampleBuffer* FileManager::readBuffer(String pathName) {

	std::unique_ptr<AudioFormatReaderSource> readerSource;
	File newFile(pathName);

	if (newFile.existsAsFile()) {
		std::unique_ptr<AudioFormatReader> reader(this->formatManager->createReaderFor(newFile));
		AudioSampleBuffer *newBuffer = new AudioSampleBuffer(reader->numChannels, reader->lengthInSamples);
		reader->read(newBuffer, 0, reader->lengthInSamples, 0, true, true);

		Range<float> range1 = newBuffer->findMinMax(0, 0, reader->lengthInSamples);
		float max1 = (std::max)(abs(range1.getStart()), abs(range1.getEnd()));
		newBuffer->applyGain(0, 0, newBuffer->getNumSamples(), 1 / max1);
		newBuffer->applyGainRamp(0, 0, 10, 0, 1);

		if (newBuffer->getNumChannels() == 2) {
			Range<float> range2 = newBuffer->findMinMax(1, 0, reader->lengthInSamples);
			float max2 = (std::max)(abs(range2.getStart()), abs(range2.getEnd()));
			newBuffer->applyGain(1, 0, newBuffer->getNumSamples(), 1 / max2);
			newBuffer->applyGainRamp(1, 0, 10, 0, 1);
		}

		return newBuffer;
	}
	else {
		return new AudioSampleBuffer();
	}
}

FileManager::~FileManager() {
	delete formatManager;
}