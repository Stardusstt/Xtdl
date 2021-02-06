#include "Converter.h"


Converter::Converter()
{

}

Converter::~Converter()
{
}

void Converter::ConvertState( string input )
{

	smatch result;
	
	//
	// [youtube] 7kmY6QOFMGg: Downloading webpage
	// 
	regex regex_youtube( "youtube" ); // match "youtube"
	if ( regex_search( input , regex_youtube ) )
	{

		regex regex_youtube_state( ":(.*)" ); // match " Downloading webpage" after ":"
		if ( regex_search( input , result , regex_youtube_state ) )
		{
			state_ = result[1] ; // Group 1.
		}
		
		return ;

	}
	
	//
	// [download] Destination: Location\filename.m4a
	// [download]  16.5% of 6.05MiB at  1.33MiB/s ETA 00:03
	// [download] 100% of 6.05MiB in 00:02
	//
	regex regex_download( "download" ); // match "download"
	if ( regex_search( input , regex_download ) )
	{

		regex regex_state( "\\d+\\.?\\d\\%" ); //  / \d+\.?\d\% /  match "16.5%"
		if ( regex_search( input , result , regex_state ) )
		{
			state_ = result[0]; // Full match
		}

		regex regex_speed( "\\d+\\.\\w+\\/." ); //  / \d+\.\w+\/. /  match "1.33MiB/s"
		if ( regex_search( input , result , regex_speed ) )
		{
			speed_ = result[0]; // Full match
		}

		regex regex_eta( "ETA.(\\d+:\\d+)" ); //  / ETA.(\d+:\d+) /  match "00:03"
		if ( regex_search( input , result , regex_eta ) )
		{
			eta_ = result[1]; // Group 1.
		}
		
		return ;

	}

	//
	// [ffmpeg] Destination: Location\filename.wav
	//
	regex regex_ffmpeg( "ffmpeg" ); // match "ffmpeg"
	if ( regex_search( input , regex_ffmpeg ) )
	{
		state_ = "Converting";
		speed_ = "";
		eta_ = "";

		return ;

	}

	//
	// Deleting original file Location\filename.m4a (pass -k to keep)
	//
	regex regex_deleting( "Deleting" ); // match "Deleting"
	if ( regex_search( input , regex_deleting ) )
	{
		state_ = "Cleaning Temp Files";
		speed_ = "";
		eta_ = "";

		return ;

	}
	
}

string Converter::ConvertCommand
( string filename , string url , string download_type , string format , string path )
{
	stringstream command_stream ;
	string command_out;

	if ( download_type == "v+a" ) // video + audio
	{
		// 
	}

	if ( download_type == "a" ) // audio only
	{

		if ( format == "original" )
		{

			command_stream << "youtube-dl  --newline"
						   << "  --config-location ./youtube-dl.conf"
						   << "  --format  bestaudio  --extract-audio"

						   //  --output " PATH/name.%(ext)s "
						   << "  --output \"" << path << "/" << filename << ".%(ext)s\" "
						   << url ;

			getline( command_stream , command_out );

			return command_out ;
		}

		if ( format == "wav" )
		{

			command_stream << "youtube-dl  --newline"
						   << "  --config-location ./youtube-dl.conf"

						   // --audio-format wav
						   << "  --format  bestaudio  --extract-audio  --audio-format wav"

						   //  --output " PATH/name.%(ext)s "
						   << "  --output \"" << path << "/" << filename << ".%(ext)s\" "
						   << url ;

			getline( command_stream , command_out );

			return command_out ;
		}

	}

	return "download_type Error" ;

}

string Converter::state() const
{
	return state_ ;
}

string Converter::speed() const
{
	return speed_ ;
}

string Converter::eta() const
{
	return eta_ ;
}

void Converter::state( string state )
{
	state_ = std::move( state );
}

void Converter::speed( string speed )
{
	speed_ = std::move( speed );
}

void Converter::eta( string eta )
{
	eta_ = std::move( eta );
}
