#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream> 
#include <vector>
#include <thread>
#include <iomanip>
#include <io.h>
#include <fcntl.h>

using namespace std ;


void splitstr( wstring s , vector<wstring> &s_out ) ;
void download( wstring command , wstring name ) ;

class ytdl
{

public:

	ytdl();
	~ytdl();


	void getstate( vector<wstring> in , wstring &state , wstring &speed , wstring &eta )
	{

		state = L"-";
		speed = L"-";
		eta = L"-";

		if ( in.front() == L"download" )
		{
			for ( wstring temp : in )
			{
				if ( temp == L"download" && sw1 == 1 )
				{
					continue;
				}

				if ( temp == L"Destination:" )
				{
					sw1 = 1;
					sw2 = 1;
					break;
				}

				if ( temp == L"at" )
				{
					sw1 = 1;
					sw2 = 2;
					continue;
				}

				if ( temp == L"ETA" )
				{
					sw1 = 1;
					sw2 = 3;
					continue;
				}

				if ( sw1 == 1 )
				{


					if ( sw2 == 1 )
					{
						state = temp;
					}

					if ( sw2 == 2 )
					{
						speed = temp;
					}

					if ( sw2 == 3 )
					{
						eta = temp;
					}

					if ( temp == in.back() )
					{
						sw1 = 1;
						sw2 = 1;
					}
					else
					{
						sw1 = 0;
					}

				}

			}

		}

		if ( in.front() == L"ffmpeg" )
		{
			state = L"Converting";
			speed = L"-";
			eta = L"-";
		}

		if ( in.front() == L"Deleting" )
		{
			state = L"Deleting temp";
		}

	}


private:

	int sw1 , sw2 ;


};

ytdl::ytdl()
{

	sw1 = 0 ;
	sw2 = 0 ;
	
}

ytdl::~ytdl()
{

}


vector<ytdl> yt1 ;

int main()
{

	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stdin), _O_WTEXT);

	int count , mod ;
	wstring name, clear, url, list, cmdfinal;
	wstringstream cmd;
	wchar_t filename[10];
	vector<thread> dl;


	//
	start :

	system( "cls" );
	wcout << " ver 0.2.0" << endl ;
	wcout << endl << " (1) Single download     (2) Reading from file  : ";
	wcin >> mod;
	wcout << endl;

	switch ( mod )
	{
	case 1 :
		goto singledownload ;
		break ;
	case 2 :
		goto readingfromfile ;
		break ;
	default:
		goto start ;
		break ;
	}
	

	//
	singledownload :

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

	cmd << L"  youtube-dl --newline  -o \"" << name << L".%(ext)s\" -f bestaudio --extract-audio --audio-format wav --audio-quality 0 " << url;

	getline(cmd, cmdfinal);

	dl.push_back( thread( download , cmdfinal , name ) ) ;
	
	dl[ dl.size() - 1 ].join() ;

	wcout << endl << endl ;
	system("pause");

	goto singledownload ;
	//


	//
	readingfromfile:

	system( "cls" );
	url = L"";
	name = L"";
	list = L"";
	list.clear();
	count = 1;
	cmdfinal = L"";
	cmd.str( L"" );
	cmd.clear();
	memset( filename , 0 , sizeof( filename ) );


	wcout << endl << " FileName : ";
	wcin >> filename;
	wcout << endl;

	FILE *fi;
	_wfopen_s( &fi , filename , L"r" );
	_setmode( _fileno( fi ) , _O_WTEXT );
	wifstream in( fi );
	in.seekg( 2 , in.beg );

	while ( !in.eof() )
	{

		getline( in , list );

		if ( count % 2 != 0 )
		{
			url = list;
		}

		if ( count % 2 == 0 )
		{
			name = list;

			cmd << L"  youtube-dl --newline  -o \"" << name << L".%(ext)s\" -f bestaudio --extract-audio --audio-format wav --audio-quality 0 " << url;

			getline( cmd , cmdfinal ) ;
			
			dl.push_back( thread( download , cmdfinal , name ) ) ;
			wcout << endl << endl ;

			dl[dl.size() - 1].join() ;

			cmdfinal = L"";
			cmd.str( L"" );
			cmd.clear();

		}

		count++;

	}

	in.close();

	wcout << endl << endl << "All Finshed" << endl << endl ;
	system( "pause" );

	goto readingfromfile ;
	//

}


void splitstr( wstring s , vector<wstring> &s_out )
{

	int current = 0 ;
	int next ;
	wstring temp ;

	while (1)
	{

		next = s.find_first_of( L"\n[] " , current ) ; // remove "\n" , "[" , "]" , " "

		if ( next != current )
		{

			temp = s.substr( current , next - current ) ;

			if ( temp.size() != 0 ) // 忽略空字串
			{
				s_out.push_back(temp) ;
			}

		}

		if ( next == wstring::npos )
		{
			break ;
		}

		current = next + 1 ;

	}

}

void download( wstring command , wstring name )
{

	wchar_t   psBuffer[1024] ;
	FILE *pPipe ;
	
	yt1.emplace_back() ;

	if (  ( pPipe = _wpopen( command.c_str() , L"rt" ) ) == NULL  )
	{
		exit( 1 ) ; //Read pipe until end of file, or an error occurs
	}
	
	wstring s;
	wstring state , speed , eta;
	
	while ( fgetws( psBuffer , 1024 , pPipe ) )
	{

		s = psBuffer;
		
		vector<wstring> s_out ;

		splitstr( s , s_out );
		yt1[ yt1.size() - 1 ].getstate( s_out , state , speed , eta );
		
		wcout << L" " << name << L".wav" << setw( 16 ) << state << setw( 15 ) << speed << setw( 10 ) << eta ;
		wcout << L"\r";

	}

	if ( feof( pPipe ) ) // Close pipe
	{
		_pclose( pPipe );

		state = L"Finished";
		wcout << L" " << name << L".wav" << setw( 16 ) << state << setw( 15 ) << speed << setw( 10 ) << eta ;

	}
	else
	{
		wcout << L"Error" ;
	}

}

