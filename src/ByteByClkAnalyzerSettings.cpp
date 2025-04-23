#include "ByteByClkAnalyzerSettings.h"
#include <AnalyzerHelpers.h>
#include <LogicPublicTypes.h>


ByteByClkAnalyzerSettings::ByteByClkAnalyzerSettings()
    : mInputChannel( UNDEFINED_CHANNEL ),
      mClockChannel( UNDEFINED_CHANNEL ),
      mStartOnRising( false ),
      mInputChannelInterface(),
      mClockChannelInterface(),
      mStartOnRisingInterface()
{
    mInputChannelInterface.SetTitleAndTooltip( "Data", "Data channel" );
    mInputChannelInterface.SetChannel( mInputChannel );

    mClockChannelInterface.SetTitleAndTooltip( "Clock", "Clock channel" );
    mClockChannelInterface.SetChannel( mClockChannel );

    mStartOnRisingInterface.SetTitleAndTooltip( "Start on rising", "Start analyzing on rising edge of clock?" );
    mStartOnRisingInterface.SetValue( mStartOnRising );

    AddInterface( &mInputChannelInterface );
    AddInterface( &mClockChannelInterface );
    AddInterface( &mStartOnRisingInterface );

    AddExportOption( 0, "Export as text/csv file" );
    AddExportExtension( 0, "text", "txt" );
    AddExportExtension( 0, "csv", "csv" );

    ClearChannels();
    AddChannel( mInputChannel, "Data", false );
    AddChannel( mClockChannel, "Clock", false );
}

ByteByClkAnalyzerSettings::~ByteByClkAnalyzerSettings()
{
}

bool ByteByClkAnalyzerSettings::SetSettingsFromInterfaces()
{
    mInputChannel = mInputChannelInterface.GetChannel();
    mClockChannel = mClockChannelInterface.GetChannel();
    mStartOnRising = mStartOnRisingInterface.GetValue();

    ClearChannels();
    AddChannel( mInputChannel, "Data", true );
    AddChannel( mClockChannel, "Clock", true );

    return true;
}

void ByteByClkAnalyzerSettings::UpdateInterfacesFromSettings()
{
    mInputChannelInterface.SetChannel( mInputChannel );
    mClockChannelInterface.SetChannel( mClockChannel );
    mStartOnRisingInterface.SetValue( mStartOnRising );
}

void ByteByClkAnalyzerSettings::LoadSettings( const char* settings )
{
    SimpleArchive text_archive;
    text_archive.SetString( settings );

    text_archive >> mInputChannel;
    text_archive >> mClockChannel;
    text_archive >> mStartOnRising;

    ClearChannels();
    AddChannel( mInputChannel, "Data", true );
    AddChannel( mClockChannel, "Clock", true );

    UpdateInterfacesFromSettings();
}

const char* ByteByClkAnalyzerSettings::SaveSettings()
{
    SimpleArchive text_archive;

    text_archive << mInputChannel;
    text_archive << mClockChannel;
    text_archive << mStartOnRising;

    return SetReturnString( text_archive.GetString() );
}
