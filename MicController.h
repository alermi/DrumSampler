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
	{"kickout", 1},
	{"kicksub", 1},
	{"snrtop", 2},
	{"snrbot", 2},
	{"tom1", 3},
	{"tom2", 3},
	{"tom3", 3},
	{"tom4", 3},
	{"tom5", 3},
	{"hh", 4},
	{"ride", 5},
	{"roommono", 6},
	{"roomstereo", 6},
	{"roomfar", 6},
	{"oh", 7}
};
class MicController {
public:
	MicController(AudioProcessorValueTreeState *treeState);

	static std::vector<String> getMicNames();
	static std::map<String, int> getMicChannelCountMap();
	static std::map<String, int> getMicExtraChannelMap();
	//LEFT OFF: In order to complete this getMicGain, create a constructor with the treeState to get the parameters from
	std::map<String, float> getMicGains(String generalControllerName, String specificControllerName);
	std::map<String, float> getEmptyMicGains();
private:
	AudioProcessorValueTreeState* treeState;

	void applyCymbalControl(std::map<String, float> *micGains, String specificInstrumentName);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MicController)
};