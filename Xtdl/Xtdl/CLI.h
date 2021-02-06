#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>

#include "targetver.h"
#include <boost/process.hpp>

using namespace std ;


class CLI
{
public:

	CLI();
	~CLI();

	void ConsoleOut( string command , string filename );

private:


};

