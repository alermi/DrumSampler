/*
  ==============================================================================

    TriggerInformation.h
    Created: 5 Jul 2020 1:21:52am
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class TriggerInformation {
public:

	std::map<String, float> micGains;
	float noteVelocity;
	int timeStamp;
	std::array<float, 2> monoPanValues;
	std::vector<std::array<float, 2>> stereoPanValues;

	TriggerInformation(std::map<String, float> micGains, float noteVelocity, int timeStamp, std::array<float, 2> monoPanValues, std::vector<std::array<float, 2>> stereoPanValues) {
		this->micGains = micGains;
		this->noteVelocity = noteVelocity;
		this->timeStamp = timeStamp;
		this->monoPanValues = monoPanValues;
		this->stereoPanValues = stereoPanValues;
	}

	static bool compare(TriggerInformation t1, TriggerInformation t2) {
		if (t1.timeStamp < t2.timeStamp) {
			return true;
		}
		else if (t1.timeStamp > t2.timeStamp) {
			return false;
		}
		else {
			jassertfalse;
			return false;
		}
	}
};