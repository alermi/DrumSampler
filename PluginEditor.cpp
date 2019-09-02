/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DrumSamplerAudioProcessorEditor::DrumSamplerAudioProcessorEditor (DrumSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	

	setSize(600, 500);

	kickRoomSlider.setRange(0, 1);
	kickRoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	kickRoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	kickRoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Kick Room Mix", kickRoomSlider);
	addAndMakeVisible(&kickRoomSlider);

	kickMasterSlider.setRange(0, 1);
	kickMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	kickMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	kickMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Kick Master Mix", kickMasterSlider);
	addAndMakeVisible(&kickMasterSlider);

	kickOverheadSlider.setRange(0, 1);
	kickOverheadSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	kickOverheadSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	kickOverheadSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Kick Overhead Mix", kickOverheadSlider);
	addAndMakeVisible(&kickOverheadSlider);

	kickInOutSlider.setRange(0, 1);
	kickInOutSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	kickInOutSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	kickInOutSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Kick In/Out Mix", kickInOutSlider);
	addAndMakeVisible(&kickInOutSlider);

	kickDirectSlider.setRange(0, 1);
	kickDirectSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	kickDirectSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	kickDirectSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Kick Direct Mix", kickDirectSlider);
	addAndMakeVisible(&kickDirectSlider);

	snareRoomSlider.setRange(0, 1);
	snareRoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	snareRoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	snareRoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Snare Room Mix", snareRoomSlider);
	addAndMakeVisible(&snareRoomSlider);

	snareBottomSlider.setRange(0, 1);
	snareBottomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	snareBottomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	snareBottomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Snare Bottom Mix", snareBottomSlider);
	addAndMakeVisible(&snareBottomSlider);

	snareOverheadSlider.setRange(0, 1);
	snareOverheadSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	snareOverheadSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	snareOverheadSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Snare Overhead Mix", snareOverheadSlider);
	addAndMakeVisible(&snareOverheadSlider);

	snareMasterSlider.setRange(0, 1);
	snareMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	snareMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	snareMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Snare Master Mix", snareMasterSlider);
	addAndMakeVisible(&snareMasterSlider);

	snareDirectSlider.setRange(0, 1);
	snareDirectSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	snareDirectSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	snareDirectSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Snare Direct Mix", snareDirectSlider);
	addAndMakeVisible(&snareDirectSlider);

	chinaMasterSlider.setRange(0, 1);
	chinaMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	chinaMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	chinaMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "China Master Mix", chinaMasterSlider);
	addAndMakeVisible(&chinaMasterSlider);

	crash_altMasterSlider.setRange(0, 1);
	crash_altMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	crash_altMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	crash_altMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Crash_Alt Master Mix", crash_altMasterSlider);
	addAndMakeVisible(&crash_altMasterSlider);

	crash_mainMasterSlider.setRange(0, 1);
	crash_mainMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	crash_mainMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	crash_mainMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Crash_Main Master Mix", crash_mainMasterSlider);
	addAndMakeVisible(&crash_mainMasterSlider);

	tom1MasterSlider.setRange(0, 1);
	tom1MasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	tom1MasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	tom1MasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Tom1 Master Mix", tom1MasterSlider);
	addAndMakeVisible(&tom1MasterSlider);

	tom1RoomSlider.setRange(0, 1);
	tom1RoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	tom1RoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	tom1RoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Tom1 Room Mix", tom1RoomSlider);
	addAndMakeVisible(&tom1RoomSlider);

	tom1DirectSlider.setRange(0, 1);
	tom1DirectSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	tom1DirectSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	tom1DirectSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Tom1 Direct Mix", tom1DirectSlider);
	addAndMakeVisible(&tom1DirectSlider);

	tom2MasterSlider.setRange(0, 1);
	tom2MasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	tom2MasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	tom2MasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Tom2 Master Mix", tom2MasterSlider);
	addAndMakeVisible(&tom2MasterSlider);

	tom2RoomSlider.setRange(0, 1);
	tom2RoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	tom2RoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	tom2RoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Tom2 Room Mix", tom2RoomSlider);
	addAndMakeVisible(&tom2RoomSlider);

	tom2DirectSlider.setRange(0, 1);
	tom2DirectSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	tom2DirectSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	tom2DirectSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Tom2 Direct Mix", tom2DirectSlider);
	addAndMakeVisible(&tom2DirectSlider);

	tom3MasterSlider.setRange(0, 1);
	tom3MasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	tom3MasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	tom3MasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Tom3 Master Mix", tom3MasterSlider);
	addAndMakeVisible(&tom3MasterSlider);

	tom3RoomSlider.setRange(0, 1);
	tom3RoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	tom3RoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	tom3RoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Tom3 Room Mix", tom3RoomSlider);
	addAndMakeVisible(&tom3RoomSlider);

	tom3DirectSlider.setRange(0, 1);
	tom3DirectSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	tom3DirectSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	tom3DirectSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Tom3 Direct Mix", tom3DirectSlider);
	addAndMakeVisible(&tom3DirectSlider);

	hi_hatRoomSlider.setRange(0, 1);
	hi_hatRoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	hi_hatRoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	hi_hatRoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Hi_Hat Room Mix", hi_hatRoomSlider);
	addAndMakeVisible(&hi_hatRoomSlider);

	hi_hatMasterSlider.setRange(0, 1);
	hi_hatMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	hi_hatMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	hi_hatMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Hi_Hat Master Mix", hi_hatMasterSlider);
	addAndMakeVisible(&hi_hatMasterSlider);


	rideMasterSlider.setRange(0, 1);
	rideMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	rideMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	rideMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Ride Master Mix", rideMasterSlider);
	addAndMakeVisible(&rideMasterSlider);

	stackMasterSlider.setRange(0, 1);
	stackMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	stackMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	stackMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Stack Master Mix", stackMasterSlider);
	addAndMakeVisible(&stackMasterSlider);

	createRotarySlider(masterSlider, masterSliderAttachment, "Master Mix");
	createRotarySlider(masterRoomSlider, masterRoomSliderAttachment, "Master Room Mix");

	createRotarySlider(kickMonoPanSlider, kickMonoPanSliderAttachment, "Kick Mono Pan");
	createRotarySlider(kickStereoPanLSlider, kickStereoPanLSliderAttachment, "Kick Stereo Pan L");
	createRotarySlider(kickStereoPanRSlider, kickStereoPanRSliderAttachment, "Kick Stereo Pan R");
	//masterSlider.setRange(0, 1);
	//masterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	//masterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	//masterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Master Mix", masterSlider);
	//addAndMakeVisible(&masterSlider);

	//masterRoomSlider.setRange(0, 1);
	//masterRoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	//masterRoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	//masterRoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Master Room Mix", masterRoomSlider);
	//addAndMakeVisible(&masterRoomSlider);
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
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
	Font instrumentFont(15, 1);
	g.setFont(instrumentFont);
	g.drawText("Kick:", 5, 20, 60, 20,Justification::left);
	g.drawText("Hi-Hat:", 5, 90, 60, 20, Justification::left);
	g.drawText("Snare:", 305, 20, 60, 20, Justification::left);
	g.drawText("China:", 305, 90, 60, 20, Justification::left);
	g.drawText("Crash 1:", 5, 160, 60, 20, Justification::left);
	g.drawText("Crash 2", 305, 160, 60, 20, Justification::left);
	g.drawText("Tom1:", 5, 230, 80, 20, Justification::left);
	g.drawText("Tom2", 305, 230, 80, 20, Justification::left);
	g.drawText("Ride:", 5, 300, 80, 20, Justification::left);
	g.drawText("Tom3", 305, 300, 80, 20, Justification::left);
	g.setFont(10);
	g.drawText("Master:", 3, 38, 60, 20, Justification::left);
	g.drawText("Room Mix:", 53, 38, 60, 20, Justification::left);
	g.drawText("OH Mix:", 113, 38, 60, 20, Justification::left);
	g.drawText("In/Out Mix:", 153, 38, 60, 20, Justification::left);
	g.drawText("Direct Mix:", 213, 38, 60, 20, Justification::left);

	g.drawText("Master:", 303, 38, 60, 20, Justification::left);
	g.drawText("Room Mix:", 353, 38, 60, 20, Justification::left);
	g.drawText("Bottom/Top:", 413, 38, 80, 20, Justification::left);
	g.drawText("OH Mix:", 483, 38, 60, 20, Justification::left);
	g.drawText("Direct Mix:", 513, 38, 60, 20, Justification::left);

	g.drawText("Master:", 3, 108, 60, 20, Justification::left);
	g.drawText("Room Mix:", 53, 108, 60, 20, Justification::left);
	g.drawText("Master:", 303, 108, 60, 20, Justification::left);
	g.drawText("Master:", 3, 178, 60, 20, Justification::left);
	g.drawText("Master:", 303, 178, 60, 20, Justification::left);

	g.drawText("Master:", 3, 248, 60, 20, Justification::left);
	g.drawText("Room Mix:", 53, 248, 60, 20, Justification::left);
	g.drawText("Direct Mix:", 103, 248, 60, 20, Justification::left);

	g.drawText("Master:", 303, 248, 60, 20, Justification::left);
	g.drawText("Room Mix:", 353, 248, 60, 20, Justification::left);
	g.drawText("Direct Mix:", 403, 248, 60, 20, Justification::left);

	g.drawText("Master:", 303, 318, 60, 20, Justification::left);
	g.drawText("Room Mix:", 353, 318, 60, 20, Justification::left);
	g.drawText("Direct Mix:", 403, 318, 60, 20, Justification::left);

	g.drawText("Master:", 3, 318, 60, 20, Justification::left);
	g.drawText("Room Master Mix:", 160, 400, 100, 40, Justification::left);
	g.drawText("Master Volume:", 160, 430, 100, 40, Justification::left);
}

void DrumSamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
	
	
	kickMasterSlider.setBounds(14, 50, 40, 40);//left top width height
	kickRoomSlider.setBounds(64, 50, 40, 40);
	kickOverheadSlider.setBounds(114, 50, 40, 40);
	kickInOutSlider.setBounds(164, 50, 40, 40);
	kickDirectSlider.setBounds(214, 50, 40, 40);
	kickMonoPanSlider.setBounds(264, 50, 40, 40);
	kickStereoPanLSlider.setBounds(254, 70, 40, 40);
	kickStereoPanRSlider.setBounds(274, 70, 40, 40);

	snareMasterSlider.setBounds(314, 50, 40, 40);
	snareRoomSlider.setBounds(364, 50, 40, 40);
	snareBottomSlider.setBounds(424, 50, 40, 40);
	snareOverheadSlider.setBounds(474, 50, 40, 40);
	snareDirectSlider.setBounds(524, 50, 40, 40);


	hi_hatMasterSlider.setBounds(14, 120, 40, 40);
	hi_hatRoomSlider.setBounds(64, 120, 40, 40);
	chinaMasterSlider.setBounds(314, 120, 40, 40);
	crash_mainMasterSlider.setBounds(14, 190, 40, 40);
	crash_altMasterSlider.setBounds(314, 190, 40, 40);

	tom1MasterSlider.setBounds(14, 260, 40, 40);
	tom1RoomSlider.setBounds(64, 260, 40, 40);
	tom1DirectSlider.setBounds(114, 260, 40, 40);

	tom2MasterSlider.setBounds(314, 260, 40, 40);
	tom2RoomSlider.setBounds(364, 260, 40, 40);
	tom2DirectSlider.setBounds(414, 260, 40, 40);

	tom3MasterSlider.setBounds(314, 330, 40, 40);
	tom3RoomSlider.setBounds(364, 330, 40, 40);
	tom3DirectSlider.setBounds(414, 330, 40, 40);

	rideMasterSlider.setBounds(14, 330, 40, 40);
	
	masterRoomSlider.setBounds(244, 400, 40, 40);
	masterSlider.setBounds(244, 430, 40, 40);
}
