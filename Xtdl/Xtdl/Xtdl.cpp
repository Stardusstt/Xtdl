#include <iostream>
#include <cstdlib>
#include <string> 
#include <vector>
#include <thread>

#include "Update.h"
#include "Converter.h"
#include "CLI.h"

using namespace std ;


int main()
{

	int mod ;
	string url , filename , download_type , format , path , command_final , txt_name  ;
	vector<thread> download;
	Update update_1 ;
	Converter converter_1 ;
	CLI cli_1 ;


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
		break ;
	case 2:
		goto ReadFromTxt ;
		break ;
	case 3:
		update_1.UpdateYoutube_dl() ;
		goto Start ;
		break ;
	default:
		goto Start ;
		break ;
	}

	//
SingleDownload:

	system( "cls" );
	url = "";
	filename = "";
	download_type = "";
	format = "";
	path = "";
	command_final = "";


	// URL
	cout << endl << " URL: ";
	cin >> url ;
	cout << endl;

	// Name
	cout << endl << " Name: ";
	cin.ignore( 10000 , '\n' ); // clean buffer
	getline( cin , filename );
	cout << endl;

	// Download Type
	cout << endl << " (v+a) Video + Audio "
		<< endl << " (a)	Audio Only "
		<< endl << " Download Type : " ;
	cin >> download_type ;
	cout << endl;

	// Format
	cout << endl << " (original) Original "
		<< endl << " (wav)		 WAV "
		<< endl << " Format : " ;
	cin >> format ;
	cout << endl;

	// Path
	cout << endl << " Path: ";
	cin.ignore( 10000 , '\n' ); // clean buffer
	getline( cin , path );
	cout << endl;

	command_final = converter_1.ConvertCommand( filename , url , download_type , format , path ) ;

	// create a thread for OutConsole
	download.emplace_back( thread( &CLI::OutConsole , &cli_1 , command_final , filename ) ) ;
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















	goto ReadFromTxt ;

}




