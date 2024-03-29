/*
  ==============================================================================

    MicController.h
    Created: 16 Jun 2020 4:45:33pm
    Author:  Ani

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
static const std::map<String, int> MIC_CHANNEL_COUNT_MAP = {
	{"kickin", 1},
	{"kickout", 1},
	{"kicksub", 1},
	{"snrtop", 1},
	{"snrbot", 1},
	{"tom1", 1},
	{"tom2", 1},
	{"tom3", 1},
	{"tom4", 1},
	{"tom5", 1},
	{"hh", 1},
	{"ride", 1},
	{"roommono", 1},
	{"roomstereo", 2},
	{"roomfar", 2},
	{"oh", 2}
};
static const std::map<String, int> MIC_EXTRA_CHANNEL_MAP = {
	{"kickin", 1},
	{"kickout", 2},
	{"kicksub", 3},
	{"snrtop", 4},
	{"snrbot", 5},
	{"tom1", 6},
	{"tom2", 7},
	{"tom3", 8},
	{"tom4", 9},
	{"tom5", 10},
	{"hh", 11},
	{"ride", 12},
	{"roommono", 13},
	{"roomstereo", 14},
	{"roomfar", 15},
	{"oh", 16}
};
class MicController {
public:
	MicController(AudioProcessorValueTreeState *treeState);

	static std::vector<String> getMicNames();
	static std::map<String, int> getMicChannelCountMap();
	static std::map<String, int> getMicExtraChannelMap();
	bool getMutingBleeds();
	//LEFT OFF: In order to complete this getMicGain, create a constructor with the treeState to get the parameters from
	std::map<String, float> getMicGains(String generalControllerName, String specificControllerName);
	std::map<String, float> getEmptyMicGains();
private:
	AudioProcessorValueTreeState* treeState;

	void applyCymbalControl(std::map<String, float> *micGains, String specificInstrumentName);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MicController)
};