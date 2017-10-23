#include "DrawManager.h"

#include <Siv3D.hpp>



DrawManager::DrawManager(ShowStatusManager &sm) {
	current = &sm;
	small_info = Font(30);
	drawList["home"] = &DrawManager::drawHome;
}


DrawManager::~DrawManager() {
}


void DrawManager::draw() {
	drawFuncType *thisDraw = &(this->drawList[current->getStatus()]);
	if (thisDraw = NULL) {
		Println(L"no mode");
	} else {
		(thisDraw)();
	}


}


void DrawManager::drawHome() {
	static const Font font(30);
	font(L"‚æ‚¤‚±‚»ASiv3D ‚Ì¢ŠE‚ÖI" + Widen(current->getStatus())).draw();

	Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });

}
