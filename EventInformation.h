/*
  ==============================================================================

    EventInformation.h
    Created: 17 Jul 2020 8:05:24pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
class EventInformation {
public:
	int timeStamp;
	bool isNoteOn;
	std::map<String, float> micGains;
	float noteVelocity;
	std::array<float, 2> monoPanValues;
	std::vector<std::array<float, 2>> stereoPanValues;
	EventInformation(int timeStamp, bool isNoteOn) {
		this->timeStamp = timeStamp;
		this->isNoteOn = isNoteOn;
	}
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EventInformation)
};