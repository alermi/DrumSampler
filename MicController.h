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
	{"snrbot", 1},
	{"snrtop", 1},
	{"tom1", 1},
	{"tom2", 1},
	{"tom3", 1},
	{"ride", 1},
	{"roommono", 1},
	{"roomstereo", 2},
	{"roomfar", 2},
	{"oh", 2}
};

class MicController {
public:
	static std::vector<String> getMicNames();
	static std::map<String, int> getMicChannelMap();
	static float getMicGain(String micName);
private:
#if JUCE_DEBUG
	//std::map<>
#endif
		//SHOUDL I DO MIC MAPS SEPERATELY
};