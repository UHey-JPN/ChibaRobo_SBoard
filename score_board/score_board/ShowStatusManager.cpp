#include "ShowStatusManager.h"


ShowStatusManager::ShowStatusManager() {
	mode = "home";
}

std::string ShowStatusManager::getStatus() {
	update();
	return mode;
}

long long int ShowStatusManager::getStartTime() {
	update();
	return startTime;
}

void ShowStatusManager::update() {
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
					}
					else if (item == "show") {
						break;
					}
					else {
						return;
					}
					break;
				case 1:
					mode.assign(item);
					break;
				case 2:
					std::istringstream iss(item);
					iss >> startTime;
					break;
				}
			}
		}


	}
}
