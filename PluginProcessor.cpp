/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <ctime>

//TODO: MOVE THESE ALL TO INSTRUMENT
const int KICK_MIC_COUNT=2;
const int KICK_VELOCITY_COUNT = 3;
const int SNARE_MIC_COUNT = 3;
const int SNARE_RIM_MIC_COUNT = 3;
const int SNARE_VELOCITY_COUNT = 4;
const int SNARE_RIM_VELOCITY_COUNT = 1;
const int FLOOR_TOM_MIC_COUNT = 2;
const int FLOOR_TOM_VELOCITY_COUNT = 3;
const int HI_HAT_CLOSED_MIC_COUNT = 2;
const int HI_HAT_CLOSED_VELOCITY_COUNT = 3;
const int HI_HAT_OPEN_MIC_COUNT = 2;
const int HI_HAT_OPEN_VELOCITY_COUNT = 2;
const int RACK_TOM_MIC_COUNT = 2;
const int RACK_TOM_VELOCITY_COUNT = 3;
const int CRASH_ALT_MIC_COUNT = 1;
const int CRASH_ALT_VELOCITY_COUNT = 1;
const int CHINA_MIC_COUNT = 1;
const int CHINA_VELOCITY_COUNT = 1;
const int CRASH_MAIN_MIC_COUNT = 1;
const int CRASH_MAIN_VELOCITY_COUNT = 2;
const int RIDE_MIC_COUNT = 1;
const int RIDE_VELOCITY_COUNT = 2;
const int STACK_MIC_COUNT = 1;
const int STACK_VELOCITY_COUNT = 1;

const int MAX_MIC_COUNT = 3;
const int MAX_VELOCITY_COUNT = 4;
const int NUM_OF_SAME_SAMPLE = 5;

const int HI_HAT_SAMPLE_OFFSET = 32;
//==============================================================================


DrumSamplerAudioProcessor::DrumSamplerAudioProcessor()
	: parameters(*this, nullptr)
#ifndef JucePlugin_PreferredChannelConfigurations
     , AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
						.withOutput("Kick", AudioChannelSet::mono(), true)
                     #endif
                       )
