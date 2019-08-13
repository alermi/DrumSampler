/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <list>
#include<iterator>
using namespace std;
//==============================================================================
/**
*/
const int MIC_COUNT = 12;
const String MIC_NAMES[12] = { "floor_tom_1", "floor_tom_2", "kick_in", "kick_out",
			"mono_room", "overhead", "rack_tom", "ride", "room", "snare_bottom", "snare_top", "wide_room"};
class DrumSamplerAudioProcessor  : public AudioProcessor
{
public:
	
	
    //==============================================================================
    DrumSamplerAudioProcessor();
    ~DrumSamplerAudioProcessor();

	bool createBuffers(AudioSampleBuffer ** sampleBuffersToFill, String instrumentName, vector<String> micNames, vector<String> velocityNames);

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
	File *getSamplesFolder() { return samplesFolder; };
	void triggerInstrument(AudioBuffer<float> *bufferToFill, AudioSampleBuffer** instrumentSamples, vector<float> micGains, int numLevels, float noteVelocity, int timeStamp);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	
	//bool createBuffers(AudioSampleBuffer** sampleBuffersToFill, String instrumentName, vector<String> micNames, vector<String> velocityNames);

	File * samplesFolder;
	AudioProcessorValueTreeState parameters;
protected:
	class IteratorPack {
	public:
		float* address;
		float velocity;
		int samplesLeft;
		bool isHiHatOpen;
		IteratorPack(float* address, float velocity, int samplesLeft, bool isHiHatOpen) {
			this->address = address;
			this->velocity = velocity;
			this->samplesLeft = samplesLeft;
			this->isHiHatOpen = isHiHatOpen;
		}
	};

	class InstrumentPack {
	public:
		String instrumentName;
		int velocityCount;
		AudioSampleBuffer*** micPointers;
		AudioSampleBuffer* tempBuffer;
		DrumSamplerAudioProcessor* processor;
		

		void createBuffers();
		void fillBuffer(int velocity, AudioSampleBuffer* bufferToFill);
		AudioSampleBuffer getBuffer();
		InstrumentPack(String instrumentName, int velocityCount, DrumSamplerAudioProcessor* processor);
	};
	
    //==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumSamplerAudioProcessor)
	
	AudioFormatManager formatManager;
	//float ***samples;
	
	//pointer to the sample left at and velocity value
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

	float roomFader;
	float masterFader;
	
};


