#include "ByteByClkAnalyzerSettings.h"
#include <AnalyzerHelpers.h>
#include <LogicPublicTypes.h>


ByteByClkAnalyzerSettings::ByteByClkAnalyzerSettings()
    : data_channel(UNDEFINED_CHANNEL),
      clock_channel(UNDEFINED_CHANNEL),
      valid_on_falling(false),
      data_interface(),
      clock_interface(),
      vof_interface() {
  data_interface.SetTitleAndTooltip("Data", "Data channel");
  data_interface.SetChannel(data_channel);

  clock_interface.SetTitleAndTooltip("Clock", "Clock channel");
  clock_interface.SetChannel(clock_channel);

  vof_interface.SetTitleAndTooltip("Bits are valid on falling edge",
                                             "Bits are valid on falling edge -> Analyzer starts with rising edge");
  vof_interface.SetValue(valid_on_falling);

  AddInterface(&data_interface);
  AddInterface(&clock_interface);
  AddInterface(&vof_interface);

  AddExportOption(0, "Export as text/csv file");
  AddExportExtension(0, "text", "txt");
  AddExportExtension(0, "csv", "csv");

  ClearChannels();
  AddChannel(data_channel, "Data", false);
  AddChannel(clock_channel, "Clock", false);
}

ByteByClkAnalyzerSettings::~ByteByClkAnalyzerSettings() {
}

bool ByteByClkAnalyzerSettings::SetSettingsFromInterfaces() {
  data_channel = data_interface.GetChannel();
  clock_channel = clock_interface.GetChannel();
  valid_on_falling = vof_interface.GetValue();

  ClearChannels();
  AddChannel(data_channel, "Data", true);
  AddChannel(clock_channel, "Clock", true);

  return true;
}

void ByteByClkAnalyzerSettings::UpdateInterfacesFromSettings() {
  data_interface.SetChannel(data_channel);
  clock_interface.SetChannel(clock_channel);
  vof_interface.SetValue(valid_on_falling);
}

void ByteByClkAnalyzerSettings::LoadSettings(const char* settings) {
  SimpleArchive text_archive;
  text_archive.SetString(settings);

  text_archive >> data_channel;
  text_archive >> clock_channel;
  text_archive >> valid_on_falling;

  ClearChannels();
  AddChannel(data_channel, "Data", true);
  AddChannel(clock_channel, "Clock", true);

  UpdateInterfacesFromSettings();
}

const char* ByteByClkAnalyzerSettings::SaveSettings() {
  SimpleArchive text_archive;

  text_archive << data_channel;
  text_archive << clock_channel;
  text_archive << valid_on_falling;

  return SetReturnString(text_archive.GetString());
}
