#include "ByteByClkAnalyzer.h"
#include "ByteByClkAnalyzerSettings.h"
#include <AnalyzerChannelData.h>
#include <LogicPublicTypes.h>

ByteByClkAnalyzer::ByteByClkAnalyzer() : Analyzer2(), settings(), sim_initilized(false) {
  SetAnalyzerSettings(&settings);
}

ByteByClkAnalyzer::~ByteByClkAnalyzer() {
  KillThread();
}

void ByteByClkAnalyzer::SetupResults() {
  // SetupResults is called each time the analyzer is run. Because the same instance can
  // be used for multiple runs, we need to clear the results each time.
  results.reset(new ByteByClkAnalyzerResults(this, &settings));
  SetAnalyzerResults(results.get());
  results->AddChannelBubblesWillAppearOn(settings.data_channel);
}

void ByteByClkAnalyzer::WorkerThread() {
  sample_rate = GetSampleRate();

  data_ch = GetAnalyzerChannelData(settings.data_channel);
  clock_ch = GetAnalyzerChannelData(settings.clock_channel);

  if(!data_ch || !clock_ch)
    return;

  if(clock_ch->GetBitState() == settings.start_on_rising)
    clock_ch->AdvanceToNextEdge();

  for(;;) {
    U8 data = 0;
    U8 mask = 1 << 7;

    clock_ch->AdvanceToNextEdge();
    U64 starting_sample = clock_ch->GetSampleNumber();
    data_ch->AdvanceToAbsPosition(starting_sample);

    for(U32 i = 0; i < 8; i++) {
      clock_ch->AdvanceToNextEdge();
      data_ch->AdvanceToAbsPosition(clock_ch->GetSampleNumber());

      if(data_ch->GetBitState() == BIT_LOW) {
        results->AddMarker(data_ch->GetSampleNumber(), AnalyzerResults::Zero,
                           settings.data_channel);
      } else {
        results->AddMarker(data_ch->GetSampleNumber(), AnalyzerResults::One,
                           settings.data_channel);
      }
      if(data_ch->GetBitState() == BIT_HIGH)
        data |= mask;

      clock_ch->AdvanceToNextEdge();

      mask = mask >> 1;
    }


    // we have a byte to save.
    Frame frame;
    frame.mData1 = data;
    frame.mFlags = 0;
    frame.mStartingSampleInclusive = starting_sample;
    frame.mEndingSampleInclusive = data_ch->GetSampleNumber();

    results->AddFrame(frame);
    results->CommitResults();
    ReportProgress(frame.mEndingSampleInclusive);
  }
}

bool ByteByClkAnalyzer::NeedsRerun() {
  return false;
}

U32 ByteByClkAnalyzer::GenerateSimulationData(
    U64 minimum_sample_index, U32 device_sample_rate,
    SimulationChannelDescriptor** simulation_channels) {
  if(sim_initilized == false) {
    sim_data_gen.Initialize(GetSimulationSampleRate(), &settings);
    sim_initilized = true;
  }

  return sim_data_gen.GenerateSimulationData(minimum_sample_index, device_sample_rate,
                                             simulation_channels);
}

U32 ByteByClkAnalyzer::GetMinimumSampleRateHz() {
  return 1; // settings.mBitRate * 4;
}

const char* ByteByClkAnalyzer::GetAnalyzerName() const {
  return "ByteByClk";
}

const char* GetAnalyzerName() {
  return "ByteByClk";
}

Analyzer* CreateAnalyzer() {
  return new ByteByClkAnalyzer();
}

void DestroyAnalyzer(Analyzer* analyzer) {
  delete analyzer;
}
