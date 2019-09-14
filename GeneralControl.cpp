/*
  ==============================================================================

    GeneralControl.cpp
    Created: 13 Sep 2019 7:57:40pm
    Author:  Ani

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GeneralControl.h"

//==============================================================================
GeneralControl::GeneralControl()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.


	setSize(240, 200);
	//label.reset(new Label("new label",
	//	TRANS("Room Volume")));
	addAndMakeVisible(&roomLabel);
	roomLabel.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	roomLabel.setJustificationType(Justification::centredLeft);
	roomLabel.setEditable(false, false, false);
	roomLabel.setColour(TextEditor::textColourId, Colours::black);
	roomLabel.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	roomLabel.setText(TRANS("Room Volume"),NotificationType::dontSendNotification);

	roomLabel.setBounds(16, 16, 96, 24);

	addAndMakeVisible(&masterLabel);
	masterLabel.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	masterLabel.setJustificationType(Justification::centredLeft);
	masterLabel.setEditable(false, false, false);
	masterLabel.setColour(TextEditor::textColourId, Colours::black);
	//masterLabel.setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	masterLabel.setText(TRANS("Master Volume"), NotificationType::dontSendNotification);

	masterLabel.setBounds(120, 16, 104, 24);

	//masterSlider.reset(new Slider("new slider"));
	addAndMakeVisible(masterSlider);
	masterSlider.setRange(0, 10, 0);
	masterSlider.setSliderStyle(Slider::LinearVertical);
	masterSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);

	masterSlider.setBounds(152, 40, 32, 144);

	//roomSlider.reset(new Slider("new slider"));
	addAndMakeVisible(roomSlider);
	roomSlider.setRange(0, 10, 0);
	roomSlider.setSliderStyle(Slider::LinearVertical);
	roomSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);

	roomSlider.setBounds(48, 40, 32, 144);


}
void GeneralControl::attach(AudioProcessorValueTreeState* parameters) {
	masterSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, "Master Mix", masterSlider);
	roomSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(*parameters, "Master Room Mix", roomSlider);
}
GeneralControl::~GeneralControl()
{
}

void GeneralControl::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background


}

void GeneralControl::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
