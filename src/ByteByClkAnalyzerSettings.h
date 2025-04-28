#ifndef BYTEBYCLK_ANALYZER_SETTINGS
#define BYTEBYCLK_ANALYZER_SETTINGS

#include <AnalyzerSettingInterface.h>
#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class ByteByClkAnalyzerSettings : public AnalyzerSettings {
public:
  ByteByClkAnalyzerSettings();
  virtual ~ByteByClkAnalyzerSettings();

  virtual bool SetSettingsFromInterfaces();
  void UpdateInterfacesFromSettings();
  virtual void LoadSettings(const char* settings);
  virtual const char* SaveSettings();


  Channel data_channel;
  Channel clock_channel;
  bool valid_on_falling;

protected:
  AnalyzerSettingInterfaceChannel data_interface;
  AnalyzerSettingInterfaceChannel clock_interface;
  AnalyzerSettingInterfaceBool vof_interface;
};

#endif // BYTEBYCLK_ANALYZER_SETTINGS
