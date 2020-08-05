/*
  ==============================================================================

    Constants.h
    Created: 2 Aug 2020 10:12:02pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class Constants {
	//TODO: move the constants in MicController to here
public:
	static std::map<String, std::map<String, bool>> getAllInstrumentsBleedFlags();
	int a = 4;
};
