/*
  ==============================================================================

    ParameterBuilder.h
    Created: 15 Jun 2020 6:41:57pm
    Author:  Ani

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class ParameterBuilder {
public:
	static AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
	static void addKickParameters(AudioProcessorValueTreeState::ParameterLayout& layout);
	static void addSnareParameters(AudioProcessorValueTreeState::ParameterLayout& layout);

	static std::unique_ptr<AudioProcessorParameterGroup> getGeneralInstrumentParameters(String instrumentName);
};
