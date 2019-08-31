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

	Slider kickInOutSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> kickInOutSliderAttachment;

	Slider kickDirectSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> kickDirectSliderAttachment;

	Slider kickOverheadSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> kickOverheadSliderAttachment;

	Slider snareRoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> snareRoomSliderAttachment;

	Slider snareBottomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> snareBottomSliderAttachment;

	Slider snareMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> snareMasterSliderAttachment;

	Slider snareOverheadSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> snareOverheadSliderAttachment;

	Slider snareDirectSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> snareDirectSliderAttachment;

	Slider chinaMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> chinaMasterSliderAttachment;

	Slider crash_altMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> crash_altMasterSliderAttachment;

	Slider crash_mainMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> crash_mainMasterSliderAttachment;

	Slider tom1MasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tom1MasterSliderAttachment;

	Slider tom1RoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tom1RoomSliderAttachment;

	Slider tom1DirectSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tom1DirectSliderAttachment;

	Slider tom2MasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tom2MasterSliderAttachment;

	Slider tom2RoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tom2RoomSliderAttachment;

	Slider tom2DirectSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tom2DirectSliderAttachment;

	Slider tom3MasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tom3MasterSliderAttachment;

	Slider tom3RoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tom3RoomSliderAttachment;

	Slider tom3DirectSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tom3DirectSliderAttachment;

	Slider hi_hatRoomSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> hi_hatRoomSliderAttachment;

	Slider hi_hatMasterSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> hi_hatMasterSliderAttachment;

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
