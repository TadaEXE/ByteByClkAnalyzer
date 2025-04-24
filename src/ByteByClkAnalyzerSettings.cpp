#include "ByteByClkAnalyzerSettings.h"
#include <AnalyzerHelpers.h>
#include <LogicPublicTypes.h>


ByteByClkAnalyzerSettings::ByteByClkAnalyzerSettings()
    : data_channel(UNDEFINED_CHANNEL),
      clock_channel(UNDEFINED_CHANNEL),
      start_on_rising(false),
      data_interface(),
      clock_interface(),
      sor_interface() {
  data_interface.SetTitleAndTooltip("Data", "Data channel");
  data_interface.SetChannel(data_channel);

  clock_interface.SetTitleAndTooltip("Clock", "Clock channel");
  clock_interface.SetChannel(clock_channel);

  sor_interface.SetTitleAndTooltip("Start on rising",
                                             "Start analyzing on rising edge of clock?");
  sor_interface.SetValue(start_on_rising);

  AddInterface(&data_interface);
  AddInterface(&clock_interface);
  AddInterface(&sor_interface);

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
  start_on_rising = sor_interface.GetValue();

  ClearChannels();
  AddChannel(data_channel, "Data", true);
  AddChannel(clock_channel, "Clock", true);

  return true;
}

void ByteByClkAnalyzerSettings::UpdateInterfacesFromSettings() {
  data_interface.SetChannel(data_channel);
  clock_interface.SetChannel(clock_channel);
  sor_interface.SetValue(start_on_rising);
}

void ByteByClkAnalyzerSettings::LoadSettings(const char* settings) {
  SimpleArchive text_archive;
  text_archive.SetString(settings);

  text_archive >> data_channel;
  text_archive >> clock_channel;
  text_archive >> start_on_rising;

  ClearChannels();
  AddChannel(data_channel, "Data", true);
  AddChannel(clock_channel, "Clock", true);

  UpdateInterfacesFromSettings();
}

const char* ByteByClkAnalyzerSettings::SaveSettings() {
  SimpleArchive text_archive;

  text_archive << data_channel;
  text_archive << clock_channel;
  text_archive << start_on_rising;

  return SetReturnString(text_archive.GetString());
}
