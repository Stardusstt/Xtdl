#include "CLI.h"
#include "Converter.h"


CLI::CLI()
{

}

CLI::~CLI()
{
}

void CLI::ConsoleOut( string command , string filename )
{

	using namespace boost::process ;


	Converter converter ;
	ipstream temp ;
	string cli_string ;
	

	child ytdl_shell( command , std_out > temp );

	while ( getline( temp , cli_string ) ) // get word from temp to cli_string until eof
	{

		converter.ConvertState( cli_string );

		cout << "                                                                           ";
		cout << "\r";
		cout << " " << filename << setw( 15 )
			 << converter.state() << setw( 15 )
			 << converter.speed() << setw( 10 )
			 << converter.eta() ;
		cout << "\r"; // back to line begin

	}

	converter.state( "Finished" );
	cout << "                                                                           ";
	cout << "\r";
	cout << " " << filename << setw( 15 )
		 << converter.state() << setw( 15 )
		 << converter.speed() << setw( 10 )
		 << converter.eta() ;
	
}
