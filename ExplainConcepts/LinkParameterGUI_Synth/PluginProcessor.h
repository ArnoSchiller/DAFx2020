/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

//#include <JuceHeader.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "NanoSound.h"
#include "NanoSynth.h"
#include "NanoVoice.h"
#include "MoogLadder.h"

//#include "PluginEditor.h"

//==============================================================================
/**
*/


class NanoAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NanoAudioProcessor();
    ~NanoAudioProcessor();

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
    MidiKeyboardState m_keyboardState;
private:
    static const int kNumberOfVoices = 16;
    NanoSynth m_synth;
    NanoSound* m_sound;

    std::unique_ptr<AudioProcessorValueTreeState> m_parameterVTS;
    std::vector <std::unique_ptr<RangedAudioParameter>> m_parameterVector;

    MoogLadderParameter m_filterparams;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NanoAudioProcessor)
};
