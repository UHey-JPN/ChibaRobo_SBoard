#pragma once
#include <string>
#include <deque>

class LineDecoder {
private:
	std::string line_buf;
	std::deque<char> queue;
	bool line_ended = false;
	bool line_available = false;

public:
	void input(const std::string &in);
	void update();
	bool getLine(std::string &result);

};
