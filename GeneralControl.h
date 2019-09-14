/*
  ==============================================================================

    GeneralControl.h
    Created: 13 Sep 2019 7:57:40pm
    Author:  Ani

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class GeneralControl    : public Component
{
public:
    GeneralControl();
    ~GeneralControl();
	Label masterLabel;
	Label roomLabel;
	Slider masterSlider;
	Slider roomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> masterSliderAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomSliderAttachment;

	void attach(AudioProcessorValueTreeState* parameters);
    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GeneralControl)
};
