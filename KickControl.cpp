/*
  ==============================================================================

    KickControl.cpp
    Created: 13 Sep 2019 1:15:37am
    Author:  Ani

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "KickControl.h"

//==============================================================================
KickControl::KickControl()
{
	InstrumentControl();
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	
	//inOutSlider.reset(new Slider("inOut"));
	addAndMakeVisible(inOutSlider);
	inOutSlider.setRange(0, 10, 0);
	inOutSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	inOutSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
	//inOutSlider.setColour(Slider::thumbColourId, Colours::white);
	//inOutSlider->addListener(this);

	inOutSlider.setBounds(48, 120, 32, 40);

	inOutLabel.setText(TRANS("In/Out:"), NotificationType::dontSendNotification);
	addAndMakeVisible(inOutLabel);
	inOutLabel.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	inOutLabel.setJustificationType(Justification::centredLeft);
	inOutLabel.setEditable(false, false, false);
	inOutLabel.setColour(TextEditor::textColourId, Colours::black);
	inOutLabel.setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	inOutLabel.setBounds(0, 128, 56, 24);
}

KickControl::~KickControl()
{
}

void KickControl::paint (Graphics& g)
{
	InstrumentControl::paint(g);

    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background



}
void KickControl::attach(AudioProcessorValueTreeState* parameters, String instrumentName) {
	InstrumentControl::attach(parameters, instrumentName);
	inOutSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, instrumentName + " In/Out Mix", inOutSlider);
}

void KickControl::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
