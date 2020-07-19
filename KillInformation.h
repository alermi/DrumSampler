/*
  ==============================================================================

    KillInformation.h
    Created: 17 Jul 2020 8:03:32pm
    Author:  Ani

  ==============================================================================
*/

#pragma once
#include "EventInformation.h"

class KillInformation : public EventInformation {
public:
	KillInformation(int timeStamp) : EventInformation(timeStamp, false){}
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KillInformation)

};