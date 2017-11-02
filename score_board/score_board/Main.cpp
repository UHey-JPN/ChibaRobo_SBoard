
#include <Siv3D.hpp>

#include <string>
#include <sstream>
#include <fstream>
#include <memory>

#include "DrawManager.h"
#include "ShowStatusManager.h"
#include "WindowInfo.h"

void draw_status_info(std::shared_ptr<ShowStatusManager> ssm);
void check_setting();

bool launch_console = false;
bool draw_show_info = false;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Main function
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//*
void Main() {
	std::shared_ptr<ShowStatusManager> ssm(new ShowStatusManager);
	DrawManager drawManager(ssm);
	WindowInfo windowInfomation;

	check_setting();

	// デバッグ用のウィンドウ生成
	if(launch_console) Console::Open();

	while (System::Update()) {
		if (Input::KeyH.clicked) {
			ssm->ld.input(std::string("show,home,") + std::to_string(ssm->getCurrentTime() - 175 * 1000) + std::string(",0,0\n"));
		}
		if (Input::KeyG.clicked) {
			ssm->ld.input(std::string("show,game,") + std::to_string(ssm->getCurrentTime() - 175 * 1000) + std::string(",0,0\n"));
		}
		if (Input::KeyR.clicked) {
			ssm->ld.input(std::string("show,result,") + std::to_string(ssm->getCurrentTime() - 500) + std::string(",0,0\n"));
		}
		if (Input::KeyV.clicked) {
			ssm->ld.input(std::string("show,vgoal,") + std::to_string(ssm->getCurrentTime() + 500) + std::string(",0,0\n"));
		}
		if (Input::KeyO.clicked) {
			ssm->ld.input(std::string("show,opening,") + std::to_string(ssm->getCurrentTime() + 500) + std::string(",0,0\n"));
		}


		// ------------------------------------------
		// 描画関係のメソッド
		// 順番には注意が必要。下のレイヤーから順に呼び出す。
		drawManager.draw();
		windowInfomation.update();
		if (draw_show_info) draw_status_info(ssm);
	}
}
/*/
void Main() {
	// ムービー (AVI, WMV)
	//VideoPlayer video(Dialog::GetOpenVideo().value_or(L"*.avi|*.wmv"));
	VideoPlayer video(L"resource/opening.avi", false, false);

	if (!video.isOpened()) {
		MessageBox::Show(L"サポートしていない形式です。");
		return;
	}

	//Window::Resize(video.getSize());
	Window::SetFullscreen(true, Graphics::GetFullScreenSize()[Graphics::GetFullScreenSize().size() - 1]);

	video.setPosFrame(0);
	video.play();

	while (System::Update()) {
		video.update();

		video.getFrameTexture().draw();

		Window::SetTitle(L"{:.1f} / {:.1f}"_fmt, video.getPosSec(), video.getLengthSec());
	}
}
//*/
void draw_status_info(std::shared_ptr<ShowStatusManager> ssm) {
	static Font status_font(10, Typeface::Medium, FontStyle::Outline);
	const std::string text = ssm->getStatus() + ","
		+ std::to_string(ssm->getShowTime()) + ","
		+ std::to_string(ssm->getScore(0)) + "-" + std::to_string(ssm->getScore(1));
	const String w_text = Widen(text);
	const int32 w = status_font(w_text).region().w;
	const int32 h = status_font(w_text).region().h;
	status_font.changeOutlineStyle(TextOutlineStyle(Palette::Black, Palette::White, 0.5));
	status_font(w_text).draw(Window::Width() - w, Window::Height() - h);

}

void check_setting() {
	std::ifstream ifs("setting.txt");
	if (!ifs) return;

	std::string line;
	for (int lnum = 0; std::getline(ifs, line); lnum++) {
		std::stringstream ss(line);
		std::string item;

		while (std::getline(ss, item, ',')) {
			if (lnum == 0 && item != "0") launch_console = true;
			if (lnum == 1 && item != "0") draw_show_info = true;
			break;
		}
	}
}




