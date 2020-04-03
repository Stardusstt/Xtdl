#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <boost/process.hpp>

using namespace std ;


class Update
{
public:

	Update();
	~Update();

	void GetVersion();
	void UpdateYoutube_dl();

private:

	string xtdl_version , youtube_dl_version , ffmpeg_version ;

};

