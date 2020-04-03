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

//
class Update
{
public:
	
	Update();
	~Update();
	
	void GetVersion();
	void UpdateYoutube_dl();

private:

	string xtdl_version , youtube_dl_version , ffmpeg_version ;

};

Update::Update()
{
	/*
	xtdl_version = "";
	youtube_dl_version = "";
	ffmpeg_version = "";
	*/
}

Update::~Update()
{
}

void Update::UpdateYoutube_dl() 
{

	using namespace boost::process ;


	ipstream output ;

	child youtube_dl_shell( "youtube-dl --update" , std_out > output );

	string s_out ;

	while ( getline( output , s_out ) ) // get word from output to s_out until eof
	{

		cout << s_out << endl ;

	}

	cout << endl;
	system( "pause" );

}

void Update::GetVersion()
{

	using namespace boost::process ;

	//  xtdl
	xtdl_version = "2020.4.2" ;

	cout << "Xtdl : " << xtdl_version ;
	cout << endl;

	//  youtube-dl
	ipstream output_youtube_dl;

	child youtube_dl_shell( "youtube-dl --version" , std_out > output_youtube_dl );

	getline( output_youtube_dl , youtube_dl_version );

	cout << "youtube-dl : " << youtube_dl_version ;
	cout << endl;

	//  ffmpeg
	ipstream output_ffmpeg;

	child ffmpeg_shell( "ffmpeg -version" , std_out > output_ffmpeg );

	getline( output_ffmpeg , ffmpeg_version );

	cout << "ffmpeg : " << ffmpeg_version ;
	cout << endl;
	
}

//
class Converter
{
public:

	Converter();
	~Converter();

	void GetState( string s_in );
	void CommandConvert( string command_in , string filename_in );

private:

	string state , speed , eta , input ;
	
};

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

//


int main()
{

	int mod ;
	string filename , url , command_final , txt_name , xtdl , youtube_dl , ffmpeg ;
	stringstream command;
	vector<thread> download;
	Update update_1 ;
	Converter converter_1 ;



	//
Start:

	system( "cls" );


	update_1.GetVersion() ;


	cout << endl << " (1) Single download "
		 << endl << " (2) Reading from txt "
		 << endl << " (3) Update youtube-dl "
		 << endl
		 << endl << " Choose the number : " ;

	cin >> mod;
	cout << endl;

	switch ( mod )
	{
	case 1:
		goto SingleDownload ;
	case 2:
		goto ReadFromTxt ;
	case 3:
		update_1.UpdateYoutube_dl() ;
		goto Start ;
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

	download.emplace_back( thread( &Converter::CommandConvert , &converter_1 , command_final , filename ) ) ; // create a thread for CommandConvert
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




