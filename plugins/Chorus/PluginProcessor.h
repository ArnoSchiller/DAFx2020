/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "LFO/LFO.h"
#include "SimpleChorus.h"

//==============================================================================
/**
*/
class SimpleChorusAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SimpleChorusAudioProcessor();
    ~SimpleChorusAudioProcessor();

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

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
		//Parameterhandling
	SimpleChorus m_chorus;
	std::vector<double> m_dataLeft;
	std::vector<double> m_dataRight;
	std::vector<double> m_dataOutLeft;
	std::vector<double> m_dataOutRight;

	std::unique_ptr<AudioProcessorValueTreeState> m_parameterVTS;
	std::vector < std::unique_ptr<RangedAudioParameter>> m_paramVector;

	LFOParameter m_lfoparams;
	std::atomic <float>* m_rate;
	float m_oldrate;
	std::atomic <float>* m_waveform;
	float m_oldwaveform;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleChorusAudioProcessor)
};
