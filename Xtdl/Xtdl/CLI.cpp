#include "CLI.h"
#include "Converter.h"


CLI::CLI()
{

}

CLI::~CLI()
{
}

void CLI::ConsoleOut( string command_in , string filename_in )
{

	using namespace boost::process ;


	Converter converter ;

	ipstream output;
	//
	//boost::filesystem::path output = "output.txt";
	//
	boost::process::child ytdl_shell( command_in , std_out > output );

	string shell_string ;

	while ( getline( output , shell_string ) ) // get word from output to shell_string
	{

		converter.ConvertState( shell_string );

		cout << "                                                                                  ";
		cout << "\r";
		cout << " " << filename_in << ".wav" << setw( 16 )
			<< converter.get_state() << setw( 15 )
			<< converter.get_speed() << setw( 10 )
			<< converter.get_eta() ;
		cout << "\r"; // back to line begin

	}

	converter.set_state( "Finished" );
	cout << "                                                                                 ";
	cout << "\r";
	cout << " " << filename_in << ".wav" << setw( 16 )
		<< converter.get_state() << setw( 15 )
		<< converter.get_speed() << setw( 10 )
		<< converter.get_eta() ;

}
