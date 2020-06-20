/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <iterator>
#include "NoteSound.h"
#include "ParameterBuilder.h"
#include "MicController.h"

using namespace std;
//==============================================================================
/**
*/
class DrumSamplerAudioProcessor  : public AudioProcessor
{
public:

	
    //==============================================================================
    DrumSamplerAudioProcessor();
    ~DrumSamplerAudioProcessor();


	//==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
	//void triggerInstrument(AudioBuffer<float> *bufferToFill, AudioSampleBuffer** instrumentSamples, vector<float> micGains, int numLevels, float noteVelocity, int timeStamp);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	
	//bool createBuffers(AudioSampleBuffer** sampleBuffersToFill, String instrumentName, vector<String> micNames, vector<String> velocityNames);


protected:

	
    //==============================================================================
	
	//float ***samples;
	
	//pointer to the sample left at and velocity value
	NoteSound* kickPack;
	FileManager* fileManager;
	AudioFormatManager* formatManager;
	list<IteratorPack>* iterators;
	AudioSampleBuffer** kickSampleBuffers;
	AudioSampleBuffer** snareSampleBuffers;
	AudioSampleBuffer** snare_rimSampleBuffers;
	AudioSampleBuffer** chinaSampleBuffers;
	AudioSampleBuffer** crash_altSampleBuffers;
	AudioSampleBuffer** crash_mainSampleBuffers;
	AudioSampleBuffer** floor_tomSampleBuffers;
	AudioSampleBuffer** rack_tomSampleBuffers;
	AudioSampleBuffer** hi_hat_closedSampleBuffers;
	AudioSampleBuffer** hi_hat_openSampleBuffers;
	AudioSampleBuffer** rideSampleBuffers;
	AudioSampleBuffer** stackSampleBuffers;
	std::map<int, NoteSound*> instrumentMap;
	std::map<String, String> parameterTreeMap;

	float roomFader;
	float masterFader;
private:
	AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
	AudioProcessorValueTreeState treeState;
	MicController micController{ &treeState };
	foleys::MagicProcessorState magicState{ *this, treeState };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumSamplerAudioProcessor)
};


