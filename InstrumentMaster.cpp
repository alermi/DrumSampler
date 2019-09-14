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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "InstrumentMaster.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InstrumentMaster::InstrumentMaster ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    groupComponent.reset (new GroupComponent ("new group",
                                              TRANS("Instrument")));
    addAndMakeVisible (groupComponent.get());
    groupComponent->setTextLabelPosition (Justification::centred);
    groupComponent->setColour (GroupComponent::outlineColourId, Colours::white);

    groupComponent->setBounds (0, 0, 100, 200);

    volumeSlider.reset (new Slider ("Volume Slider"));
    addAndMakeVisible (volumeSlider.get());
    volumeSlider->setRange (0, 10, 0);
    volumeSlider->setSliderStyle (Slider::LinearVertical);
    volumeSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    volumeSlider->setColour (Slider::thumbColourId, Colours::white);

    volumeSlider->setBounds (72, 60, 24, 126);

    leftPan.reset (new Slider ("Left Pan"));
    addAndMakeVisible (leftPan.get());
    leftPan->setRange (0, 1, 0);
    leftPan->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    leftPan->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    leftPan->addListener (this);

    leftPan->setBounds (36, 32, 32, 32);

    rightPan.reset (new Slider ("Right Pan"));
    addAndMakeVisible (rightPan.get());
    rightPan->setRange (0, 1, 0);
    rightPan->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    rightPan->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    rightPan->addListener (this);

    rightPan->setBounds (52, 32, 32, 32);

    monoPan.reset (new Slider ("Mono Pan"));
    addAndMakeVisible (monoPan.get());
    monoPan->setRange (0, 10, 0);
    monoPan->setSliderStyle (Slider::LinearHorizontal);
    monoPan->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    monoPan->addListener (this);

    monoPan->setBounds (36, 24, 48, 8);

    label.reset (new Label ("new label",
                            TRANS("Room Volume")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (448, 288, 96, 24);

    label2.reset (new Label ("new label",
                             TRANS("Master Volume")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (552, 288, 104, 24);

    masterSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (masterSlider.get());
    masterSlider->setRange (0, 10, 0);
    masterSlider->setSliderStyle (Slider::LinearVertical);
    masterSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);

    masterSlider->setBounds (584, 312, 32, 144);

    roomSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (roomSlider.get());
    roomSlider->setRange (0, 10, 0);
    roomSlider->setSliderStyle (Slider::LinearVertical);
    roomSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);

    roomSlider->setBounds (480, 312, 32, 144);

    groupComponent2.reset (new GroupComponent ("new group",
                                               TRANS("group")));
    addAndMakeVisible (groupComponent2.get());

    groupComponent2->setBounds (432, 272, 240, 200);

    label3.reset (new Label ("new label",
                             TRANS("OH:")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (0, 64, 72, 24);

    label4.reset (new Label ("new label",
                             TRANS("Room:")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (0, 88, 56, 24);

    label5.reset (new Label ("new label",
                             TRANS("Top/Bottom:")));
    addAndMakeVisible (label5.get());
    label5->setFont (Font (11.90f, Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (-0.092f));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label5->setBounds (0, 136, 60, 24);

    slider.reset (new Slider ("new slider"));
    addAndMakeVisible (slider.get());
    slider->setRange (0, 10, 0);
    slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider->addListener (this);

    slider->setBounds (45, 56, 32, 40);

    slider2.reset (new Slider ("new slider"));
    addAndMakeVisible (slider2.get());
    slider2->setRange (0, 10, 0);
    slider2->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    slider2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider2->addListener (this);

    slider2->setBounds (45, 80, 32, 40);

    slider3.reset (new Slider ("new slider"));
    addAndMakeVisible (slider3.get());
    slider3->setRange (0, 10, 0);
    slider3->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    slider3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider3->addListener (this);

    slider3->setBounds (50, 128, 32, 40);

    label6.reset (new Label ("new label",
                             TRANS("Direct:")));
    addAndMakeVisible (label6.get());
    label6->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label6->setBounds (0, 112, 56, 24);

    slider4.reset (new Slider ("new slider"));
    addAndMakeVisible (slider4.get());
    slider4->setRange (0, 10, 0);
    slider4->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    slider4->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider4->addListener (this);

    slider4->setBounds (45, 104, 32, 40);

    label7.reset (new Label ("new label",
                             TRANS("Pan:")));
    addAndMakeVisible (label7.get());
    label7->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label7->setBounds (0, 24, 40, 24);

    label8.reset (new Label ("new label",
                             TRANS("Volume:")));
    addAndMakeVisible (label8.get());
    label8->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label8->setBounds (0, 160, 64, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (100, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InstrumentMaster::~InstrumentMaster()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    volumeSlider = nullptr;
    leftPan = nullptr;
    rightPan = nullptr;
    monoPan = nullptr;
    label = nullptr;
    label2 = nullptr;
    masterSlider = nullptr;
    roomSlider = nullptr;
    groupComponent2 = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    label5 = nullptr;
    slider = nullptr;
    slider2 = nullptr;
    slider3 = nullptr;
    label6 = nullptr;
    slider4 = nullptr;
    label7 = nullptr;
    label8 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InstrumentMaster::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InstrumentMaster::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void InstrumentMaster::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == leftPan.get())
    {
        //[UserSliderCode_leftPan] -- add your slider handling code here..
        //[/UserSliderCode_leftPan]
    }
    else if (sliderThatWasMoved == rightPan.get())
    {
        //[UserSliderCode_rightPan] -- add your slider handling code here..
        //[/UserSliderCode_rightPan]
    }
    else if (sliderThatWasMoved == monoPan.get())
    {
        //[UserSliderCode_monoPan] -- add your slider handling code here..
        //[/UserSliderCode_monoPan]
    }
    else if (sliderThatWasMoved == slider.get())
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }
    else if (sliderThatWasMoved == slider2.get())
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        //[/UserSliderCode_slider2]
    }
    else if (sliderThatWasMoved == slider3.get())
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        //[/UserSliderCode_slider3]
    }
    else if (sliderThatWasMoved == slider4.get())
    {
        //[UserSliderCode_slider4] -- add your slider handling code here..
        //[/UserSliderCode_slider4]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InstrumentMaster" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="100" initialHeight="200">
  <BACKGROUND backgroundColour="ff000000"/>
  <GROUPCOMPONENT name="new group" id="7ee8d04f4c8e4fba" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 0 100 200" outlinecol="ffffffff"
                  title="Instrument" textpos="36"/>
  <SLIDER name="Volume Slider" id="293520ce5caabac1" memberName="volumeSlider"
          virtualName="" explicitFocusOrder="0" pos="72 60 24 126" thumbcol="ffffffff"
          min="0.0" max="10.0" int="0.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Left Pan" id="d7aafd3f9c831cb9" memberName="leftPan" virtualName=""
          explicitFocusOrder="0" pos="36 32 32 32" min="0.0" max="1.0"
          int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Right Pan" id="e099e87addeb9178" memberName="rightPan"
          virtualName="" explicitFocusOrder="0" pos="52 32 32 32" min="0.0"
          max="1.0" int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Mono Pan" id="d01de9b44ba53c48" memberName="monoPan" virtualName=""
          explicitFocusOrder="0" pos="36 24 48 8" min="0.0" max="10.0"
          int="0.0" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="new label" id="449ec999673fcd23" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="448 288 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Room Volume" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5fd1103a839fd213" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="552 288 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Master Volume" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="c98cceaa2bedb41e" memberName="masterSlider"
          virtualName="" explicitFocusOrder="0" pos="584 312 32 144" min="0.0"
          max="10.0" int="0.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="new slider" id="dc9f87689d7b8cb" memberName="roomSlider"
          virtualName="" explicitFocusOrder="0" pos="480 312 32 144" min="0.0"
          max="10.0" int="0.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <GROUPCOMPONENT name="new group" id="c9bfa9edb5dfee91" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="432 272 240 200" title="group"/>
  <LABEL name="new label" id="d422bc04e70f0ab7" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="0 64 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="OH:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e79a3be223180a1" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="0 88 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Room:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e4ed6c55f979fbce" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="0 136 60 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Top/Bottom:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11.9" kerning="-0.092" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="3f6a8280e374db2f" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="45 56 32 40" min="0.0" max="10.0"
          int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="161ea416e09cac1" memberName="slider2" virtualName=""
          explicitFocusOrder="0" pos="45 80 32 40" min="0.0" max="10.0"
          int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="a8adbaaf31c31da5" memberName="slider3"
          virtualName="" explicitFocusOrder="0" pos="50 128 32 40" min="0.0"
          max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="ca5a175a39d34a0c" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="0 112 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Direct:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="26530b188fcff613" memberName="slider4"
          virtualName="" explicitFocusOrder="0" pos="45 104 32 40" min="0.0"
          max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="a67df8fdccf81427" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="0 24 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pan:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="474e8b7cf1d5a9b5" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="0 160 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Volume:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: m_png, 1616, "m.png"
static const unsigned char resource_InstrumentMaster_m_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,225,0,0,0,225,8,3,0,0,0,9,109,34,72,0,0,0,123,80,76,84,69,255,255,255,0,0,0,75,75,75,
220,220,220,97,97,97,207,207,207,248,248,248,108,108,108,225,225,225,143,143,143,228,228,228,202,202,202,174,174,174,235,235,235,70,70,70,216,216,216,188,188,188,34,34,34,180,180,180,152,152,152,119,119,
119,59,59,59,126,126,126,169,169,169,87,87,87,102,102,102,145,145,145,205,205,205,111,111,111,234,234,234,156,156,156,163,163,163,19,19,19,54,54,54,42,42,42,28,28,28,82,82,82,11,11,11,135,135,135,195,
195,195,40,40,40,0,1,238,15,0,0,5,144,73,68,65,84,120,156,237,157,233,90,19,65,16,69,11,130,44,97,137,34,40,178,168,136,219,251,63,161,178,24,66,250,118,87,205,116,77,234,202,87,247,231,116,79,87,159,
108,103,50,171,72,38,147,201,100,50,153,76,38,147,201,100,50,153,76,38,147,201,100,50,153,215,158,253,243,237,118,78,38,40,122,168,20,61,249,224,88,108,182,165,229,151,99,181,167,236,104,53,119,28,139,
233,132,158,213,30,179,187,209,154,58,225,214,174,99,185,135,124,97,35,252,232,88,238,33,223,216,8,111,29,203,25,75,110,152,112,107,223,177,222,223,124,224,35,252,233,88,239,111,12,21,55,77,184,229,88,
79,228,45,35,161,171,18,47,24,9,63,57,22,212,101,24,65,232,169,68,93,134,33,132,142,74,252,205,73,232,167,196,133,169,222,230,9,253,148,104,144,97,12,161,155,18,109,229,2,8,189,148,104,145,97,16,225,161,
79,185,239,188,132,62,74,60,54,86,139,32,244,81,226,103,26,194,243,114,145,139,18,223,153,74,109,130,240,168,92,228,161,68,32,195,51,184,207,102,122,194,217,73,185,204,65,137,103,229,168,11,248,219,51,
61,225,226,180,92,118,208,95,12,84,146,237,24,194,55,112,50,189,1,50,60,136,35,220,43,23,118,43,17,192,204,227,8,15,203,133,189,74,4,50,60,135,216,155,33,68,31,211,78,37,190,47,71,60,138,36,60,40,151,
118,42,241,14,190,102,113,132,243,114,105,159,18,223,148,3,238,73,36,161,128,141,141,46,37,2,25,222,255,118,5,18,130,237,154,46,37,130,50,247,139,3,9,157,149,88,219,134,136,36,244,85,34,216,14,156,223,
47,143,36,116,85,34,150,161,196,18,186,42,17,203,80,130,9,47,203,134,209,74,252,90,142,245,216,16,74,232,168,196,138,12,37,152,16,41,113,62,174,204,117,57,210,213,99,75,44,161,155,18,193,225,152,31,79,
77,177,132,110,74,4,50,188,124,106,10,38,244,82,98,77,134,18,78,120,85,54,141,81,226,77,57,204,242,84,171,96,66,249,81,182,141,80,34,208,206,209,191,182,104,194,214,220,236,1,175,211,178,45,154,16,124,
190,134,43,17,124,214,175,151,141,209,132,173,223,8,115,192,239,213,213,178,49,156,208,65,137,13,25,10,1,161,131,18,193,139,116,249,220,26,79,8,182,183,6,42,17,108,251,221,60,183,198,19,118,43,17,108,
191,175,158,119,28,79,216,173,68,176,91,242,116,165,153,128,176,87,137,96,248,213,102,2,194,78,37,130,125,33,215,171,237,4,132,157,74,252,164,140,206,64,216,117,44,17,200,240,235,139,14,12,132,93,74,108,
203,80,72,8,123,148,120,91,174,123,243,162,3,5,33,216,141,100,85,226,126,185,234,218,69,56,20,132,29,74,84,100,40,44,132,213,221,185,106,192,216,107,61,56,8,129,18,207,77,163,107,50,20,22,194,209,74,212,
100,40,52,132,35,149,168,202,80,104,8,71,42,241,99,185,214,251,245,62,44,132,227,148,120,91,174,117,179,222,135,133,112,148,18,117,25,10,15,33,58,58,166,42,241,103,185,206,105,209,137,134,112,140,18,193,
192,101,39,26,194,17,74,252,85,174,114,86,246,162,33,196,167,221,53,3,206,141,181,141,27,68,56,88,137,22,25,10,19,225,96,37,130,75,184,10,25,10,21,97,229,172,173,106,192,245,204,133,12,133,138,176,126,
178,129,117,224,109,212,143,136,112,160,18,77,50,20,46,194,97,74,4,163,194,126,76,132,131,148,104,147,161,112,17,14,82,34,184,158,217,60,104,28,225,0,37,2,25,222,225,158,84,132,3,148,104,148,161,176,17,
218,149,8,46,225,58,198,61,185,8,205,74,180,202,80,216,8,43,23,20,148,1,215,51,67,25,10,29,33,184,66,18,42,17,12,89,155,0,25,97,245,92,230,151,1,151,112,97,25,10,29,161,81,137,102,25,226,17,67,9,225,5,
118,235,1,239,116,69,134,194,71,104,250,134,129,111,235,231,234,128,116,132,22,37,130,95,220,138,12,133,144,16,92,172,188,174,68,208,165,38,67,33,36,52,40,17,200,240,109,125,60,62,66,93,137,96,188,198,
4,248,8,85,37,14,145,161,48,18,162,155,119,204,149,246,69,99,56,66,66,240,30,173,158,63,50,72,134,66,73,168,124,207,6,201,80,56,9,129,18,159,79,106,70,123,228,234,50,20,78,194,166,18,65,227,247,230,4,
24,9,209,31,248,165,18,193,27,220,144,161,144,18,182,148,8,6,107,79,128,146,176,161,196,129,50,20,82,194,134,18,193,124,91,50,196,107,16,16,86,149,8,222,221,119,202,4,56,9,171,223,54,112,104,163,41,67,
161,37,4,127,31,30,148,8,78,98,108,202,80,104,9,43,74,4,251,83,219,50,20,90,194,138,18,7,203,80,120,9,177,18,193,72,234,4,88,9,161,18,193,177,41,253,17,0,172,132,72,137,199,195,101,40,196,132,64,137,224,
66,74,77,134,66,76,104,187,213,170,38,67,97,38,52,221,46,87,147,161,48,19,90,110,121,172,202,80,152,9,45,183,173,86,101,40,212,132,134,187,173,90,38,64,76,168,223,49,215,244,60,28,98,66,253,17,0,186,12,
133,155,80,187,115,245,111,211,4,152,9,53,37,126,49,13,66,77,168,40,209,32,67,33,39,108,43,241,194,54,1,106,194,182,18,45,50,20,118,194,230,211,56,140,19,224,38,108,41,209,250,112,56,110,194,150,18,103,
198,33,200,9,235,74,252,102,157,0,57,97,93,137,54,25,10,63,97,85,137,54,25,10,63,97,237,225,17,70,25,10,63,97,77,137,70,25,202,127,64,120,122,177,3,98,249,115,255,20,122,194,238,36,97,119,146,112,242,
36,97,119,146,112,242,36,97,119,146,112,242,36,97,119,146,112,242,36,97,119,146,112,242,36,97,119,146,112,242,36,97,119,146,112,242,36,97,119,146,112,242,36,97,119,146,112,242,36,97,119,94,63,33,62,235,
231,74,95,209,43,240,233,241,3,142,206,169,217,93,204,202,44,58,159,109,60,36,251,160,254,108,228,19,250,50,153,76,38,147,201,100,50,153,76,38,147,201,100,50,153,76,38,147,201,100,50,153,76,230,85,228,
15,132,72,83,2,148,158,226,222,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* InstrumentMaster::m_png = (const char*) resource_InstrumentMaster_m_png;
const int InstrumentMaster::m_pngSize = 1616;


//[EndFile] You can add extra defines here...
//[/EndFile]

