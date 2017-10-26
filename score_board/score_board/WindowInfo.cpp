#include "WindowInfo.h"


//////////////////////////////////////////////////////////////////
// WindowInfo class
//
WindowInfo::WindowInfo() :
	resolutions(Graphics::GetFullScreenSize()),
	font(40, Typeface::Medium, FontStyle::Outline)
{
	right = new ClickedKey( &Input::KeyRight );
	left = new ClickedKey( &Input::KeyLeft );

	Window::SetStyle(WindowStyle::NonFrame);
	Window::Resize(resolutions[resolutions.size() - 1]);
	Window::SetFullscreen(true, resolutions[resolutions.size() - 1]);
	window_size_id = resolutions.size() - 1;
	font.changeOutlineStyle(TextOutlineStyle(Palette::White, Palette::Black, 2.0));
}

WindowInfo::~WindowInfo() {
	delete right;
	delete left;
}

void WindowInfo::update() {
	if (left->isClicked()) {
		window_size_id--;
		if (window_size_id < 0) window_size_id = 0;
		Window::SetFullscreen(true, resolutions[window_size_id]);
		time = DISP_TIME;
	}
	if (right->isClicked()) {
		window_size_id++;
		if (window_size_id >= resolutions.size()) window_size_id = resolutions.size() - 1;
		Window::SetFullscreen(true, resolutions[window_size_id]);
		time = DISP_TIME;
	}

	if (time > 0) {
		time--;
		std::string text(std::to_string(Window::Width()) + "~" + std::to_string(Window::Height()));
		font(Widen(text)).drawCenter(Window::Width() / 2, Window::Height() / 2);
	}
}


//////////////////////////////////////////////////////////////////
// ClickedKey class
//
WindowInfo::ClickedKey::ClickedKey(const s3d::Key * k) {
	this_key = k;
	called = false;
}

bool WindowInfo::ClickedKey::isClicked() {
	if (this_key->pressed) {
		if (called) {
			return false;
		} else {
			called = true;
			return true;
		}
	} else {
		called = false;
		return false;
	}
}
