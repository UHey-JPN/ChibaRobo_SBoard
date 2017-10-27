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

		draw_status_info(ssm);
		drawManager.draw();
		windowInfomation.update();
	}
}


void draw_status_info(std::shared_ptr<ShowStatusManager> ssm) {
	static const Font font(10);
	const String text = Widen(ssm->getStatus() + "," + std::to_string(ssm->getShowTime()));
	const int32 w = font(text).region().w;
	const int32 h = font(text).region().h;
	font(text).draw(Window::Width() - w, Window::Height() - h);

}




