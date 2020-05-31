/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <ctime>

const int NUM_OF_SAME_SAMPLE = 5;

const int HI_HAT_SAMPLE_OFFSET = 32;
//==============================================================================


DrumSamplerAudioProcessor::DrumSamplerAudioProcessor()
	: parameters(*this, nullptr)
#ifndef JucePlugin_PreferredChannelConfigurations
     , AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                        .withOutput ("Master", AudioChannelSet::stereo(), true)
						.withOutput("Room Stereo", AudioChannelSet::stereo(), true)
						.withOutput("Overhead Stereo", AudioChannelSet::stereo(), true)
						.withOutput("Kick", AudioChannelSet::mono(), true)
						.withOutput("Snare", AudioChannelSet::mono(), true)
						.withOutput("Tom1", AudioChannelSet::mono(), true)
						.withOutput("Tom2", AudioChannelSet::mono(), true)
						.withOutput("Tom3", AudioChannelSet::mono(), true)


                     #endif
                       )
#endif
{
	
	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick Room Mix",       // parameter ID
		"Kick Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));
	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick In/Out Mix",       // parameter ID
		"Kick In/Out Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick Overhead Mix",       // parameter ID
		"Kick Overhead Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick Master Mix",       // parameter ID
		"Kick Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));
	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick Direct Mix",       // parameter ID
		"Kick Direct Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick Mono Pan",       // parameter ID
		"Kick Mono Pan",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));
	
	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick Stereo Pan L",       // parameter ID
		"Kick Stereo Pan L",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick Stereo Pan R",       // parameter ID
		"Kick Stereo Pan R",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		1.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Snare Room Mix",       // parameter ID
		"Snare Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Snare Bottom Mix",       // parameter ID
		"Snare Bottom Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Snare Master Mix",       // parameter ID
		"Snare Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.8f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Snare Overhead Mix",       // parameter ID
		"Snare Overhead Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Snare Direct Mix",       // parameter ID
		"Snare Direct Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Snare Mono Pan",       // parameter ID
		"Snare Mono Pan",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Snare Stereo Pan L",       // parameter ID
		"Snare Stereo Pan L",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Snare Stereo Pan R",       // parameter ID
		"Snare Stereo Pan R",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		1.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("China Master Mix",       // parameter ID
		"China Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.3f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Crash_Alt Master Mix",       // parameter ID
		"Crash_Alt Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.3f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Crash_Main Master Mix",       // parameter ID
		"Crash_Main Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.3f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Hi_Hat Master Mix",       // parameter ID
		"Hi_Hat_Closed Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.3f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Hi_Hat Room Mix",       // parameter ID
		"Hi_Hat_Closed Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));


	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom1 Room Mix",       // parameter ID
		"Tom1 Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom1 Master Mix",       // parameter ID
		"Tom1 Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.35f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom1 Overhead Mix",       // parameter ID
		"Tom1 Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom1 Direct Mix",       // parameter ID
		"Tom1 Direct Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom1 Mono Pan",       // parameter ID
		"Tom1 Mono Pan",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom1 Stereo Pan L",       // parameter ID
		"Tom1 Stereo Pan L",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom1 Stereo Pan R",       // parameter ID
		"Tom1 Stereo Pan R",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		1.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom2 Room Mix",       // parameter ID
		"Tom2 Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom2 Master Mix",       // parameter ID
		"Tom2 Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.35f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom2 Direct Mix",       // parameter ID
		"Tom2 Direct Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom2 Overhead Mix",       // parameter ID
		"Tom2 Overhead Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.35f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom2 Mono Pan",       // parameter ID
		"Tom2 Mono Pan",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom2 Stereo Pan L",       // parameter ID
		"Tom2 Stereo Pan L",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom2 Stereo Pan R",       // parameter ID
		"Tom2 Stereo Pan R",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		1.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom3 Room Mix",       // parameter ID
		"Tom3 Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom3 Direct Mix",       // parameter ID
		"Tom3 Direct Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom3 Master Mix",       // parameter ID
		"Tom3 Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.35f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom3 Overhead Mix",       // parameter ID
		"Tom3 Overhead Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.35f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom3 Mono Pan",       // parameter ID
		"Tom3 Mono Pan",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom3 Stereo Pan L",       // parameter ID
		"Tom3 Stereo Pan L",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Tom3 Stereo Pan R",       // parameter ID
		"Tom3 Stereo Pan R",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		1.0f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Ride Master Mix",       // parameter ID
		"Ride Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Stack Master Mix",       // parameter ID
		"Stack Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.3f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Master Mix",       // parameter ID
		"Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.8f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Master Room Mix",       // parameter ID
		"Master Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.8f,         // default value
		""));


	parameters.state = ValueTree(Identifier("DrumSamplerVT"));
	
	fileManager=new FileManager();
	instrumentMap = std::map<int, Instrument*>();
	int buffersCreated = 0;
	for (std::map<int, std::pair<String, int>>::iterator iter = fileManager->MidiMap.begin(); iter != fileManager->MidiMap.end(); ++iter)
	{
		if (iter->second.first.compare("")) {
			Instrument* newInstrument=new Instrument(iter->second.first, iter->second.second, fileManager, this);
			buffersCreated += newInstrument->createBuffers();
			instrumentMap.insert(pair<int, Instrument*>(iter->first, newInstrument));
		}

	}
	DBG("Buffers created count: " + String(buffersCreated));
}

