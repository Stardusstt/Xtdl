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

