#pragma once
#include "showStatusManager.h"

#include <Siv3D.hpp>
#include <string>
#include <memory>

class DrawManager {
public: // クラスの外で using を使いたいので public にしている。
	class DrawManagerImpl; // 実務クラスの宣言

private:
	std::unique_ptr<DrawManagerImpl> pImpl;
	std::shared_ptr<ShowStatusManager> current;

public:
	DrawManager(std::shared_ptr<ShowStatusManager> ssm);

public:
	void draw();
};


using drawFunc_t = void (DrawManager::DrawManagerImpl:: *)();

class DrawManager::DrawManagerImpl {
private:
	std::shared_ptr<ShowStatusManager> current;
	std::map<std::string, std::function<void()> > m_funcs;

public:
	DrawManagerImpl(std::shared_ptr<ShowStatusManager> ssm);

	void draw(std::string key);
	void drawError();
	void drawHome();
};