DrumSamplerAudioProcessor::~DrumSamplerAudioProcessor()
{
	for (map<int, Instrument*>::iterator it = instrumentMap.begin(); it != instrumentMap.end(); it++)
	{
		delete it->second;
	}
	delete fileManager;

}

//==============================================================================
const String DrumSamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DrumSamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DrumSamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DrumSamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DrumSamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DrumSamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DrumSamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DrumSamplerAudioProcessor::setCurrentProgram (int index)
{
}

const String DrumSamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void DrumSamplerAudioProcessor::changeProgramName (int index, const String& newName)
{
}
//==============================================================================
void DrumSamplerAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	reset();
	srand(time(0));
}

void DrumSamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DrumSamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
	//AudioChannelSet::dis
	//TODO: Fix if we add a ride bus too
	//layouts.getChannelSet(false,0)
	if (layouts.outputBuses.size() != 8) { 
		return false;
	}
	if (layouts.getChannelSet(false,0) != AudioChannelSet::stereo()) {
		return false;
	}
	if (layouts.getChannelSet(false, 1) != AudioChannelSet::stereo()) {
		return false;
	}
	if (layouts.getChannelSet(false, 2) != AudioChannelSet::stereo()) {
		return false;
	}
	if (layouts.getChannelSet(false, 3) != AudioChannelSet::mono()) {
		return false;
	}
	if (layouts.getChannelSet(false, 4) != AudioChannelSet::mono()) {
		return false;
	}
	if (layouts.getChannelSet(false, 5) != AudioChannelSet::mono()) {
		return false;
	}
	if (layouts.getChannelSet(false, 6) != AudioChannelSet::mono()) {
		return false;
	}
	if (layouts.getChannelSet(false, 7) != AudioChannelSet::mono()) {
		return false;
	}
	if (layouts.getChannelSet(false, 8) != AudioChannelSet::mono()) {
		return false;
	}

	return true;
	//layouts.
 // #if JucePlugin_IsMidiEffect
 //   ignoreUnused (layouts);
 //   return true;
 // #else
 //   // This is the place where you check if the layout is supported.
 //   // In this template code we only support mono or stereo.
 //   if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
 //    && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
 //       return false;

 //   // This checks if the input layout matches the output layout
 //  #if ! JucePlugin_IsSynth
 //   if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
 //       return false;
 //  #endif

 //   return true;
 // #endif
}
#endif

void DrumSamplerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

	
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = 0; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
	
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
	MidiMessage currMessage;
	MidiBuffer::Iterator iterator(midiMessages);
	int midiPosition = -1;
	
	map<int, Instrument*>::iterator it;

	while (iterator.getNextEvent(currMessage, midiPosition)) {

		if (currMessage.isNoteOn(false)){
			//Get the midi note information
			const int noteNumber = currMessage.getNoteNumber();
			const float noteVelocity = currMessage.getFloatVelocity();
			const int timeStamp=currMessage.getTimeStamp();
			//Get the master parameters.
			//masterFader = *parameters.getRawParameterValue("Master Mix");
			//roomFader= *parameters.getRawParameterValue("Master Room Mix");
			
			//	micVector.push_back(((1 - roomFader)*(1 - snare_rimBottomFader))*masterFader*snare_rimMaster);//top
			//	micVector.push_back(((1 - roomFader)*snare_rimBottomFader)*masterFader*snare_rimMaster);//bottom
			std::map<int, Instrument*>::iterator iter = instrumentMap.find(noteNumber);
			if (iter != instrumentMap.end()) {
				float master;
				float overHead;
				Instrument *tempInst = (iter->second);

				vector<float> micVector;
				String instrumentName = tempInst->instrumentName;
				if (instrumentName.compareIgnoreCase("sidestick")==0 || instrumentName.compareIgnoreCase("rimshot")==0) {
					instrumentName = String("snare");
				}
				// Convert the instrument name to capital so that we can find the parameter value
				instrumentName=instrumentName.replaceSection(0, 1, instrumentName.substring(0, 1).toUpperCase());

				roomFader = (*parameters.getRawParameterValue(instrumentName + " Room Mix")) * (*parameters.getRawParameterValue("Master Room Mix"));
				master = (*parameters.getRawParameterValue(instrumentName + " Master Mix")) * (*parameters.getRawParameterValue("Master Mix"));
				overHead = *parameters.getRawParameterValue(instrumentName + " Overhead Mix");
				float monoPan = *parameters.getRawParameterValue(instrumentName + " Mono Pan");
				float stereoPan[2];
				stereoPan[0]= *parameters.getRawParameterValue(instrumentName + " Stereo Pan L");
				stereoPan[1] = *parameters.getRawParameterValue(instrumentName + " Stereo Pan R");

				float kickInOut = *parameters.getRawParameterValue("Kick In/Out Mix");
				float kickDirect = *parameters.getRawParameterValue("Kick Direct Mix");
				float snareDirect = *parameters.getRawParameterValue("Snare Direct Mix");
				float snareBottomTop = *parameters.getRawParameterValue("Snare Bottom Mix");
				float tom1Direct= *parameters.getRawParameterValue("Tom1 Direct Mix");
				float tom2Direct = *parameters.getRawParameterValue("Tom2 Direct Mix");
				float tom3Direct = *parameters.getRawParameterValue("Tom3 Direct Mix");


				//const String MIC_NAMES[MIC_COUNT] = { "kick_in", "kick_out", "snare_bottom", "snare_top", "tom1", "tom2", "tom3", "ride", "room_mono", "room_main",
				//"room_wide", "overhead"};
				micVector.push_back(float(0.2*master*kickDirect*kickInOut)); // kick_in 1
				micVector.push_back(float(0.2*master*kickDirect*(1 - kickInOut))); // kick_out 1
				micVector.push_back(float(0.2*master*snareDirect*snareBottomTop)); // snare_bottom
				micVector.push_back(float(0.2*master*snareDirect*(1 - snareBottomTop))); // snare_top
				micVector.push_back(float(0.5*master*tom1Direct)); // tom1
				micVector.push_back(float(0.5*master*tom2Direct)); // tom2
				micVector.push_back(float(0.5*master*tom3Direct)); // tom3
				micVector.push_back(float(0.5*master)); // ride
				micVector.push_back(float(0.2*roomFader*master)); // room_mono
				micVector.push_back(float(0.2*roomFader*master)); // room_main
				micVector.push_back(float(0.2*roomFader*master)); // room_wide
				micVector.push_back(float(0.2*overHead*master)); // overhead
				tempInst->triggerInstrument(micVector, noteVelocity, timeStamp, monoPan, stereoPan, this);
			}
		}
	}

	for (it = instrumentMap.begin(); it != instrumentMap.end(); it++)
	{
		it->second->fillFromIterators(buffer);
	}

}

//==============================================================================
bool DrumSamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DrumSamplerAudioProcessor::createEditor()
{
    return new DrumSamplerAudioProcessorEditor (*this);
}

//==============================================================================
void DrumSamplerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	ValueTree state = parameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void DrumSamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr) {
		if (xmlState->hasTagName(parameters.state.getType())) {
			parameters.replaceState(ValueTree::fromXml(*xmlState));
		}
	}
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DrumSamplerAudioProcessor();
}
