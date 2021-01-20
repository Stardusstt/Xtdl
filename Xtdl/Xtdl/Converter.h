#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

#include "targetver.h"
#include <boost/process.hpp>

using namespace std ;


class Converter
{
public:

	Converter();
	~Converter();

	void ConvertState( string s_in );
	string ConvertCommand
	( string filename_in , string url_in , string download_type , string format , string path );

	string get_state();
	string get_speed();
	string get_eta();
	void set_state( string s_in );
	void set_speed( string s_in );
	void set_eta( string s_in );

private:

	string state , speed , eta , input ;

};

