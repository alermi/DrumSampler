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
	volumeSlider.setRange(0, 10, 0);
	volumeSlider.setSliderStyle(Slider::LinearVertical);
	volumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
	//volumeSlider->setColour(Slider::thumbColourId, Colours::white);

	volumeSlider.setBounds(56, 40, 48, 144);

	//leftPan.reset(new Slider("Left Pan"));
	addAndMakeVisible(&leftPan);
	leftPan.setRange(0, 1, 0);
	leftPan.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	leftPan.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
	//leftPan->addListener(this);

	leftPan.setBounds(8, 160, 32, 32);

	//rightPan.reset(new Slider("Right Pan"));
	addAndMakeVisible(&rightPan);
	rightPan.setRange(0, 1, 0);
	rightPan.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	rightPan.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
	//rightPan->addListener(this);

	rightPan.setBounds(24, 160, 32, 32);

	//monoPan.reset(new Slider("Mono Pan"));
	addAndMakeVisible(&monoPan);
	monoPan.setRange(0, 10, 0);
	monoPan.setSliderStyle(Slider::LinearHorizontal);
	monoPan.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
	//monoPan->addListener(this);

	monoPan.setBounds(8, 152, 48, 8);


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
