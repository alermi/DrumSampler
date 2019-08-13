/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <ctime>

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
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	

	formatManager.registerBasicFormats();
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
	
	//samplesFolder=new File(String("C:\\Users\\Ani\\Documents\\JUCE Projects\\DrumSampler\\Samples"));
	
	FileChooser samplesFinder("Please choose the folder containing the samples for DrumSampler.");
	samplesFinder.browseForDirectory();
	File returned = samplesFinder.getResult();
	samplesFolder=new File(returned);
	
	iterators = new list<IteratorPack>();
	/*
	InstrumentPack* kickPack = new InstrumentPack("kick", 6, this);
	kickPack->createBuffers();*/

	kickSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> kickMics = { "Direct","Room" };
	vector<String> kickVelocities = { "Soft","Medium","Hard" };
	createBuffers(kickSampleBuffers, "Kick", kickMics, kickVelocities);
	/*
	snareSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> snareMics = { "Top","Bottom","Room" };
	vector<String> snareVelocities = { "Feather","Soft","Medium","Hard" };
	createBuffers(snareSampleBuffers, "Snare", snareMics, snareVelocities);

	chinaSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> chinaMics = { "OH" };
	vector<String> chinaVelocities = { "Medium" };
	createBuffers(chinaSampleBuffers, "China", chinaMics, chinaVelocities);
	
	crash_altSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> crash_altMics = { "OH" };
	vector<String> crash_altVelocities = { "Medium" };
	createBuffers(crash_altSampleBuffers, "Crash_Alt", crash_altMics, crash_altVelocities);

	crash_mainSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> crash_mainMics = { "OH" };
	vector<String> crash_mainVelocities = { "Soft", "Hard" };
	createBuffers(crash_mainSampleBuffers, "Crash_Main", crash_mainMics, crash_mainVelocities);

	floor_tomSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> floor_tomMics = { "Direct", "Room" };
	vector<String> floor_tomVelocities = { "Soft","Medium", "Hard" };
	createBuffers(floor_tomSampleBuffers, "Floor_Tom", floor_tomMics, floor_tomVelocities);

	rack_tomSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> rack_tomMics = { "Direct", "Room" };
	vector<String> rack_tomVelocities = { "Soft","Medium", "Hard" };
	createBuffers(rack_tomSampleBuffers, "Rack_Tom", rack_tomMics, rack_tomVelocities);

	hi_hat_closedSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> hi_hat_closedMics = { "Direct", "Room" };
	vector<String> hi_hat_closedVelocities = { "Soft","Medium", "Hard" };
	createBuffers(hi_hat_closedSampleBuffers, "Hi_Hat_Closed", hi_hat_closedMics, hi_hat_closedVelocities);
	
	hi_hat_openSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> hi_hat_openMics = { "Direct", "Room" };
	vector<String> hi_hat_openVelocities = { "Soft", "Hard" };
	createBuffers(hi_hat_openSampleBuffers, "Hi_Hat_Open", hi_hat_openMics, hi_hat_openVelocities);

	rideSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> rideMics = { "OH" };
	vector<String> rideVelocities = { "Soft", "Hard" };
	createBuffers(rideSampleBuffers, "Ride", rideMics, rideVelocities);

	stackSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> stackMics = { "OH" };
	vector<String> stackVelocities = { "Medium" };
	createBuffers(stackSampleBuffers, "Stack", stackMics, stackVelocities);

	snare_rimSampleBuffers = (AudioSampleBuffer **)calloc(NUM_OF_SAME_SAMPLE*MAX_MIC_COUNT*MAX_VELOCITY_COUNT, sizeof(AudioSampleBuffer*));
	vector<String> snare_rimMics = { "Top","Bottom","Room" };
	vector<String> snare_rimVelocities = { "Medium" };
	createBuffers(snare_rimSampleBuffers, "Snare_Rim", snare_rimMics, snare_rimVelocities);*/
	/*
	for (int i = 0; i < NUM_OF_SAME_SAMPLE*KICK_MIC_COUNT*KICK_VELOCITY_COUNT; i++) {
		auto test = kickSampleBuffers[i];
	}*/
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

