#include "Converter.h"


Converter::Converter()
{

}

Converter::~Converter()
{
}

void Converter::GetState( string s_in )
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

void Converter::CommandConvert( string command_in , string filename_in )
{

	using namespace boost::process ;


	ipstream output;
	//
	//boost::filesystem::path output = "output.txt";
	//
	child ytdl_shell( command_in , std_out > output );

	string shell_string ;

	while ( getline( output , shell_string ) ) // get word from output to shell_string
	{

		GetState( shell_string );

		cout << "                                                                                  ";
		cout << "\r";
		cout << " " << filename_in << ".wav" << setw( 16 )
			<< state << setw( 15 )
			<< speed << setw( 10 )
			<< eta ;
		cout << "\r"; // back to line begin

	}

	state = "Finished";
	cout << "                                                                                 ";
	cout << "\r";
	cout << " " << filename_in << ".wav" << setw( 16 )
		<< state << setw( 15 )
		<< speed << setw( 10 )
		<< eta ;

}
