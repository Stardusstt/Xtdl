#include <iostream>
#include <cstdlib>
#include <string> 
#include <vector>
#include <thread>
#include <limits>

#include "targetver.h"
#include "Update.h"
#include "Converter.h"
#include "CLI.h"

using namespace std ;


enum class EMode
{
	// Enumeration for mode
	// start from 1
	SingleDownload = 1 , ReadTxt , Update
};

void SingleDownload()
{

	Converter converter ;
	CLI cli ;
	vector<thread> download;
	string url , filename , download_type , format , path , command_final ;


	system( "cls" );

	// URL
	cout << endl << " URL: ";
	cin >> url ;

	// discards max() amount of characters until finds a delimiter
	// ( ignore() also discards the delimiter if it finds it )
	// prevent getline() skip input
	cin.ignore( std::numeric_limits<std::streamsize>::max() , '\n' );

	cout << endl;

	// Name
	cout << endl << " Name: ";
	getline( cin , filename );
	cout << endl;

	// Download Type
	cout << endl << " (v+a) Video + Audio "
		<< endl << " (a)	Audio Only "
		<< endl << " Download Type : " ;
	cin >> download_type ;
	cin.ignore( std::numeric_limits<std::streamsize>::max() , '\n' );
	cout << endl;

	// Format
	cout << endl << " (original) Original "
		<< endl << " (wav)		 WAV "
		<< endl << " Format : " ;
	cin >> format ;
	cin.ignore( std::numeric_limits<std::streamsize>::max() , '\n' );
	cout << endl;

	// Path
	cout << endl << " Path: ";
	getline( cin , path );
	cout << endl;

	// Convert Command
	command_final = converter.ConvertCommand( filename , url , download_type , format , path ) ;

	// create a thread for CLI::ConsoleOut
	download.emplace_back( thread( &CLI::ConsoleOut , &cli , command_final , filename ) ) ;
	download[download.size() - 1].join() ;

	cout << endl << endl ;
	system( "pause" );

}

void ChooseMode( EMode eMode )
{

	Update update;

	switch ( eMode )
	{
	case EMode::SingleDownload:
		SingleDownload(); // run SingleDownload
		break ;
	case EMode::ReadTxt:
		//
		cout << "ReadTxt";
		system( "pause" );
		break ;
	case EMode::Update:
		update.UpdateYoutube_dl(); // run UpdateYoutube_dl
		break ;
	default:
		//
		cout << "default";
		system( "pause" );
		break ;
	}

}

int main()
{

	EMode eMode;
	Update update ;
	int mode ;


	while ( 1 )
	{

		system( "cls" );

		update.GetVersion() ;

		cout << endl << " (1) Single download "
			<< endl << " (2) Reading from txt "
			<< endl << " (3) Update youtube-dl "
			<< endl
			<< endl << " Choose the number : " ;
		cin >> mode;

		eMode = static_cast<EMode>( mode ); // int to enum 

		ChooseMode( eMode );

	}

}




