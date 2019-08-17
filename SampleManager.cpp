/*
  ==============================================================================

    SampleManager.cpp
    Created: 13 Aug 2019 9:47:50pm
    Author:  Ani

  ==============================================================================
*/

#include "SampleManager.h"

//TODO: Make static
void SampleManager::findSamplesFolder(){
	//samplesFolder=new File(String("C:\\Users\\Ani\\Documents\\JUCE Projects\\DrumSampler\\Samples"));

	FileChooser samplesFinder("Please choose the folder containing the samples for DrumSampler.");
	samplesFinder.browseForDirectory();
	File returned = samplesFinder.getResult();
	samplesFolder = new File(returned);
}

File* SampleManager::getSamplesFolder() {
	return samplesFolder;
}

SampleManager::SampleManager() {
	findSamplesFolder();
}