#include <string>
#include <memory>

#include <Siv3D.hpp>

#include "DrawManager.h"
#include "ShowStatusManager.h"




void Main()
{
	std::shared_ptr<ShowStatusManager> ssm(new ShowStatusManager);
	DrawManager drawManager(ssm);

	// ウィンドウサイズを可変に
	Window::SetStyle(WindowStyle::Sizeable);

	while (System::Update()) {
		s3d::uint64 current = Time::SecSince1970() * 1000 - Time::MillisecSince1601();

		Println(current);

		if (Input::KeyS.clicked) {
			ssm->ld.input("show,home,1508819251000\n");
		}
		drawManager.draw();
	}
}
