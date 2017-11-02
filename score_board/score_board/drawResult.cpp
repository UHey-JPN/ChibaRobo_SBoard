#include "DrawManager.h"

void DrawManager::DrawManagerImpl::drawResult() {
	if (ssm->getShowTime() < 0) return;
	static int cnt = 0;
	static String score[2];


	const int drum_roll_time = 3000;

	const int32 w = Window::Width();
	const int32 h = Window::Height();

	// ”wŒi‰æ‘œ‚Ì•`‰æ
	result_image->resize(w, h).draw();

	if (ssm->getShowTime() < drum_roll_time) {
		cnt++;
		if (cnt == 2) {
			for (int i = 0; i < 2; i++) score[i] = Widen(std::to_string(Time::GetMicrosec() % 100));
			cnt = 0;
		}
	} else {
		for (int i = 0; i < 2; i++) score[i] = Widen(std::to_string(ssm->getScore(i)));
	}

	drawScore(650, 400, 150, 500, score);
}