/* Method to fill the Audio Buffers with corresponding samples.
*/
bool DrumSamplerAudioProcessor::createBuffers
	(AudioSampleBuffer** sampleBuffersToFill, String instrumentName, vector<String> micNames, vector<String> velocityNames) {
	
	

	for (int hardness = 0; hardness < velocityNames.size(); hardness++) {

		for (int mic = 0; mic < micNames.size(); mic++) {

			for (int i = 1; i <= NUM_OF_SAME_SAMPLE; i++) {
				std::unique_ptr<AudioFormatReaderSource> readerSource;
				File newFile(String(getSamplesFolder()->getFullPathName() + "\\"+instrumentName+" "+micNames.at(mic)+" "+velocityNames.at(hardness)+"  (" + String(i) + ").wav"));
				if (newFile.existsAsFile()) {
					std::unique_ptr<AudioFormatReader> reader(this->formatManager.createReaderFor(newFile));
					AudioSampleBuffer *newBuffer = new AudioSampleBuffer(1, reader->lengthInSamples);
					reader->read(newBuffer, 0, reader->lengthInSamples, 0, true, false);
					Range<float> range = newBuffer->findMinMax(0, 0, reader->lengthInSamples);
					float max = std::max(abs(range.getStart()), abs(range.getEnd()));
					newBuffer->applyGain(1 / max);
					newBuffer->applyGainRamp(0, 10, 0, 1);
					int testint = (hardness*NUM_OF_SAME_SAMPLE*micNames.size()) + (NUM_OF_SAME_SAMPLE*mic) + (i - 1);
					sampleBuffersToFill[(hardness*NUM_OF_SAME_SAMPLE*micNames.size())+(NUM_OF_SAME_SAMPLE*mic)+(i - 1)] = newBuffer;
				}
				else {
					sampleBuffersToFill[(hardness*NUM_OF_SAME_SAMPLE*micNames.size()) + (NUM_OF_SAME_SAMPLE*mic) + (i - 1)] = new AudioSampleBuffer();
				}
			}
		}
	}
	return true;
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

//void DrumSamplerAudioProcessor::triggerInstrument
//	(AudioBuffer<float> *bufferToFill, AudioSampleBuffer** instrumentSamples, vector<float> micGains, int numLevels, float noteVelocity, int timeStamp) {
//	
//	//TODO:Mix in the room sound and other mics
//	// Change 5
//	//AudioSampleBuffer *newArray = instrumentSamples[5];
//	
//	//Calculate which hardness level of each sample top play based on velocity of the note and 
//	//the number of available velocities.
//	float levelNumber = 128*noteVelocity*float(numLevels) / 129;
//	//Vector to hold the read pointers of each sample to be played.
//	vector<const float*> inVector;
//	//vector to hold how many sample from each read pointer is going to be played.
//	vector<int> sampleCountVector;
//	
//	//Randomize which version of the same sample it is going to play
//	int version = rand() % NUM_OF_SAME_SAMPLE;
//
//	//Create an iterator to be played for each microphone
//	for (int i = 0; i < micGains.size() ; i++) {
//		//Find the correct index that holds each sample of each room mic.
//		int index = (int(levelNumber)*NUM_OF_SAME_SAMPLE*micGains.size()) + (version + i * NUM_OF_SAME_SAMPLE);//Place of the sample in array of buffers
//		inVector.push_back(instrumentSamples[index]->getReadPointer(0));
//		//Add the number of samples to be played to another vector
//		sampleCountVector.push_back(instrumentSamples[version + i * NUM_OF_SAME_SAMPLE]->getNumSamples());
//
//	}
//	//auto in = newArray[5]->getReadPointer(0);
//	//int sampleNum = newArray->getNumSamples();
//	
//	int i = 0;
//	//TODO:Set Stereo gain levels
//	//Write the samples to the output buffer and store the remaining in iteratorPack.
//	for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel) {
//		float *out = bufferToFill->getWritePointer(channel);
//
//		for (int j = 0; j < inVector.size(); j++) {
//			for (i = 0; ((i < sampleCountVector.at(j)) && (i < getBlockSize() - timeStamp)); i++) {
//				
//				out[timeStamp + i] += (inVector.at(j)[i] * noteVelocity*micGains.at(j));
//			}
//			if ((i + timeStamp >= getBlockSize())&&channel==0) {
//				IteratorPack newPack(((float*)(inVector.at(j) + i)), noteVelocity*micGains.at(j), sampleCountVector.at(j) - i,(instrumentSamples==hi_hat_openSampleBuffers));
//				iterators->push_back(newPack);
//			}
//		}
//		
//	}
//	//If we triggered a closed hi-hat, mute open hi_hat hits.
//	if (instrumentSamples == hi_hat_closedSampleBuffers) {
//		for (IteratorPack &currPack : *iterators) {
//			if (currPack.isHiHatOpen) {
//				currPack.samplesLeft = timeStamp+HI_HAT_SAMPLE_OFFSET;
//			}
//		}
//	}
//
//	
//}
void DrumSamplerAudioProcessor::triggerInstrument
(AudioBuffer<float> *bufferToFill, AudioSampleBuffer** instrumentSamples, vector<float> micGains, int numLevels, float noteVelocity, int timeStamp) {

	//TODO:Mix in the room sound and other mics
	// Change 5
	//AudioSampleBuffer *newArray = instrumentSamples[5];

	//Calculate which hardness level of each sample top play based on velocity of the note and 
	//the number of available velocities.
	float levelNumber = 128 * noteVelocity*float(numLevels) / 129;
	//Vector to hold the read pointers of each sample to be played.
	vector<const float*> inVector;
	//vector to hold how many sample from each read pointer is going to be played.
	vector<int> sampleCountVector;

	//Randomize which version of the same sample it is going to play
	int version = rand() % NUM_OF_SAME_SAMPLE;

	//Create an iterator to be played for each microphone
	for (int i = 0; i < micGains.size(); i++) {
		//Find the correct index that holds each sample of each room mic.
		int index = (int(levelNumber)*NUM_OF_SAME_SAMPLE*micGains.size()) + (version + i * NUM_OF_SAME_SAMPLE);//Place of the sample in array of buffers
		inVector.push_back(instrumentSamples[index]->getReadPointer(0));
		//Add the number of samples to be played to another vector
		sampleCountVector.push_back(instrumentSamples[version + i * NUM_OF_SAME_SAMPLE]->getNumSamples());

	}
	//auto in = newArray[5]->getReadPointer(0);
	//int sampleNum = newArray->getNumSamples();

	int i = 0;
	//TODO:Set Stereo gain levels
	//Write the samples to the output buffer and store the remaining in iteratorPack.
	for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel) {
		float *out = bufferToFill->getWritePointer(channel);

		for (int j = 0; j < inVector.size(); j++) {
			for (i = 0; ((i < sampleCountVector.at(j)) && (i < getBlockSize() - timeStamp)); i++) {

				out[timeStamp + i] += (inVector.at(j)[i] * noteVelocity*micGains.at(j));
			}
			if ((i + timeStamp >= getBlockSize()) && channel == 0) {
				IteratorPack newPack(((float*)(inVector.at(j) + i)), noteVelocity*micGains.at(j), sampleCountVector.at(j) - i, (instrumentSamples == hi_hat_openSampleBuffers));
				iterators->push_back(newPack);
			}
		}

	}
	//If we triggered a closed hi-hat, mute open hi_hat hits.
	if (instrumentSamples == hi_hat_closedSampleBuffers) {
		for (IteratorPack &currPack : *iterators) {
			if (currPack.isHiHatOpen) {
				currPack.samplesLeft = timeStamp + HI_HAT_SAMPLE_OFFSET;
			}
		}
	}


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
		for (int channel = 0; channel < totalNumOutputChannels; ++channel){
			float *out = buffer.getWritePointer(channel);
			for (i = 0; (i < currPack.samplesLeft) && (i < getBlockSize()); i++) {
				out[i] += currPack.address[i]*currPack.velocity;
			}
		}
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
			float kickMaster = *parameters.getRawParameterValue("Kick Master Mix");
			roomFader *= *parameters.getRawParameterValue("Kick Room Mix");
			micVector.push_back((1 - roomFader)*masterFader*kickMaster);//direct
			micVector.push_back(roomFader*masterFader*kickMaster);//room
			triggerInstrument(&buffer, kickSampleBuffers, micVector, KICK_VELOCITY_COUNT, noteVelocity, timeStamp);
		//}

			//Very long if statements to map each midi note to an instrument. TODO:Fix it

			// //if hi_hat_closed
			//if ((noteNumber <= 11 && noteNumber>=7)||
			//		(noteNumber>=18 && noteNumber<=22) ||
			//		noteNumber==42 || 
			//		noteNumber==44 ||
			//		(noteNumber>=61 && noteNumber<=65)||
			//		noteNumber==119 ||
			//		noteNumber==122){
			//	float hi_hat_closedMaster = *parameters.getRawParameterValue("Hi_Hat Master Mix");
			//	roomFader *= *parameters.getRawParameterValue("Hi_Hat Room Mix");
			//	micVector.push_back((1 - roomFader)*masterFader*hi_hat_closedMaster);//direct
			//	micVector.push_back(roomFader*masterFader*hi_hat_closedMaster);//room
			//	triggerInstrument(&buffer, hi_hat_closedSampleBuffers, micVector, HI_HAT_CLOSED_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			////If snare
			//else if (noteNumber == 6 || 
			//		noteNumber==33|| 
			//		noteNumber==37||
			//		noteNumber==38||
			//		(noteNumber>=66 && noteNumber<=71)||
			//		noteNumber==125){
			//	float snareBottomFader = *parameters.getRawParameterValue("Snare Bottom Mix");
			//	float snareMaster = *parameters.getRawParameterValue("Snare Master Mix");
			//	roomFader *= *parameters.getRawParameterValue("Snare Room Mix");
			//	micVector.push_back(((1 - roomFader)*(1 - snareBottomFader))*masterFader*snareMaster);//top
			//	micVector.push_back(((1 - roomFader)*snareBottomFader)*masterFader*snareMaster);//bottom
			//	micVector.push_back(roomFader*masterFader*snareMaster);//room
			//	triggerInstrument(&buffer, snareSampleBuffers, micVector, SNARE_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			////If kick
			//else if (noteNumber>=34 && noteNumber<=36) {
			//	float kickMaster = *parameters.getRawParameterValue("Kick Master Mix");
			//	roomFader *= *parameters.getRawParameterValue("Kick Room Mix");
			//	micVector.push_back((1 - roomFader)*masterFader*kickMaster);//direct
			//	micVector.push_back(roomFader*masterFader*kickMaster);//room
			//	triggerInstrument(&buffer, kickSampleBuffers, micVector, KICK_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			////if hi_hat_open
			//else if ((noteNumber >= 12 && noteNumber<=17||
			//		(noteNumber >= 23 && noteNumber <= 26)||
			//		noteNumber==46)||
			//		noteNumber==60||
			//		noteNumber>=120 && noteNumber<=124) {
			//	float hi_hat_openMaster = *parameters.getRawParameterValue("Hi_Hat Master Mix");
			//	roomFader *= *parameters.getRawParameterValue("Hi_Hat Room Mix");
			//	micVector.push_back((1 - roomFader)*masterFader*hi_hat_openMaster);//direct
			//	micVector.push_back(roomFader*masterFader*hi_hat_openMaster);//room
			//	triggerInstrument(&buffer, hi_hat_openSampleBuffers, micVector, HI_HAT_OPEN_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			////If crash_main
			//else if (noteNumber == 28||
			//	noteNumber==29||
			//	noteNumber==49||
			//	noteNumber==54||
			//	noteNumber==83||
			//	noteNumber==94||
			//	noteNumber==95) {
			//	float crash_mainMaster = *parameters.getRawParameterValue("Crash_Main Master Mix");
			//	micVector.push_back(crash_mainMaster*noteVelocity*masterFader);
			//	triggerInstrument(&buffer, crash_mainSampleBuffers, micVector, CRASH_MAIN_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}//If crash_alt
			//else if ((noteNumber >= 30 && noteNumber <= 32)||
			//	noteNumber==57||
			//	noteNumber==58||
			//	noteNumber==76||
			//	noteNumber==106||
			//	noteNumber==107||
			//	noteNumber==118) {
			//	float crash_altMaster = *parameters.getRawParameterValue("Crash_Alt Master Mix");
			//	micVector.push_back(crash_altMaster*noteVelocity*masterFader);
			//	triggerInstrument(&buffer, crash_altSampleBuffers, micVector, CRASH_ALT_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			////If china
			//else if (noteNumber == 52 ||
			//	noteNumber == 93||
			//	noteNumber==117) {
			//	float chinaMaster = *parameters.getRawParameterValue("China Master Mix");
			//	micVector.push_back(chinaMaster*noteVelocity*masterFader);
			//	triggerInstrument(&buffer, chinaSampleBuffers, micVector, CHINA_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			////if ride
			//else if (noteNumber == 51||
			//	noteNumber==53||
			//	noteNumber==56||
			//	noteNumber==59||
			//	(noteNumber>=84 && noteNumber<= 92)||
			//	(noteNumber>=96 && noteNumber <= 105||
			//	(noteNumber>=108 && noteNumber<=116))) {
			//	float rideMaster = *parameters.getRawParameterValue("Ride Master Mix");
			//	micVector.push_back(rideMaster*noteVelocity*masterFader);
			//	triggerInstrument(&buffer, rideSampleBuffers, micVector, RIDE_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			////if stack
			//else if (noteNumber == 27 ||
			//	noteNumber==55) {
			//	float stackMaster = *parameters.getRawParameterValue("Stack Master Mix");
			//	micVector.push_back(stackMaster*noteVelocity*masterFader);
			//	triggerInstrument(&buffer, stackSampleBuffers, micVector, STACK_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			//
			////if rack tom
			//else if (noteNumber <= 3||
			//	noteNumber==45||
			//	noteNumber==47||
			//	noteNumber==48||
			//	noteNumber==50||
			//	(noteNumber>=77 && noteNumber<=82)) {
			//	float rack_tomMaster = *parameters.getRawParameterValue("Rack_Tom Master Mix");
			//	roomFader = *parameters.getRawParameterValue("Rack_Tom Room Mix");
			//	micVector.push_back((1 - roomFader)*masterFader*rack_tomMaster);//direct
			//	micVector.push_back(roomFader*masterFader*rack_tomMaster);//room
			//	triggerInstrument(&buffer, rack_tomSampleBuffers, micVector, RACK_TOM_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			////if floor tom
			//else if (noteNumber == 4 ||
			//	noteNumber == 5 |
			//	noteNumber == 41 ||
			//	noteNumber == 43||
			//	(noteNumber>=72 && noteNumber<=75)) {
			//	float floor_tomMaster = *parameters.getRawParameterValue("Floor_Tom Master Mix");
			//	roomFader *= *parameters.getRawParameterValue("Floor_Tom Room Mix");
			//	micVector.push_back((1 - roomFader)*masterFader*floor_tomMaster);//direct
			//	micVector.push_back(roomFader*masterFader*floor_tomMaster);//room
			//	triggerInstrument(&buffer, floor_tomSampleBuffers, micVector, FLOOR_TOM_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}
			//
			////if snare rim
			//else if (noteNumber == 39||
			//	noteNumber==40|
			//	noteNumber==126||
			//	noteNumber==127) {
			//	float snare_rimBottomFader = *parameters.getRawParameterValue("Snare Bottom Mix");
			//	float snare_rimMaster = *parameters.getRawParameterValue("Snare Master Mix");
			//	roomFader *= *parameters.getRawParameterValue("Snare Room Mix");
			//	micVector.push_back(((1 - roomFader)*(1 - snare_rimBottomFader))*masterFader*snare_rimMaster);//top
			//	micVector.push_back(((1 - roomFader)*snare_rimBottomFader)*masterFader*snare_rimMaster);//bottom
			//	micVector.push_back(roomFader*masterFader*snare_rimMaster);//room
			//	triggerInstrument(&buffer, snare_rimSampleBuffers, micVector, SNARE_RIM_VELOCITY_COUNT, noteVelocity, timeStamp);
			//}

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

DrumSamplerAudioProcessor::InstrumentPack::InstrumentPack(String instrumentName, int velocityCount, DrumSamplerAudioProcessor* processor) {
	this->velocityCount = velocityCount;
	this->instrumentName = instrumentName;
	this->processor = processor;
}

void DrumSamplerAudioProcessor::InstrumentPack::createBuffers() {
	this->micPointers = ((AudioSampleBuffer***)calloc(MIC_COUNT, sizeof(AudioSampleBuffer**)));
	
	for (int micNumber = 0; micNumber < MIC_NAMES->length();micNumber++) {
		String micName = MIC_NAMES[micNumber];
		bool arrayCreated = 0;

		for (int velocityNumber = 0; velocityNumber < this->velocityCount; velocityNumber++) {
			String velocityName;
			velocityName.append("v", 1);
			velocityName.append(String(velocityNumber + 1),1);
			
			for (int versionNumber = 0; versionNumber < NUM_OF_SAME_SAMPLE; versionNumber++) {			
				if (micPointers[micNumber] == 0) {
					micPointers[micNumber]=(AudioSampleBuffer**)calloc(NUM_OF_SAME_SAMPLE*this->velocityCount, sizeof(AudioSampleBuffer*));
				}

				String version;
				version.append("(", 1);
				version.append(String(versionNumber + 1),1);
				version.append((")"),1);

				std::unique_ptr<AudioFormatReaderSource> readerSource;
				File newFile(String(processor->getSamplesFolder()->getFullPathName() + "\\" + instrumentName + " " + MIC_NAMES[micNumber] + " " + velocityName + " " + version + ".wav"));
				
				if (newFile.existsAsFile()) {
					
					std::unique_ptr<AudioFormatReader> reader(this->processor->formatManager.createReaderFor(newFile));
					AudioSampleBuffer *newBuffer = new AudioSampleBuffer(1, reader->lengthInSamples);
					reader->read(newBuffer, 0, reader->lengthInSamples, 0, true, false);
					Range<float> range = newBuffer->findMinMax(0, 0, reader->lengthInSamples);
					float max = std::max(abs(range.getStart()), abs(range.getEnd()));
					newBuffer->applyGain(1 / max);
					newBuffer->applyGainRamp(0, 10, 0, 1);
					//TODO:Delete testint
					int testint = (velocityNumber*NUM_OF_SAME_SAMPLE) + (versionNumber);
					micPointers[micNumber][(velocityNumber*NUM_OF_SAME_SAMPLE) + (versionNumber)] = newBuffer;
				}
				else {

					if (velocityNumber == 0 && versionNumber == 0) {
						delete this->micPointers[micNumber];
						this->micPointers[micNumber] = 0;
						break;
					}
					else {
						micPointers[micNumber][(velocityNumber*NUM_OF_SAME_SAMPLE) + (versionNumber)] = new AudioSampleBuffer();
					}
				}
				if (micPointers[micNumber] == 0) break;
			}
			if (micPointers[micNumber] == 0) break;
		}
	}
}

void DrumSamplerAudioProcessor::InstrumentPack::fillBuffer(int velocity, AudioSampleBuffer* bufferToFill) {

}
