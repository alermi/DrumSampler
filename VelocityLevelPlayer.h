/*
  ==============================================================================

    VelocityLevelPlayer.h
    Created: 5 Jul 2020 1:07:58am
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "HitIterator.h"
#include "MicController.h"
#include "FileManager.h"
#include "BlockEvents.h"

#define MAX_NUM_TRIGGERS_IN_BLOCK_PER_VELOCITY_LEVEL 4
#define MAX_NUM_KILLS_IN_BLOCK_PER_VELOCITY_LEVEL 4
#define FADE_OUT_SAMPLES 1000

class VelocityLevelPlayer {
private:
	AudioProcessor* processor;
	int levelNum;
	std::vector<TriggerInformation> newTriggers;
	std::vector<int> newKills;
	std::vector<int> stopPoints;
	//HitIterator* findAvailableHitIterator();
	int blockSize;
	std::unique_ptr<HitIterator> hitIterator;
	//HitIterator* hitIterator;
	BlockEvents blockEvents;
	int roundRobinCount;
public:	
	VelocityLevelPlayer(AudioProcessor * processor, FileManager* fileManager, NoteProperties* noteProperties, int levelNum, std::map<String, AudioSampleBuffer*>* micOutputs, std::map<String, bool> bleedMap, int roundRobinCount);
	void trigger(TriggerInformation triggerInfo);
	void kill(int timeStamp);
	void processBlock(bool isMutingBleeds);
	void setBlockSize(int blockSize);
	void createBuffers(FileManager* fileManager, NoteProperties* noteProperties);
	std::map<String, std::map<int, AudioSampleBuffer*>> micMap;
	~VelocityLevelPlayer();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VelocityLevelPlayer)
};