#ifndef BYTEBYCLK_SIMULATION_DATA_GENERATOR
#define BYTEBYCLK_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class ByteByClkAnalyzerSettings;

class ByteByClkSimulationDataGenerator {
public:
  ByteByClkSimulationDataGenerator();
  ~ByteByClkSimulationDataGenerator();

  void Initialize(U32 simulation_sample_rate, ByteByClkAnalyzerSettings* settings);
  U32 GenerateSimulationData(U64 newest_sample_requested, U32 sample_rate,
                             SimulationChannelDescriptor** simulation_channel);

protected:
  ByteByClkAnalyzerSettings* mSettings;
  U32 mSimulationSampleRateHz;

protected:
  void CreateSerialByte();
  std::string mSerialText;
  U32 mStringIndex;

  SimulationChannelDescriptor mSerialSimulationData;
};
#endif // BYTEBYCLK_SIMULATION_DATA_GENERATOR
