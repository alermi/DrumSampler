/*
  ==============================================================================

    MasterPanel.cpp
    Created: 12 Sep 2019 2:36:19pm
    Author:  Ani

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MasterPanel.h"

//==============================================================================
MasterPanel::MasterPanel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	setSize(500, 200);
}

MasterPanel::~MasterPanel()
{
}

void MasterPanel::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

	addAndMakeVisible(&kickMaster);
	addAndMakeVisible(&snareMaster);
	addAndMakeVisible(&tom1Master);
	addAndMakeVisible(&tom2Master);
	addAndMakeVisible(&tom3Master);


}
void MasterPanel::attach(AudioProcessorValueTreeState* parameters) {
	kickMaster.attach(parameters, "Kick");
	snareMaster.attach(parameters, "Snare");
	tom1Master.attach(parameters, "Tom1");
	tom2Master.attach(parameters, "Tom2");
	tom3Master.attach(parameters, "Tom3");



}

void MasterPanel::resized()
{
	auto r = getLocalBounds();
	kickMaster.setBounds(r.removeFromLeft(100));
	snareMaster.setBounds(r.removeFromLeft(100));
	tom1Master.setBounds(r.removeFromLeft(100));
	tom2Master.setBounds(r.removeFromLeft(100));
	tom3Master.setBounds(r.removeFromLeft(100));

    // This method is where you should set the bounds of any child
    // components that your component contains..

}
