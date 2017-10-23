#include <string>
#include <Siv3D.hpp>

#include "DrawManager.h"
#include "ShowStatusManager.h"

void Main()
{
	ShowStatusManager showStatusManager;
	DrawManager drawManager(showStatusManager);

	// ウィンドウサイズを可変に
	Window::SetStyle(WindowStyle::Sizeable);

	while (System::Update())
	{
		drawManager.draw();
	}
}
