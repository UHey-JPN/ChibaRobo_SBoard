#include "DrawManager.h"

void DrawManager::DrawManagerImpl::drawVgoal() {
	static const int number = 16;

	if (ssm->getShowTime() < 0) return;
	
	double shift = 2 * (ssm->getShowTime() % 1000) / 1000.0;
	double scale = 1;
	double length = sqrt(Window::Width()*Window::Width() + Window::Height()*Window::Height());

	if (ssm->getShowTime() < 1000 - 1) {
		scale *= (ssm->getShowTime() % 1000) / 1000.0;
	} else {
		scale = 1;
	}
	for (int i = 0; i < number; i++) {
		if ((i % 2) == 0) {
			Circle(Window::Width() / 2, Window::Height() / 2, length*scale).drawPie(TwoPi * (i + shift) / number, TwoPi / number, Palette::Gold);
		} else {
			Circle(Window::Width() / 2, Window::Height() / 2, length*scale).drawPie(TwoPi * (i + shift) / number, TwoPi / number, Palette::Silver);
		}
	}

	score_font[score_font.size() - 4](L"V GOAL").drawCenter(Window::Width() * 0.5, Window::Height() * 0.52, Color(255, 255, 255, 255 * scale));
	score_font[score_font.size() - 1](L"V GOAL").drawCenter(Window::Width() * 0.5, Window::Height() * 0.5, Color(255, 0, 0, 255 * scale));

}
