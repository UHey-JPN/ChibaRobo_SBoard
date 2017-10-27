#include "ShowStatusManager.h"


ShowStatusManager::ShowStatusManager() :
	udp_exe(L"exejar.bat")
{
	if (!udp_exe) System::Exit();

	mode = "home";
}

ShowStatusManager::~ShowStatusManager() {
	udp_exe.write("quit\n");
}

std::string ShowStatusManager::getStatus() {
	update();
	return mode;
}

long long int ShowStatusManager::getStartTime() {
	update();
	return startTime;
}

long long int ShowStatusManager::getCurrentTime() {
	return (long long int)(Time::MillisecSince1601() - WINUTC_2_EPOC);
}

long long int ShowStatusManager::getShowTime() {
	return getCurrentTime() - getStartTime();
}

int ShowStatusManager::getScore(int side) {
	if (side == 0 || side == 1) {
		return score[side];
	}
	return 0;
}

void ShowStatusManager::update() {
	// 外部実行プログラムの標準入出力を読み出し
	if (udp_exe.available()) {
		std::string str;
		udp_exe.read(str);
		ld.input(str);
	}
	while (1) {
		std::string line;
		if (ld.getLine(line) == false) return;

		std::stringstream ss(line);

		{
			std::string item;
			int cnt = 0;
			while (std::getline(ss, item, ',')) {
				switch (cnt++) {
					case 0:
						if (item == "#") {
							std::cout << line << std::endl;
							return;
						} else if (item == "show") {
							break;
						} else {
							return;
						}
						break;
					case 1:
						mode.assign(item);
						break;
					case 2: {
						std::istringstream iss(item);
						iss >> startTime;
						break;
					}
					case 3: {
						std::istringstream iss(item);
						iss >> score[0];
						break;
					}
					case 4: {
						std::istringstream iss(item);
						iss >> score[1];
						break;
					}

				}
			}
		}


	}
}

std::vector<std::string> ShowStatusManager::split(std::string str) {
	std::vector<std::string> ret;
	std::string item;

	std::stringstream ss(str);

	while (std::getline(ss, item, ',')) {
		ret.push_back(item);
	}
	return ret;
}
