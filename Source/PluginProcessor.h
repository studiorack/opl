/*
  ==============================================================================

    This file was initially auto-generated by the Introjucer.
	Now it is safe to edit.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <deque>
#include "../JuceLibraryCode/JuceHeader.h"
#include "hiopl.h"
#include "FloatParameter.h"


//==============================================================================
class AdlibBlasterAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AdlibBlasterAudioProcessor();
	void initPrograms();
	void applyPitchBend();
    ~AdlibBlasterAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    static const int MAX_INSTRUMENT_FILE_SIZE_BYTES = 1024;
	
	int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);
	void setEnumParameter (String name, int newValue);
	void setIntParameter (String name, int newValue);
	int getIntParameter (String name);
	int getEnumParameter (String name);
	bool getBoolParameter(String name);
	void loadInstrumentFromFile(String filename);
	void saveInstrumentToFile(String filename);
	void setParametersByRegister(int register_base, int op, uint8 value);

	void disableChannel(const int idx);
	void enableChannel(const int idx);
	void toggleChannel(const int idx);
	bool isChannelEnabled(const int idx) const;
	size_t nChannelsEnabled();
	const char* getChannelEnvelopeStage(int idx) const;

	void updateGuiIfPresent();

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

public:
    String lastLoadFile;
    int selectedIdxFile = -1;
private:
	Hiopl *Opl;
	std::vector<FloatParameter*> params;
	std::map<String, int> paramIdxByName;
	std::map<String, std::vector<float>> programs;
	std::vector<String> program_order;
	int i_program;
	bool velocity;
	static const int NO_NOTE=-1;
	static const char *PROGRAM_INDEX;
	int active_notes[Hiopl::CHANNELS + 1];		// keyed by 1-based channel index
	bool channel_enabled[Hiopl::CHANNELS + 1];  // keyed by 1-based channel index
	std::deque<int> available_channels;			// most recently freed at end
	std::deque<int> used_channels;				// most recently used at end
	float currentScaledBend;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdlibBlasterAudioProcessor)
};
#endif  // PLUGINPROCESSOR_H_INCLUDED
