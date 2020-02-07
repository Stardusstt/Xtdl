#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream> 
#include <vector>
#include <thread>
#include <iomanip>
#include <boost/process.hpp>
#include <boost/locale.hpp>
#include <regex>

using namespace std ;


void GetState( string s_in , string &state , string &speed , string &eta )
{

	smatch result;
	regex regex_youtube( "youtube" );
	regex regex_download( "download" );
	regex regex_state( "\\d+\\.?\\d\\%" );
	regex regex_speed( "\\d+\\.\\w+\\/." );
	regex regex_eta( "(ETA).(\\d+:\\d+)" );
	regex regex_ffmpeg( "ffmpeg" );
	regex regex_deleting( "Deleting" );


	// begin
	if ( regex_search( s_in , result , regex_youtube ) )
	{
		state = s_in;
	}

	if ( regex_search( s_in , result , regex_download ) )
	{

		if ( regex_search( s_in , result , regex_state ) )
		{
			state = result[0];
		}

		if ( regex_search( s_in , result , regex_speed ) )
		{
			speed = result[0];
		}

		if ( regex_search( s_in , result , regex_eta ) )
		{
			state = result[2];
		}

	}

	if ( regex_search( s_in , result , regex_ffmpeg ) )
	{
		state = "Converting";
		speed = "";
		eta = "";
	}

	if ( regex_search( s_in , result , regex_deleting ) )
	{
		state = "Deleting temp";
		speed = "";
		eta = "";
	}
	// end

}

void CommandConvert( string command , string filename )
{
	
	using namespace boost::process ;
	

	ipstream output;
	//
	//boost::filesystem::path output = "output.txt";
	//
	child ytdl_shell( command , std_out > output );

	string state , speed , eta , s_in ;
	
	while ( getline( output , s_in ) ) // get word from output to s_in
	{

		GetState( s_in , state , speed , eta );




		cout << "                                                                                  ";
		cout << "\r";
		cout << " " << filename << ".wav" << setw( 16 ) 
			  << state << setw( 15 ) 
			  << speed << setw( 10 ) 
			  << eta ;
		cout << "\r"; // back to line begin

	}

	state = "Finished";
	cout << "                                                                                 ";
	cout << "\r";
	cout << " " << filename << ".wav" << setw( 16 ) 
		  << state << setw( 15 ) 
		  << speed << setw( 10 ) 
		  << eta ;

}


int main()
{

	int mod ;
	string filename , url , command_final , txt_name ;
	stringstream command;
	vector<thread> download;


//
Start:

	system( "cls" );
	cout << " Xtdl  ver 1.0.0" << endl ;
	cout << endl << " (1) Single download     (2) Reading from txt  : ";
	cin >> mod;
	cout << endl;

	switch ( mod )
	{
	case 1:
		goto SingleDownload ;
	case 2:
		goto ReadFromTxt ;
	default:
		goto Start ;
	}

//
SingleDownload:

	system( "cls" );
	url = "";
	filename = "";
	command_final = "";
	command.str( "" );
	command.clear();
	
	
	cout << endl << " URL: ";
	cin >> url;
	cout << endl;

	cout << endl << " Name: ";
	cin.ignore( 10000 , '\n' ); // clean buffer
	getline( cin , filename );
	cout << endl;
	
	// splice command
	command << "youtube-dl  --newline  -f  bestaudio  --extract-audio  --audio-format wav  --audio-quality 0  -o  \""
			<< filename 
			<< ".%(ext)s\"  "
			<< url;
	getline( command , command_final );

	download.push_back( thread( CommandConvert , command_final , filename ) ) ;
	download[download.size() - 1].join() ;

	cout << endl << endl ;
	system( "pause" );

	goto SingleDownload ;

//
ReadFromTxt:

	system( "cls" );
	url = "";
	filename = "";
	command_final = "";
	command.str( "" );
	command.clear();
	













	goto ReadFromTxt ;

}




