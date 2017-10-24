#include <string>
#include <memory>

#include <Siv3D.hpp>

#include "DrawManager.h"
#include "ShowStatusManager.h"




void Main()
{
	std::shared_ptr<ShowStatusManager> showStatusManager(new ShowStatusManager);
	DrawManager drawManager(showStatusManager);

	// ウィンドウサイズを可変に
	Window::SetStyle(WindowStyle::Sizeable);

	while (System::Update())
	{
		drawManager.draw();
	}
}
