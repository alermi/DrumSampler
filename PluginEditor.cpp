/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

//==============================================================================
DrumSamplerAudioProcessorEditor::DrumSamplerAudioProcessorEditor (DrumSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(740, 200);
	
	masterPanel.attach(&processor.parameters);
	addAndMakeVisible(masterPanel);
}

DrumSamplerAudioProcessorEditor::~DrumSamplerAudioProcessorEditor()
{
}
void DrumSamplerAudioProcessorEditor::createRotarySlider(Slider& slider, ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>& sliderAttachment, String parameterID) {
	slider.setRange(0, 1);
	slider.setSliderStyle(Slider::RotaryVerticalDrag);
	slider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	sliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, parameterID, slider);
	addAndMakeVisible(&slider);
}

//==============================================================================
void DrumSamplerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	
	//TODO: Set the backgroundColour with lookAndFeel
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	g.fillAll(Colours::black);
	g.setColour (Colours::white);
	Font instrumentFont(15, 1);

	getLookAndFeel().setColour(Slider::thumbColourId, Colours::white);

	g.setFont(instrumentFont);

}

void DrumSamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.

	//left top width height
	//kickMasterSlider.setBounds(14, 50, 40, 40);
	
	auto r = getLocalBounds();

	masterPanel.setBounds(r.removeFromTop(200));
	//drumImage.setBounds(0, 0, 740, 500);
	//testMaster.setBounds(0,400,740,200);
}
void DrumSamplerAudioProcessorEditor::drawPanSliders(Slider& monoSlider, Slider& stereoLSlider, Slider& stereoRSlider, int x, int y) {
	monoSlider.setBounds(x, y, 40, 40);
	stereoLSlider.setBounds(x-10, y+20, 40, 40);
	stereoRSlider.setBounds(x+10, y+20, 40, 40);
}