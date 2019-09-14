/*
  ==============================================================================

    InstrumentControl.cpp
    Created: 12 Sep 2019 1:24:38pm
    Author:  Ani

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "InstrumentControl.h"

//==============================================================================
InstrumentControl::InstrumentControl()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	groupComponent.reset(new GroupComponent("new group",
		TRANS("Instrument")));
	addAndMakeVisible(groupComponent.get());

	groupComponent->setBounds(0, 0, 100, 200);

	//volumeSlider.reset(new Slider("Volume Slider"));
	addAndMakeVisible(&volumeSlider);
	volumeSlider.setRange(0, 1, 0);
	volumeSlider.setSliderStyle(Slider::LinearVertical);
	volumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
	//volumeSlider->setColour(Slider::thumbColourId, Colours::white);

	volumeSlider.setBounds(72, 60, 24, 126);

	//leftPan.reset(new Slider("Left Pan"));
	addAndMakeVisible(&leftPan);
	leftPan.setRange(0, 1, 0);
	leftPan.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	leftPan.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
	//leftPan->addListener(this);

	leftPan.setBounds(36, 32, 32, 32);

	//rightPan.reset(new Slider("Right Pan"));
	addAndMakeVisible(&rightPan);
	rightPan.setRange(0, 1, 0);
	rightPan.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	rightPan.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
	//rightPan->addListener(this);

	rightPan.setBounds(52, 32, 32, 32);

	//monoPan.reset(new Slider("Mono Pan"));
	addAndMakeVisible(&monoPan);
	monoPan.setRange(0, 1, 0);
	monoPan.setSliderStyle(Slider::LinearHorizontal);
	monoPan.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
	//monoPan->addListener(this);

	monoPan.setBounds(36, 24, 48, 8);

	addAndMakeVisible(&panLabel);
	panLabel.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	panLabel.setJustificationType(Justification::centredLeft);
	panLabel.setEditable(false, false, false);
	panLabel.setColour(TextEditor::textColourId, Colours::black);
	panLabel.setText(TRANS("Pan:"), NotificationType::dontSendNotification);

	panLabel.setBounds(0, 24, 40, 24);

	addAndMakeVisible(&overheadLabel);
	overheadLabel.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	overheadLabel.setJustificationType(Justification::centredLeft);
	overheadLabel.setEditable(false, false, false);
	overheadLabel.setColour(TextEditor::textColourId, Colours::black);
	overheadLabel.setText(TRANS("OH:"), NotificationType::dontSendNotification);

	overheadLabel.setBounds(0, 64, 72, 24);

	addAndMakeVisible(&roomLabel);
	roomLabel.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	roomLabel.setJustificationType(Justification::centredLeft);
	roomLabel.setEditable(false, false, false);
	roomLabel.setColour(TextEditor::textColourId, Colours::black);
	roomLabel.setText(TRANS("Room:"), NotificationType::dontSendNotification);

	roomLabel.setBounds(0, 88, 56, 24);

	addAndMakeVisible(&directLabel);
	directLabel.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	directLabel.setJustificationType(Justification::centredLeft);
	directLabel.setEditable(false, false, false);
	directLabel.setColour(TextEditor::textColourId, Colours::black);
	directLabel.setText(TRANS("Direct:"), NotificationType::dontSendNotification);

	directLabel.setBounds(0, 112, 56, 24);

	addAndMakeVisible(&volumeLabel);
	volumeLabel.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	volumeLabel.setJustificationType(Justification::centredLeft);
	volumeLabel.setEditable(false, false, false);
	volumeLabel.setColour(TextEditor::textColourId, Colours::black);
	volumeLabel.setText(TRANS("Volume:"), NotificationType::dontSendNotification);
	
	volumeLabel.setBounds(16, 160, 64, 24);


	addAndMakeVisible(&overheadSlider);
	overheadSlider.setRange(0, 1, 0);
	overheadSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	overheadSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);

	overheadSlider.setBounds(45, 56, 32, 40);


	addAndMakeVisible(&roomSlider);
	roomSlider.setRange(0, 1, 0);
	roomSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	roomSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);

	roomSlider.setBounds(45, 80, 32, 40);

	addAndMakeVisible(&directSlider);
	directSlider.setRange(0, 1, 0);
	directSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	directSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);

	directSlider.setBounds(45, 104, 32, 40);
	//[UserPreSize]
	//[/UserPreSize]

	setSize(100, 200);
}

InstrumentControl::~InstrumentControl()
{

	groupComponent = nullptr;
	//volumeSlider = nullptr;
	//leftPan = nullptr;
	//rightPan = nullptr;
	//monoPan = nullptr;
}
void InstrumentControl::attach(AudioProcessorValueTreeState* parameters, String instrumentName) {
	volumeSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, instrumentName+" Master Mix", volumeSlider);
	monoPanSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, instrumentName + " Mono Pan", monoPan);
	stereoPanLSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, instrumentName + " Stereo Pan L", leftPan);
	stereoPanRSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, instrumentName + " Stereo Pan R", rightPan);

	overheadSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, instrumentName + " Overhead Mix", overheadSlider);
	roomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, instrumentName + " Room Mix", roomSlider);
	directSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, instrumentName + " Direct Mix", directSlider);

	groupComponent.get()->setText(instrumentName);
}
void InstrumentControl::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background



}

void InstrumentControl::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
