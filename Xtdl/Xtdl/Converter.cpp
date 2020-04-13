#include "Converter.h"


Converter::Converter()
{

}

Converter::~Converter()
{
}

void Converter::ConvertState( string s_in )
{

	input = s_in ;

	smatch result;
	regex regex_youtube( "youtube" );
	regex regex_download( "download" );
	regex regex_state( "\\d+\\.?\\d\\%" );
	regex regex_speed( "\\d+\\.\\w+\\/." );
	regex regex_eta( "(ETA).(\\d+:\\d+)" );
	regex regex_ffmpeg( "ffmpeg" );
	regex regex_deleting( "Deleting" );


	// begin
	if ( regex_search( input , result , regex_youtube ) )
	{
		state = input;
	}

	if ( regex_search( input , result , regex_download ) )
	{

		if ( regex_search( input , result , regex_state ) )
		{
			state = result[0];
		}

		if ( regex_search( input , result , regex_speed ) )
		{
			speed = result[0];
		}

		if ( regex_search( input , result , regex_eta ) )
		{
			state = result[2];
		}

	}

	if ( regex_search( input , result , regex_ffmpeg ) )
	{
		state = "Converting";
		speed = "";
		eta = "";
	}

	if ( regex_search( input , result , regex_deleting ) )
	{
		state = "Deleting temp";
		speed = "";
		eta = "";
	}
	// end

}

string Converter::ConvertCommand
( string filename_in , string url_in , string download_type , string format , string path )
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

			command_stream << "youtube-dl  --newline  --config-location ./youtube-dl.conf"
				<< "  --format  bestaudio  --extract-audio"
				<< "  --output \""
				<< path << "/"
				<< filename_in << ".%(ext)s\"  "
				<< url_in ;

			getline( command_stream , command_out );

			return command_out ;

		}

		if ( format == "wav" )
		{

			command_stream << "youtube-dl  --newline  --config-location ./youtube-dl.conf"
				<< "  --format  bestaudio  --extract-audio  --audio-format wav" // --audio-format wav
				<< "  --output \""
				<< path << "/"
				<< filename_in << ".%(ext)s\"  "
				<< url_in ;

			getline( command_stream , command_out );

			return command_out ;

		}

	}

	return "download_type Error" ;

}

string Converter::get_state()
{
	return state ;
}

string Converter::get_speed()
{
	return speed ;
}

string Converter::get_eta()
{
	return eta ;
}

void Converter::set_state( string s_in )
{
	state = s_in ;
}

void Converter::set_speed( string s_in )
{
	speed = s_in ;
}

void Converter::set_eta( string s_in )
{
	eta = s_in ;
}
