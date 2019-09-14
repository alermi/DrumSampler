/*
  ==============================================================================

    SnareControl.h
    Created: 14 Sep 2019 1:59:02am
    Author:  Ani

  ==============================================================================
*/

#pragma once

#include "InstrumentControl.h"
//==============================================================================
/*
*/
class SnareControl    : public InstrumentControl
{
public:
    SnareControl();
    ~SnareControl();

	Slider topBottomSlider;
	Label topBottomLabel;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> topBottomSliderAttachment;

	void attach(AudioProcessorValueTreeState* parameters, String instrumentName);
    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SnareControl)
};
