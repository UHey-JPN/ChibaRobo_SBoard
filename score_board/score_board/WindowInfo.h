#pragma once

#include <Siv3D.hpp>
#include <memory>


//////////////////////////////////////////////////////////////////
// WindowInfo class
//
class WindowInfo {
private:
	class ClickedKey;

private:
	const int DISP_TIME = 180;
	ClickedKey * right;
	ClickedKey * left;
	const Array<Size> resolutions;
	size_t window_size_id;
	int time = DISP_TIME;
	Font font;

public:
	WindowInfo();
	~WindowInfo();
	void update();

};


//////////////////////////////////////////////////////////////////
// ClickedKey class
//
class WindowInfo::ClickedKey {
private:
	bool called = false;
	const s3d::Key * this_key;

public:
	ClickedKey(const s3d::Key * k);
	bool isClicked();
};
