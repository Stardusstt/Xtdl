// tool-youtube-dl.cpp: 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream> 
#include <io.h>
#include <fcntl.h>
#include <process.h>
using namespace std;
int main() {


	// Set mode:
	int result1 , result2;

	result1 = _setmode(_fileno(stdout), _O_U16TEXT);
	result2 = _setmode(_fileno(stdin), _O_U16TEXT);
	
	if ( (result1 || result2) == -1) {

		perror("Cannot set mode");
	
	}else{
	
		wcout << endl << " Successfully changed mode " << endl << endl ;
	
	}
	
	system("pause");
	

	wstring name, clear, url, cmdfinal;
	wstringstream cmd;

	start:


	system("cls");
	url = L"";
	name = L"";
	cmdfinal = L"";
	cmd.str(L"");
	cmd.clear();

	
	wcout << endl << " URL: ";
	wcin >> url;
	wcout << endl;

	wcout << endl << " Name: ";
	clear = L"\n";
	getline(wcin, clear);
	getline(wcin, name, L'\n');
	wcout << endl;
	
	cmd << L"start/min youtube-dl -o \"" << name << L".wav\" -f bestaudio --extract-audio --audio-format wav --audio-quality 0 " << url;

	getline(cmd, cmdfinal);

	_wsystem(cmdfinal.c_str());

	system("pause");

	goto start;






}