#endif
{
	

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick Room Mix",       // parameter ID
		"Kick Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Kick Master Mix",       // parameter ID
		"Kick Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.5f,         // default value
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

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Floor_Tom Room Mix",       // parameter ID
		"Floor_Tom Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Floor_Tom Master Mix",       // parameter ID
		"Floor_Tom Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.35f,         // default value
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


	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Rack_Tom Room Mix",       // parameter ID
		"Rack_Tom Room Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.2f,         // default value
		""));

	parameters.createAndAddParameter(std::make_unique<AudioParameterFloat>("Rack_Tom Master Mix",       // parameter ID
		"Rack_Tom Master Mix",       // parameter name
		NormalisableRange<float>(0, 1),    // range
		0.35f,         // default value
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
	
	sampleManager=new SampleManager();

	//list<IteratorPack>* iterators;
	iterators = new list<IteratorPack>();
	formatManager = new AudioFormatManager();
	// TODO: Move to file manager
	formatManager->registerBasicFormats();


	instrumentMap = std::map<int, Instrument>();
	
	for (std::map<int, std::pair<String, int>>::iterator iter = sampleManager->MidiMap.begin(); iter != sampleManager->MidiMap.end(); ++iter)
	{
		if (iter->second.first.compare("")) {
			Instrument newInstrument(iter->second.first, iter->second.second, formatManager, sampleManager, iterators);
			newInstrument.createBuffers();
			instrumentMap.insert(pair<int, Instrument>(iter->first, newInstrument));
		}

	}
/*
	kickPack = new Instrument(String("kick"), 6, formatManager, sampleManager, iterators);

	kickPack->createBuffers();*/




}

DrumSamplerAudioProcessor::~DrumSamplerAudioProcessor()
{
	//Free each buffer in each array of buffers.
	/*vector<AudioSampleBuffer**> buffersList;
	buffersList.push_back(kickSampleBuffers);
	buffersList.push_back(snareSampleBuffers);
	buffersList.push_back(snare_rimSampleBuffers);
	buffersList.push_back(chinaSampleBuffers);
	buffersList.push_back(crash_altSampleBuffers);
	buffersList.push_back(crash_mainSampleBuffers);
	buffersList.push_back(floor_tomSampleBuffers);
	buffersList.push_back(rack_tomSampleBuffers);
	buffersList.push_back(hi_hat_closedSampleBuffers);
	buffersList.push_back(hi_hat_openSampleBuffers);
	buffersList.push_back(rideSampleBuffers);
	buffersList.push_back(stackSampleBuffers);
	
	for (AudioSampleBuffer** &currBuffer : buffersList) {
		for (int i = 0; i < NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT; i++) {
			if (currBuffer[i])
				delete currBuffer[i];
		}
	}
	
	delete iterators;
	delete samplesFolder;*/
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
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
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
	
	std::list<IteratorPack>::iterator it;
	std::list<IteratorPack>::iterator end;
	it = iterators->begin();
	end = iterators->end();
	
	//Loop through the iterators left from previous blocks and fill the current block
	while (it!=end) {
		IteratorPack currPack = *it;
		int i=0;
		//for (int channel = 0; channel < 1; ++channel){
		float *out = buffer.getWritePointer(currPack.channelNum);
		for (i = 0; (i < currPack.samplesLeft) && (i < getBlockSize()); i++) {
			out[i] += currPack.address[i]*currPack.velocity;
		}
		//}
		//If the iterator has reached the end, erase the element.
		if (i < getBlockSize()) {
			it=iterators->erase(it);
		}
		//Else update the remaining numbers.
		else {
			it->samplesLeft -= i;
			it->address += i;
			it++;
		}
	}
	
	while (iterator.getNextEvent(currMessage, midiPosition)) {

		if (currMessage.isNoteOn(false)){
			//Get the midi note information
			const int noteNumber = currMessage.getNoteNumber();
			const float noteVelocity = currMessage.getFloatVelocity();
			const int timeStamp=currMessage.getTimeStamp();
			//Get the master parameters.
			masterFader = *parameters.getRawParameterValue("Master Mix");
			roomFader= *parameters.getRawParameterValue("Master Room Mix");
			
			
			vector<float> micVector; 
			////If kick
		//else if (noteNumber>=34 && noteNumber<=36) {


			//TODO: Vary these parameters based on the isntrument
			float master = *parameters.getRawParameterValue("Kick Master Mix");
			roomFader *= *parameters.getRawParameterValue("Kick Room Mix");
			//micVector.push_back((1 - roomFader)*masterFader*kickMaster);//direct
			//micVector.push_back(roomFader*masterFader*kickMaster);//room
			//
			micVector.push_back(float(0.2*master)); // kick_in 1
			micVector.push_back(float(0.2*master)); // kick_out 1
			micVector.push_back(float(1)); // snare_bottom
			micVector.push_back(float(1)); // snare_top
			micVector.push_back(float(1)); // tom1
			micVector.push_back(float(1)); // tom2
			micVector.push_back(float(1)); // tom3
			micVector.push_back(float(1)); // ride
			micVector.push_back(float(0)); // overhead
			micVector.push_back(float(0.2*roomFader)); // room_main
			micVector.push_back(float(0.2*roomFader)); // room_mono
			micVector.push_back(float(0.2*roomFader)); // room_wide

			//	micVector.push_back(((1 - roomFader)*(1 - snare_rimBottomFader))*masterFader*snare_rimMaster);//top
			//	micVector.push_back(((1 - roomFader)*snare_rimBottomFader)*masterFader*snare_rimMaster);//bottom
			std::map<int, Instrument>::iterator iter = instrumentMap.find(noteNumber);
			if (iter != instrumentMap.end()) {
				Instrument tempInst = iter->second;
				//TODO: Remove micPointers, velocityCount
				tempInst.triggerInstrument(&buffer, tempInst.micPointers, micVector, tempInst.velocityCount, noteVelocity, timeStamp, totalNumOutputChannels, getBlockSize());
			}
		}
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
}

void DrumSamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DrumSamplerAudioProcessor();
}
