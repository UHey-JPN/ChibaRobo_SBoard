#include <string>
#include <memory>

#include <Siv3D.hpp>

#include "DrawManager.h"
#include "ShowStatusManager.h"
#include "WindowInfo.h"

void draw_status_info(std::shared_ptr<ShowStatusManager> ssm);

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Main function
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void Main() {
	std::shared_ptr<ShowStatusManager> ssm(new ShowStatusManager);
	DrawManager drawManager(ssm);
	WindowInfo windowInfomation;

	// デバッグ用のウィンドウ生成
	Console::Open();

	while (System::Update()) {
		if (Input::KeyH.clicked) {
			ssm->ld.input(std::string("show,home,") + std::to_string(ssm->getCurrentTime() - 500) + std::string(",0,0\n"));
		}
		if (Input::KeyO.clicked) {
			ssm->ld.input(std::string("show,opening,") + std::to_string(ssm->getCurrentTime() - 500) + std::string(",0,0\n"));
		}
		if (Input::KeyG.clicked) {
			ssm->ld.input(std::string("show,game,") + std::to_string(ssm->getCurrentTime() - 500) + std::string(",0,0\n"));
		}
		if (Input::Key1.clicked) {
			ssm->ld.input(std::string("show,game,") + std::to_string(ssm->getCurrentTime() - 500) + std::string(",1,5\n"));
		}
		if (Input::Key2.clicked) {
			ssm->ld.input(std::string("show,game,") + std::to_string(ssm->getCurrentTime() - 500) + std::string(",0,0\n"));
		}




		// ------------------------------------------
		// 描画関係のメソッド
		// 順番には注意が必要。下のレイヤーから順に呼び出す。
		draw_status_info(ssm);
		drawManager.draw();
		windowInfomation.update();
	}
}


void draw_status_info(std::shared_ptr<ShowStatusManager> ssm) {
	static const Font font(10);
	const std::string text = ssm->getStatus() + ","
		+ std::to_string(ssm->getShowTime()) + ","
		+ std::to_string(ssm->getScore(0)) + "-" + std::to_string(ssm->getScore(1));
	const String w_text = Widen(text);
	const int32 w = font(w_text).region().w;
	const int32 h = font(w_text).region().h;
	font(w_text).draw(Window::Width() - w, Window::Height() - h);

}




