#include "ByteByClkAnalyzer.h"
#include "ByteByClkAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

ByteByClkAnalyzer::ByteByClkAnalyzer()
    : Analyzer2(), mSettings(), mSimulationInitilized(false) {
  SetAnalyzerSettings(&mSettings);
}

ByteByClkAnalyzer::~ByteByClkAnalyzer() {
  KillThread();
}

void ByteByClkAnalyzer::SetupResults() {
  // SetupResults is called each time the analyzer is run. Because the same instance can
  // be used for multiple runs, we need to clear the results each time.
  mResults.reset(new ByteByClkAnalyzerResults(this, &mSettings));
  SetAnalyzerResults(mResults.get());
  mResults->AddChannelBubblesWillAppearOn(mSettings.mInputChannel);
}

void ByteByClkAnalyzer::WorkerThread() {
  mSampleRateHz = GetSampleRate();

  mSerial = GetAnalyzerChannelData(mSettings.mInputChannel);

  if(mSerial->GetBitState() == BIT_LOW)
    mSerial->AdvanceToNextEdge();

  U32 samples_per_bit = mSampleRateHz; // / mSettings.mBitRate;
  U32 samples_to_first_center_of_first_data_bit =
      1; // U32( 1.5 * double( mSampleRateHz ) / double( mSettings.mBitRate ) );

  for(;;) {
    U8 data = 0;
    U8 mask = 1 << 7;

    mSerial->AdvanceToNextEdge(); // falling edge -- beginning of the start bit

    U64 starting_sample = mSerial->GetSampleNumber();

    mSerial->Advance(samples_to_first_center_of_first_data_bit);

    for(U32 i = 0; i < 8; i++) {
      // let's put a dot exactly where we sample this bit:
      mResults->AddMarker(mSerial->GetSampleNumber(), AnalyzerResults::Dot,
                          mSettings.mInputChannel);

      if(mSerial->GetBitState() == BIT_HIGH)
        data |= mask;

      mSerial->Advance(samples_per_bit);

      mask = mask >> 1;
    }


    // we have a byte to save.
    Frame frame;
    frame.mData1 = data;
    frame.mFlags = 0;
    frame.mStartingSampleInclusive = starting_sample;
    frame.mEndingSampleInclusive = mSerial->GetSampleNumber();

    mResults->AddFrame(frame);
    mResults->CommitResults();
    ReportProgress(frame.mEndingSampleInclusive);
  }
}

bool ByteByClkAnalyzer::NeedsRerun() {
  return false;
}

U32 ByteByClkAnalyzer::GenerateSimulationData(
    U64 minimum_sample_index, U32 device_sample_rate,
    SimulationChannelDescriptor** simulation_channels) {
  if(mSimulationInitilized == false) {
    mSimulationDataGenerator.Initialize(GetSimulationSampleRate(), &mSettings);
    mSimulationInitilized = true;
  }

  return mSimulationDataGenerator.GenerateSimulationData(
      minimum_sample_index, device_sample_rate, simulation_channels);
}

U32 ByteByClkAnalyzer::GetMinimumSampleRateHz() {
  return 1; // mSettings.mBitRate * 4;
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
