#ifndef BYTEBYCLK_ANALYZER_SETTINGS
#define BYTEBYCLK_ANALYZER_SETTINGS

#include <AnalyzerSettingInterface.h>
#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class ByteByClkAnalyzerSettings : public AnalyzerSettings
{
public:
	ByteByClkAnalyzerSettings();
	virtual ~ByteByClkAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
  Channel mClockChannel;
  bool mStartOnRising;

protected:
	AnalyzerSettingInterfaceChannel	mInputChannelInterface;
	AnalyzerSettingInterfaceChannel	mClockChannelInterface;
  AnalyzerSettingInterfaceBool mStartOnRisingInterface;
};

#endif //BYTEBYCLK_ANALYZER_SETTINGS
