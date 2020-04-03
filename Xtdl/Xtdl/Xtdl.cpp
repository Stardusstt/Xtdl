#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream> 
#include <vector>
#include <thread>

#include "Update.h"
#include "Converter.h"

using namespace std ;


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




