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

	void ConvertState( string input );
	string ConvertCommand
	( string filename , string url , string download_type , string format , string path );
	string state() const;
	string speed() const;
	string eta() const;
	void state( string state );
	void speed( string speed );
	void eta( string eta );

private:

	string state_ , speed_ , eta_ ;

};

