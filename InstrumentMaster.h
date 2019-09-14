/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InstrumentMaster  : public Component,
                          public Slider::Listener
{
public:
    //==============================================================================
    InstrumentMaster ();
    ~InstrumentMaster();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* m_png;
    static const int m_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> groupComponent;
    std::unique_ptr<Slider> volumeSlider;
    std::unique_ptr<Slider> leftPan;
    std::unique_ptr<Slider> rightPan;
    std::unique_ptr<Slider> monoPan;
    std::unique_ptr<Label> label;
    std::unique_ptr<Label> label2;
    std::unique_ptr<Slider> masterSlider;
    std::unique_ptr<Slider> roomSlider;
    std::unique_ptr<GroupComponent> groupComponent2;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Label> label4;
    std::unique_ptr<Label> label5;
    std::unique_ptr<Slider> slider;
    std::unique_ptr<Slider> slider2;
    std::unique_ptr<Slider> slider3;
    std::unique_ptr<Label> label6;
    std::unique_ptr<Slider> slider4;
    std::unique_ptr<Label> label7;
    std::unique_ptr<Label> label8;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentMaster)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

