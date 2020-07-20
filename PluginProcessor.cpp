/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include <ctime>

#include "BlockEventsTest.cpp"

#define TESTING 1

#define LOADSAMPLES 1
const int NUM_OF_SAME_SAMPLE = 5;

const int HI_HAT_SAMPLE_OFFSET = 32;
//==============================================================================


DrumSamplerAudioProcessor::DrumSamplerAudioProcessor()
	: treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#ifndef JucePlugin_PreferredChannelConfigurations
     , AudioProcessor (BusesProperties()
                     //#if ! JucePlugin_IsMidiEffect
                        .withOutput ("Master", AudioChannelSet::stereo(), true)
						.withOutput("Kick", AudioChannelSet::stereo(), true)
						.withOutput("Snare", AudioChannelSet::stereo(), true)
						.withOutput("Toms", AudioChannelSet::stereo(), true)
						.withOutput("HiHat", AudioChannelSet::stereo(), true)
						.withOutput("Ride", AudioChannelSet::stereo(), true)
						.withOutput("Room", AudioChannelSet::stereo(), true)
						.withOutput("OH", AudioChannelSet::stereo(), true)


                     //#endif
                       )
#endif
{
	
#ifdef TESTING
	UnitTestRunner testRunner;
	testRunner.runAllTests();
#endif
	
	fileManager=new FileManager();
	instrumentMap = std::map<int, NoteSound*>();
	if (!LOADSAMPLES) return;

	for (String micName : MicController::getMicNames()) {		
		//TODO: Reconsider the initial number of samples.
		micOutputs[micName] = new AudioSampleBuffer(2, 0);
	}
	// Gets the instrument names from the MidiMap file.
	for (std::map<int, NoteProperties>::iterator iter = fileManager->MidiMap.begin(); iter != fileManager->MidiMap.end(); ++iter)
	{
		if (iter->second.generalControllerName.compare("")) {
			//TODO: Handle the isInstrument cases
			//TODO: add robin count parameter
			NoteSound* newInstrument=new NoteSound(&iter->second, fileManager, this, &micOutputs);
			//newInstrument->createBuffers();
			instrumentMap.insert(pair<int, NoteSound*>(iter->first, newInstrument));
		}

	}
}

AudioProcessorValueTreeState::ParameterLayout DrumSamplerAudioProcessor::createParameterLayout()
{
	return ParameterBuilder::createParameterLayout();
}

DrumSamplerAudioProcessor::~DrumSamplerAudioProcessor()
{
	for (map<int, NoteSound*>::iterator it = instrumentMap.begin(); it != instrumentMap.end(); it++)
	{
		delete it->second;
	}
	for (auto const& x : micOutputs)
	{
		delete x.second;
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
	for (auto const& instrument : instrumentMap) {
		instrument.second->setBlockSize(samplesPerBlock);
	}
	for (std::map<String, AudioSampleBuffer*>::iterator iter = micOutputs.begin(); iter != micOutputs.end(); ++iter) {
		iter->second->setSize(2, samplesPerBlock + FADE_OUT_SAMPLES);
	}
}

void DrumSamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DrumSamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
	//TODO:DELETE
	if (JUCEApplication::isStandaloneApp()) {
		if (layouts.getMainOutputChannelSet() != AudioChannelSet::disabled()
			|| layouts.getMainOutputChannelSet() != AudioChannelSet::stereo()) {
			return true;
		}
		else return false;
	}
	//return true;
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
	if (layouts.getChannelSet(false, 3) != AudioChannelSet::stereo()) {
		return false;
	}
	if (layouts.getChannelSet(false, 4) != AudioChannelSet::stereo()) {
		return false;
	}
	if (layouts.getChannelSet(false, 5) != AudioChannelSet::stereo()) {
		return false;
	}
	if (layouts.getChannelSet(false, 6) != AudioChannelSet::stereo()) {
		return false;
	}
	if (layouts.getChannelSet(false, 7) != AudioChannelSet::stereo()) {
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
	for (std::map<String, AudioSampleBuffer*>::iterator iter = micOutputs.begin(); iter != micOutputs.end(); ++iter) {
		iter->second->clear();
	}
	
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	// MAGIC GUI: send midi messages to the keyboard state
	magicState.processMidiBuffer(midiMessages, buffer.getNumSamples(), true);
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
	

	while (iterator.getNextEvent(currMessage, midiPosition)) {

		if (currMessage.isNoteOn(false)){
			//Get the midi note information
			const int noteNumber = currMessage.getNoteNumber();
			const float noteVelocity = currMessage.getFloatVelocity();
			const int timeStamp=currMessage.getTimeStamp();
			//Get the master parameters.
			//masterFader = *treeState.getRawParameterValue("Master Mix");
			//roomFader= *treeState.getRawParameterValue("Master Room Mix");
			
			std::map<int, NoteSound*>::iterator iter = instrumentMap.find(noteNumber);
			// Checks if the instrument is a valid one
			if (iter != instrumentMap.end()) {
				NoteSound *tempSound = (iter->second);
				String generalControllerName = tempSound->noteProperties->generalControllerName;
				String specificControllerName = tempSound->noteProperties->specificControllerName;


				float pan = *treeState.getRawParameterValue(specificControllerName + " Pan");
				auto micGains = micController.getMicGains(generalControllerName, specificControllerName);
				tempSound->triggerSound(micGains, noteVelocity, timeStamp, pan, this);

				//TODO: DELETE, TESTING PURPOSES
				if (tempSound->noteProperties->noteNum == 50) {
					instrumentMap[52]->killSound(timeStamp);
				}
				if (tempSound->noteProperties->noteNum == 80) {
					instrumentMap[79]->killSound(timeStamp);
				}
			}
		}

		////TODO: DELETE, TESTING
		//buffer.getWritePointer(0)[0] = -1.0f;
	}


	map<int, NoteSound*>::iterator it;
	// Fills the buffer with all already activate instruments
	for (it = instrumentMap.begin(); it != instrumentMap.end(); it++)
	{
		it->second->fillFromIterators();
	}

	//for (auto const& mic : micOutputs) {
	//	buffer.addFrom(0, 0, *mic.second, 0, 0, buffer.getNumSamples());
	//	buffer.addFrom(1, 0, *mic.second, 1, 0, buffer.getNumSamples());
	//}
	outputManager.processBlock(this, &buffer, &micOutputs);
	midiMessages.clear();
}

//==============================================================================
bool DrumSamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DrumSamplerAudioProcessor::createEditor()
{
    //return new DrumSamplerAudioProcessorEditor (*this);

	return new foleys::MagicPluginEditor(magicState, BinaryData::interface_xml, BinaryData::interface_xmlSize);
	//return new foleys::MagicPluginEditor(magicState);
}

//==============================================================================
void DrumSamplerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	//ValueTree state = treeState.copyState();
	//std::unique_ptr<XmlElement> xml(state.createXml());
	//copyXmlToBinary(*xml, destData);
	magicState.getStateInformation(destData);
}

void DrumSamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

	//std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	//if (xmlState.get() != nullptr) {
	//	if (xmlState->hasTagName(treeState.state.getType())) {
	//		treeState.replaceState(ValueTree::fromXml(*xmlState));
	//	}
	//}
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	magicState.setStateInformation(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DrumSamplerAudioProcessor();
}
