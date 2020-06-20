/*
  ==============================================================================

    NoteSound.h
    Created: 13 Aug 2019 8:21:30pm
    Author:  Ani

  ==============================================================================
*/
//#include "../JuceLibraryCode/JuceHeader.h"
#pragma once
#include "FileManager.h"
#include "IteratorPack.h"
#include <vector>
#include <list>
#include <iterator>
#include <array>

//TODO: Remove all namespace stds
using namespace std;

class NoteSound {
public:
	//String instrumentName;
	//int velocityCount;
	NoteProperties *noteProperties;

	std::map<String, std::map<String, AudioSampleBuffer*>> micMap;
	FileManager* fileManager;
	list<IteratorPack>* iterators;
	AudioProcessor* processor;
	//AudioSampleBuffer mainBuffer;
	//static const int micToExtraChannelMap[7];S
	String getBufferMapKey(int velocityNum, int versionNum);
	void createBuffers();
	void triggerSound(std::map<String, float> micGains, float noteVelocity, int timeStamp, float monoPan, AudioProcessor *processor);
	NoteSound(NoteProperties* noteProperties, FileManager* fileManager, AudioProcessor* processor);
	void fillFromIterators(AudioSampleBuffer output);
	~NoteSound();
};