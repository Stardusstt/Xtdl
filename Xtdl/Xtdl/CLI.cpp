#include "CLI.h"
#include "Converter.h"


CLI::CLI()
{

}

CLI::~CLI()
{
}

void CLI::OutConsole( string command_in , string filename_in )
{

	using namespace boost::process ;


	Converter converter_1 ;

	ipstream output;
	//
	//boost::filesystem::path output = "output.txt";
	//
	child ytdl_shell( command_in , std_out > output );

	string shell_string ;

	while ( getline( output , shell_string ) ) // get word from output to shell_string
	{

		converter_1.ConvertState( shell_string );

		cout << "                                                                                  ";
		cout << "\r";
		cout << " " << filename_in << ".wav" << setw( 16 )
			<< converter_1.get_state() << setw( 15 )
			<< converter_1.get_speed() << setw( 10 )
			<< converter_1.get_eta() ;
		cout << "\r"; // back to line begin

	}

	converter_1.set_state( "Finished" );
	cout << "                                                                                 ";
	cout << "\r";
	cout << " " << filename_in << ".wav" << setw( 16 )
		<< converter_1.get_state() << setw( 15 )
		<< converter_1.get_speed() << setw( 10 )
		<< converter_1.get_eta() ;

}
