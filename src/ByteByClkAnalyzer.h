#ifndef BYTEBYCLK_ANALYZER_H
#define BYTEBYCLK_ANALYZER_H

#include "ByteByClkAnalyzerResults.h"
#include "ByteByClkAnalyzerSettings.h"
#include "ByteByClkSimulationDataGenerator.h"
#include <Analyzer.h>
#include <memory>

class ANALYZER_EXPORT ByteByClkAnalyzer : public Analyzer2 {
public:
  ByteByClkAnalyzer();
  virtual ~ByteByClkAnalyzer();

  virtual void SetupResults();
  virtual void WorkerThread();

  virtual U32 GenerateSimulationData(U64 newest_sample_requested, U32 sample_rate,
                                     SimulationChannelDescriptor** simulation_channels);
  virtual U32 GetMinimumSampleRateHz();

  virtual const char* GetAnalyzerName() const;
  virtual bool NeedsRerun();

protected:
  U32 get_samples_per_clock();
  ByteByClkAnalyzerSettings settings;
  std::unique_ptr<ByteByClkAnalyzerResults> results;
  AnalyzerChannelData* data_ch;
  AnalyzerChannelData* clock_ch;

  ByteByClkSimulationDataGenerator sim_data_gen;
  bool sim_initilized;

  U32 sample_rate;
  // Serial analysis vars:
  // U32 mSampleRateHz;
  // U32 mStartOfStopBitOffset;
  // U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer();
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer(Analyzer* analyzer);

#endif // BYTEBYCLK_ANALYZER_H
