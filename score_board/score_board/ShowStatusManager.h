#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "LineDecoder.h"


class ShowStatusManager {
private:
	long long int startTime = 0;
	std::string mode;

public:
	LineDecoder ld;

public:
	ShowStatusManager();
	std::string getStatus();
	long long int getStartTime();

private:
	void update();
};

