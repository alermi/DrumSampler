/*
  ==============================================================================

    TriggerInformation.h
    Created: 5 Jul 2020 1:21:52am
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "EventInformation.h"

class TriggerInformation : public EventInformation {
public:



	TriggerInformation(std::map<String, float> micGains, float noteVelocity, int timeStamp) 
				: EventInformation(timeStamp, true) {
		this->micGains = micGains;
		this->noteVelocity = noteVelocity;
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

	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TriggerInformation)
	JUCE_LEAK_DETECTOR(TriggerInformation)
};