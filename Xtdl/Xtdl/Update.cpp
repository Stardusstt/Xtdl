#include "Update.h"


Update::Update()
{

	//xtdl_version = "";
	//youtube_dl_version = "";
	//ffmpeg_version = "";

}

Update::~Update()
{
}

void Update::UpdateYoutube_dl()
{

	using namespace boost::process ;


	ipstream temp ; // create pipestream 
	string cli_string ;


	child youtube_dl_shell( "youtube-dl --update" , std_out > temp );

	while ( getline( temp , cli_string ) ) // get word from temp to cli_string until eof
	{
		cout << endl << cli_string << endl ;
	}

	cout << endl;
	system( "pause" );

}

void Update::GetVersion()
{

	using namespace boost::process ;

	//  xtdl
	xtdl_version = "2021.2.7" ;

	cout << "Xtdl : " << xtdl_version ;
	cout << endl;

	//  youtube-dl
	ipstream output_youtube_dl;

	child youtube_dl_shell( "youtube-dl --version" , std_out > output_youtube_dl );

	getline( output_youtube_dl , youtube_dl_version ); // only get first line

	cout << "youtube-dl : " << youtube_dl_version ;
	cout << endl;

	//  ffmpeg
	ipstream output_ffmpeg;

	child ffmpeg_shell( "ffmpeg -version" , std_out > output_ffmpeg );

	getline( output_ffmpeg , ffmpeg_version ); // only get first line

	cout << "ffmpeg : " << ffmpeg_version ;
	cout << endl;

}

