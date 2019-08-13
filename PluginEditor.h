/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DrumSamplerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DrumSamplerAudioProcessorEditor (DrumSamplerAudioProcessor&);
    ~DrumSamplerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	DrumSamplerAudioProcessor& processor;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
	Slider kickRoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> kickRoomSliderAttachment;

	Slider kickMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> kickMasterSliderAttachment;

	Slider snareRoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> snareRoomSliderAttachment;

	Slider snareBottomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> snareBottomSliderAttachment;

	Slider snareMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> snareMasterSliderAttachment;

	Slider chinaMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> chinaMasterSliderAttachment;

	Slider crash_altMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> crash_altMasterSliderAttachment;

	Slider crash_mainMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> crash_mainMasterSliderAttachment;

	Slider floor_tomMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> floor_tomMasterSliderAttachment;

	Slider floor_tomRoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> floor_tomRoomSliderAttachment;

	Slider hi_hatRoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> hi_hatRoomSliderAttachment;

	Slider hi_hatMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> hi_hatMasterSliderAttachment;

	Slider rack_tomMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rack_tomMasterSliderAttachment;

	Slider rack_tomRoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rack_tomRoomSliderAttachment;

	Slider rideMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rideMasterSliderAttachment;

	Slider stackMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> stackMasterSliderAttachment;

	Slider masterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> masterSliderAttachment;

	Slider masterRoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> masterRoomSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrumSamplerAudioProcessorEditor)
};
