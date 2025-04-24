/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EnvelopeFilterPedalAudioProcessor::EnvelopeFilterPedalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif

apvts(*this,nullptr,"Params",createParams())
{
}

EnvelopeFilterPedalAudioProcessor::~EnvelopeFilterPedalAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout EnvelopeFilterPedalAudioProcessor::createParams(){
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // Sliders
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID({"SensitivityKnob",1}),"Sensitivity",-18.f,6.f,0.f));
      
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID({"MaxFreqKnob",1}),"MaxFreq",1000.f,20000.f,4000.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID({"MinFreqKnob",1}),"MinFreq",20.f,750.f,50.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID({"ResonanceKnob",1}),"Resonance",0.5f, 5.0f, 1.2f));
    
    // Buttons
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID({"BypassButton",1}),"Bypass",false));
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID({"SweepDirectionButton",1}),"SweepDirection",false));
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID({"FilterType",1}),"FilterType",false)); // Make into a 3 stage slider eventually
    
    return {params.begin(),params.end()};
    
}

//==============================================================================
const juce::String EnvelopeFilterPedalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EnvelopeFilterPedalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EnvelopeFilterPedalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EnvelopeFilterPedalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EnvelopeFilterPedalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EnvelopeFilterPedalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EnvelopeFilterPedalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EnvelopeFilterPedalAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EnvelopeFilterPedalAudioProcessor::getProgramName (int index)
{
    return {};
}

void EnvelopeFilterPedalAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EnvelopeFilterPedalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    filter.setFs(static_cast<float>(sampleRate));
    
}

void EnvelopeFilterPedalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EnvelopeFilterPedalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void EnvelopeFilterPedalAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    bool isCurrentlyBypassed = isBypassed.load();
    
    if (isCurrentlyBypassed)
        return;
    
    float currentSensitivity = sensitivitySliderValue.load();  
    minFreq = minFreqSliderValue.load();
    maxFreq = maxFreqSliderValue.load();
    resonance = resonanceSliderValue.load();
    
    
  
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    int N = buffer.getNumSamples();
    
    filter.setFreq(freqValue);
    filter.setQ(resonance);
    filter.setFilterType(filterType);
    
    
    //float envelopeValue = envelope.calculatePeak(buffer, 0, N, peakAlpha);      // Change to togglable switch
    for (int channel = 0; channel < totalNumInputChannels; ++channel){
        
        envelopeValue = envelope.calculateRMS(buffer, channel, N);
        
    };
    
    float adjustedEnv = envelopeValue * sensitivity;
    
    cutoffFreq = minFreq + (maxFreq - minFreq) * adjustedEnv;
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        int count = 0;
        for (int n = 0; n < N; ++n){
            smoothedCutoff[channel] = 0.999f * smoothedCutoff[channel] + 0.001f * cutoffFreq;
            
            filter.setFreq(smoothedCutoff[channel]);

            float x = buffer.getWritePointer(channel)[n];
            float y = filter.processSample(x,channel);
            buffer.getWritePointer(channel)[n] = y;
        }
        
        //filter.processBuffer(channelData, N, channel);
        
    }
}

//==============================================================================
bool EnvelopeFilterPedalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EnvelopeFilterPedalAudioProcessor::createEditor()
{
    return new EnvelopeFilterPedalAudioProcessorEditor (*this);
}

//==============================================================================
void EnvelopeFilterPedalAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto currentState = apvts.copyState();
    
    std::unique_ptr<juce::XmlElement> xml (currentState.createXml());
    
    copyXmlToBinary(*xml, destData);
    
}

void EnvelopeFilterPedalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    
    juce::ValueTree newTree = juce::ValueTree::fromXml(*xml);
    
    apvts.replaceState(newTree);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EnvelopeFilterPedalAudioProcessor();
}
