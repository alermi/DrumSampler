/*
  ==============================================================================

    InstrumentControl.h
    Created: 12 Sep 2019 1:24:38pm
    Author:  Ani

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class InstrumentControl    : public Component
{
public:
    InstrumentControl();
    ~InstrumentControl();

	void attach(AudioProcessorValueTreeState* parameters, String instrumentName);

    void paint (Graphics&) override;
    void resized() override;

private:

	std::unique_ptr<GroupComponent> groupComponent;
	Slider volumeSlider;
	Slider leftPan;
	Slider rightPan;
	Slider monoPan;
	Slider roomSlider;
	Slider overheadSlider;
	Slider directSlider;
	Label panLabel;
	Label roomLabel;
	Label overheadLabel;
	Label directLabel;
	Label volumeLabel;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeSliderAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> monoPanSliderAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> stereoPanLSliderAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> stereoPanRSliderAttachment;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> overheadSliderAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomSliderAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> directSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentControl)
};
