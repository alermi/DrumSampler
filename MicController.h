/*
  ==============================================================================

    MicController.h
    Created: 16 Jun 2020 4:45:33pm
    Author:  Ani

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
static const std::map<String, int> MIC_CHANNEL_MAP = {
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

class MicController {
public:
	MicController(AudioProcessorValueTreeState *treeState);

	static std::vector<String> getMicNames();
	static std::map<String, int> getMicChannelMap();
	//LEFT OFF: In order to complete this getMicGain, create a constructor with the treeState to get the parameters from
	std::map<String, float> getMicGains(String controllerName);
	std::map<String, float> getEmptyMicGains();
private:
	AudioProcessorValueTreeState* treeState;

	void applyCommonControls(std::map<String, float> *micGains);
		//SHOUDL I DO MIC MAPS SEPERATELY
};