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
	static void addTomParameters(AudioProcessorValueTreeState::ParameterLayout& layout);
	static void addCymbalParameters(AudioProcessorValueTreeState::ParameterLayout& layout);
	static void addCymbalBalanceParameters(AudioProcessorValueTreeState::ParameterLayout& layout);

	static std::unique_ptr<AudioProcessorParameterGroup> getGeneralInstrumentParameters(String instrumentName);
	static std::unique_ptr<AudioProcessorParameterGroup> getSpecificInstrumentParameters(String specificInstrumentName, bool hasCloseMic);
	static std::unique_ptr<AudioProcessorParameterGroup> getCymbalBalanceParameters(String micType);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterBuilder)

};
