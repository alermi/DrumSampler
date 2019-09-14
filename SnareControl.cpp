/*
  ==============================================================================

    SnareControl.cpp
    Created: 14 Sep 2019 1:59:02am
    Author:  Ani

  ==============================================================================
*/

#include "SnareControl.h"

//==============================================================================
SnareControl::SnareControl()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	addAndMakeVisible(&topBottomSlider);
	topBottomSlider.setRange(0, 10, 0);
	topBottomSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	topBottomSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);

	topBottomSlider.setBounds(50, 128, 32, 40);

	topBottomLabel.setText(TRANS("Bottom/Top:"), NotificationType::dontSendNotification);
	addAndMakeVisible(&topBottomLabel);
	//topBottomLabel.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	topBottomLabel.setJustificationType(Justification::centredLeft);
	topBottomLabel.setEditable(false, false, false);
	topBottomLabel.setColour(TextEditor::textColourId, Colours::black);
	topBottomLabel.setFont(Font(11.90f, Font::plain).withTypefaceStyle("Regular").withExtraKerningFactor(-0.092f));

	topBottomLabel.setBounds(0, 136, 60, 24);
}

SnareControl::~SnareControl()
{
}

void SnareControl::attach(AudioProcessorValueTreeState* parameters, String instrumentName) {
	InstrumentControl::attach(parameters, instrumentName);
	topBottomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, instrumentName + " Bottom Mix", topBottomSlider);
}
void SnareControl::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background


}

void SnareControl::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
