#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
#include <regex>
#include <boost/process.hpp>

using namespace std ;


class Converter
{
public:

	Converter();
	~Converter();

	void GetState( string s_in );
	void CommandConvert( string command_in , string filename_in );

private:

	string state , speed , eta , input ;

};

