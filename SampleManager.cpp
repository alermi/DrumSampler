/*
  ==============================================================================

    SampleManager.cpp
    Created: 13 Aug 2019 9:47:50pm
    Author:  Ani

  ==============================================================================
*/

#include "SampleManager.h"
#include <windows.h>
#include <Tchar.h>


//TODO: Make static
void SampleManager::findSamplesFolder(){
	samplesFolder=new File(String("C:\\Users\\Ani\\Desktop\\Samples Mono"));
/*
	FileChooser samplesFinder("Please choose the folder containing the samples for DrumSampler.");
	samplesFinder.browseForDirectory();
	File returned = samplesFinder.getResult();
	samplesFolder = new File(returned);*/
}

File* SampleManager::getSamplesFolder() {
	return samplesFolder;
}

SampleManager::SampleManager() {
	MidiMap = std::map<int, std::pair<String, int>>();
	fillMidiMap();
	findSamplesFolder();
}

void SampleManager::fillMidiMap() {
	int i;
	LPCTSTR path = _T("C:\\Users\\Ani\\Documents\\JUCE Projects\\DrumSampler\\Source\\MidiMapping.ini");

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