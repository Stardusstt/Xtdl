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
	int result1, result2, result3;

	result1 = _setmode(_fileno(stdout), _O_WTEXT);
	result2 = _setmode(_fileno(stdin), _O_WTEXT);
	result3 = 0;

	if ((result1 || result2 || result3) == -1) {

		perror("Cannot set mode");

	}
	else {

		wcout << endl << " Successfully changed mode " << endl << endl;

	}

	system("pause");
	//

	//

	int count, mod;
	wstring name, clear, url, list, cmdfinal;
	wstringstream cmd;
	wchar_t filename[10];
	
	//

	//

	system("cls");
	wcout << endl << " (1)Command line    (2)File read  : ";
	wcin >> mod;
	wcout << endl;

	if (mod == 1)
	{
		goto commandline;
	}
	else
	{
		goto fileread;
	}

	//

	// 1)Command line
	commandline:


	system("cls");
	url = L"";
	name = L"";
	list = L"";
	list.clear();
	count = 1;
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

	cmd << L"start/min youtube-dl -o \"" << name << L".%(ext)s\" -f bestaudio --extract-audio --audio-format wav --audio-quality 0 " << url;

	getline(cmd, cmdfinal);

	_wsystem(cmdfinal.c_str());

	system("pause");


	goto commandline;



	// (2)File read
	fileread:


	system("cls");
	url = L"";
	name = L"";
	list = L"";
	list.clear();
	count = 1;
	cmdfinal = L"";
	cmd.str(L"");
	cmd.clear();
	memset(filename, 0, sizeof(filename));

	//

	
	wcout << endl << " FileName : ";
	wcin >> filename;
	wcout << endl;
	
	//



	// Unicode txt open

	FILE* fi;
	_wfopen_s(&fi, filename , L"r");
	_setmode(_fileno(fi), _O_WTEXT);
	wifstream in(fi);
	in.seekg(2, in.beg);
	
	//
	
	//
	
	while (!in.eof())
	{


		getline(in, list);
		if (count % 2 != 0)
		{
			url = list;
		}

		if (count % 2 == 0)
		{
			name = list;
			

			cmd << L"start/min youtube-dl -o \"" << name << L".%(ext)s\" -f bestaudio --extract-audio --audio-format wav --audio-quality 0 " << url;

			getline(cmd, cmdfinal);
			_wsystem(cmdfinal.c_str());

			cmdfinal = L"";
			cmd.str(L"");
			cmd.clear();
			

		}


		count++;

	}
	in.close();


	system("pause");


	goto fileread;





}


