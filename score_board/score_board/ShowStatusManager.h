#pragma once

#include <Siv3D.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include "LineDecoder.h"


class ShowStatusManager {
public:
	const long long int WINUTC_2_EPOC = 11644473600000;

private:
	long long int startTime = 0;
	std::string mode;
	int score[2] = { 0 };
	PipeServer udp_exe;

public:
	LineDecoder ld;

public:
	ShowStatusManager();
	~ShowStatusManager();
	std::string getStatus();
	long long int getStartTime();
	long long int getCurrentTime();
	long long int getShowTime();
	int getScore(int side);

private:
	void update();
	std::vector<std::string> split(std::string str);
};

