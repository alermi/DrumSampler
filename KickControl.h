/*
  ==============================================================================

    KickControl.h
    Created: 13 Sep 2019 1:15:37am
    Author:  Ani

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "InstrumentControl.h"
//==============================================================================
/*
*/
class KickControl: public InstrumentControl
{
public:
    KickControl();
    ~KickControl();
	
	Slider inOutSlider;
	Label inOutLabel;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> inOutSliderAttachment;

	void attach(AudioProcessorValueTreeState* parameters, String instrumentName);

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KickControl)
};
