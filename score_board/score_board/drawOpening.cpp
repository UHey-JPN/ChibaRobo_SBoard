#include "DrawManager.h"

void DrawManager::DrawManagerImpl::drawOpening() {
	static const int number = 16;

	if (ssm->getShowTime() < 0) return;

	if ( !video.isPlaying() && ssm->getShowTime() < video.getLengthSec() * 1000) {
		video.setPosFrame(0);
		video.play();
	}

	video.update();
	video.getFrameTexture().resize(Window::Size()).draw();
	
}
