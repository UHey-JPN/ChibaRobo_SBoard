#include "DrawManager.h"

void DrawManager::DrawManagerImpl::drawGame() {
	if (ssm->getShowTime() < 0) return;

	const int game_time = (int)(185 * 1000 - ssm->getShowTime());
	const int game_min = (game_time + 1000) / 1000 / 60;
	const int game_sec = (game_time + 1000) / 1000 % 60;

	if (game_time > 180 * 1000 - 1) {
		// カウントダウン
		Circle(Window::Width() / 2, Window::Height() / 2, Window::Height() / 4).drawArc(0, -TwoPi * (game_time % 1000) / 1000, 30, 0, Palette::White);
		score_font[score_font.size() - 1](Widen(std::to_string(game_sec))).drawCenter(Window::Width() / 2, Window::Height() / 2);
	} else if (game_time > 177 * 1000 - 1) {
		// STARTと表示
		int alpha;
		if (game_time > 178 * 1000 - 1) {
			alpha = 255;
		} else {
			alpha = (game_time % 1000) * 256 / 1000;
		}
		score_font[score_font.size() - 1](L"START").drawCenter(Window::Width() / 2, Window::Height() / 2, Alpha(alpha));
	} else if (game_time > 0) {
		// 試合中
		String score[2];
		double y_pos = 0.7;
		if (game_time > 60 * 1000 - 1) {
			for (int i = 0; i < 2; i++) score[i] = Widen(std::to_string(ssm->getScore(i)));
		} else {
			for (int i = 0; i < 2; i++) score[i] = Widen("??");
		}
		drawScore(650, 300, 150, 100, score);
		score_font[score_font.size() - 1](Widen(std::to_string(game_min))).drawCenter(Window::Width() * 1 / 5, Window::Height() * y_pos);
		score_font[score_font.size() - 1](L":").drawCenter(Window::Width() * 2 / 5, Window::Height() * y_pos);
		score_font[score_font.size() - 1](Widen(std::to_string(game_sec / 10))).drawCenter(Window::Width() * 3 / 5, Window::Height() * y_pos);
		score_font[score_font.size() - 1](Widen(std::to_string(game_sec % 10))).drawCenter(Window::Width() * 4 / 5, Window::Height() * y_pos);
	} else {
		// 試合終了
		String score[2];
		double y_pos = 0.7;
		for (int i = 0; i < 2; i++) score[i] = Widen("??");
		drawScore(650, 300, 150, 100, score);
		score_font[score_font.size() - 1](L"Finish").drawCenter(Window::Width() / 2, Window::Height() * y_pos);
	}
}
