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
	

	setSize(400, 400);

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

	snareMasterSlider.setRange(0, 1);
	snareMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	snareMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	snareMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Snare Master Mix", snareMasterSlider);
	addAndMakeVisible(&snareMasterSlider);

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

	floor_tomMasterSlider.setRange(0, 1);
	floor_tomMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	floor_tomMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	floor_tomMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Floor_Tom Master Mix", floor_tomMasterSlider);
	addAndMakeVisible(&floor_tomMasterSlider);

	floor_tomRoomSlider.setRange(0, 1);
	floor_tomRoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	floor_tomRoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	floor_tomRoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Floor_Tom Room Mix", floor_tomRoomSlider);
	addAndMakeVisible(&floor_tomRoomSlider);

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

	rack_tomMasterSlider.setRange(0, 1);
	rack_tomMasterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	rack_tomMasterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	rack_tomMasterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Rack_Tom Master Mix", rack_tomMasterSlider);
	addAndMakeVisible(&rack_tomMasterSlider);

	rack_tomRoomSlider.setRange(0, 1);
	rack_tomRoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	rack_tomRoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	rack_tomRoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Rack_Tom Room Mix", rack_tomRoomSlider);
	addAndMakeVisible(&rack_tomRoomSlider);

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

	masterSlider.setRange(0, 1);
	masterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	masterSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	masterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Master Mix", masterSlider);
	addAndMakeVisible(&masterSlider);

	masterRoomSlider.setRange(0, 1);
	masterRoomSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	masterRoomSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
	masterRoomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "Master Room Mix", masterRoomSlider);
	addAndMakeVisible(&masterRoomSlider);
}

DrumSamplerAudioProcessorEditor::~DrumSamplerAudioProcessorEditor()
{
	

	
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
	g.drawText("Snare:", 205, 20, 60, 20, Justification::left);
	g.drawText("China:", 205, 90, 60, 20, Justification::left);
	g.drawText("Crash 1:", 5, 160, 60, 20, Justification::left);
	g.drawText("Crash 2", 205, 160, 60, 20, Justification::left);
	g.drawText("Rack Tom:", 5, 230, 80, 20, Justification::left);
	g.drawText("Floor Tom", 205, 230, 80, 20, Justification::left);
	g.drawText("Ride:", 5, 300, 80, 20, Justification::left);
	g.setFont(10);
	g.drawText("Master:", 3, 38, 60, 20, Justification::left);
	g.drawText("Room Mix:", 53, 38, 60, 20, Justification::left);
	g.drawText("Master:", 203, 38, 60, 20, Justification::left);
	g.drawText("Room Mix:", 253, 38, 60, 20, Justification::left);
	g.drawText("Bottom/Top Mix:", 313, 38, 80, 20, Justification::left);
	g.drawText("Master:", 3, 108, 60, 20, Justification::left);
	g.drawText("Room Mix:", 53, 108, 60, 20, Justification::left);
	g.drawText("Master:", 203, 108, 60, 20, Justification::left);
	g.drawText("Master:", 3, 178, 60, 20, Justification::left);
	g.drawText("Master:", 203, 178, 60, 20, Justification::left);
	g.drawText("Master:", 3, 248, 60, 20, Justification::left);
	g.drawText("Room Mix:", 53, 248, 60, 20, Justification::left);
	g.drawText("Master:", 203, 248, 60, 20, Justification::left);
	g.drawText("Room Mix:", 253, 248, 60, 20, Justification::left);
	g.drawText("Master:", 3, 318, 60, 20, Justification::left);
	g.drawText("Room Master Mix:", 160, 300, 100, 40, Justification::left);
	g.drawText("Master Volume:", 160, 330, 100, 40, Justification::left);
} 

void DrumSamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
	
	
	kickMasterSlider.setBounds(14, 50, 40, 40);//left top width height
	kickRoomSlider.setBounds(64, 50, 40, 40);
	snareMasterSlider.setBounds(214, 50, 40, 40);
	snareRoomSlider.setBounds(264, 50, 40, 40);
	snareBottomSlider.setBounds(324, 50, 40, 40);
	hi_hatMasterSlider.setBounds(14, 120, 40, 40);
	hi_hatRoomSlider.setBounds(64, 120, 40, 40);
	chinaMasterSlider.setBounds(214, 120, 40, 40);
	crash_mainMasterSlider.setBounds(14, 190, 40, 40);
	crash_altMasterSlider.setBounds(214, 190, 40, 40);

	rack_tomMasterSlider.setBounds(14, 260, 40, 40);
	rack_tomRoomSlider.setBounds(64, 260, 40, 40);
	floor_tomMasterSlider.setBounds(214, 260, 40, 40);
	floor_tomRoomSlider.setBounds(264, 260, 40, 40);
	rideMasterSlider.setBounds(14, 330, 40, 40);
	
	
	
	
	masterRoomSlider.setBounds(244, 300, 40, 40);
	masterSlider.setBounds(244, 330, 40, 40);
}
