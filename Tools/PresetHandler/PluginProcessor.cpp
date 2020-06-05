/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NanoAudioProcessor::NanoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
 {
    for (auto kk = 0; kk < kNumberOfVoices; ++kk)
    //for (auto kk = 0; kk < 1; ++kk)
    {
        m_synth.addVoice(new NanoVoice());
    }
    m_sound =  new NanoSound();
    //m_synth.addSound(*m_pSound);


    m_synth.addSound(m_sound);
	
	m_filterparams.addParameter(m_paramVector);

	m_parameterVTS = std::make_unique<AudioProcessorValueTreeState>(*this, nullptr, Identifier("NanoVTS"),
		AudioProcessorValueTreeState::ParameterLayout(m_paramVector.begin(), m_paramVector.end()));

	m_presets.setAudioValueTreeState(m_parameterVTS.get());
	m_presets.loadAllUserPresets();


	m_sound->m_cutoff = m_parameterVTS->getRawParameterValue(paramCutoff.ID);
	m_sound->m_reso = m_parameterVTS->getRawParameterValue(paramResonance.ID);
	m_parameterVTS->state.setProperty("version", JucePlugin_VersionString, nullptr);
}

NanoAudioProcessor::~NanoAudioProcessor()
{
}

//==============================================================================
const String NanoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NanoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NanoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NanoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NanoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NanoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NanoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NanoAudioProcessor::setCurrentProgram (int index)
{
}

const String NanoAudioProcessor::getProgramName (int index)
{
    return {};
}

void NanoAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NanoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    m_synth.prepareToPlay(sampleRate, samplesPerBlock);

/*	String in("Lala");
	ValueTree vt = m_presets.getPreset(in);
	String temp = vt.getProperty("presetname");

	if (in == temp)
		m_parameterVTS->replaceState(vt);
//*/
}

void NanoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NanoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void NanoAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    m_keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
    m_synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool NanoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NanoAudioProcessor::createEditor()
{
    return static_cast<AudioProcessorEditor*> (new NanoAudioProcessorEditor(*this, *m_parameterVTS, m_presets));
}

//==============================================================================
void NanoAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	auto state = m_parameterVTS->copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void NanoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(m_parameterVTS->state.getType()))
			m_parameterVTS->replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NanoAudioProcessor();
}
