 /*
  ==============================================================================

    MasterPanel.h
    Created: 12 Sep 2019 2:36:19pm
    Author:  Ani

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "InstrumentControl.h"
#include "KickControl.h"
//==============================================================================
/*
*/
class MasterPanel    : public Component
{
public:
    MasterPanel();
    ~MasterPanel();
	KickControl kickMaster;
	InstrumentControl snareMaster;
	InstrumentControl tom1Master;
	InstrumentControl tom2Master;
	InstrumentControl tom3Master;

	void MasterPanel::attach(AudioProcessorValueTreeState* parameters);
    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterPanel)
};