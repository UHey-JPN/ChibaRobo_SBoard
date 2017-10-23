#pragma once
#include "showStatusManager.h"

#include <Siv3D.hpp>
#include <string>

class DrawManager {
private:
	ShowStatusManager *current;
	Font small_info;
	typedef void (DrawManager::*drawFuncType)(void);
	std::map < std::string, drawFuncType> drawList;

public:
	DrawManager(ShowStatusManager & sm);
	~DrawManager();

	void draw();
	void drawHome();
};

