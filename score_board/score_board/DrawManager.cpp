#include "DrawManager.h"

#include <memory>
#include <string>
#include <Siv3D.hpp>



DrawManager::DrawManager(std::shared_ptr<ShowStatusManager> ssm) : pImpl(new DrawManagerImpl(ssm)) {
	current = ssm;
}

void DrawManager::draw() {
	std::string key = current->getStatus();
	pImpl->draw(key);
}




DrawManager::DrawManagerImpl::DrawManagerImpl(std::shared_ptr<ShowStatusManager> ssm) {
	current = ssm;
	m_funcs["home"] = [&]() {this->drawHome(); };
	m_funcs["opening"] = [&]() {this->drawHome(); };
	m_funcs["home"] = [&]() {this->drawHome(); };
	m_funcs["home"] = [&]() {this->drawHome(); };
	m_funcs["home"] = [&]() {this->drawHome(); };

	home_image.reset(new Texture(L"resource/home.png"));

}

void DrawManager::DrawManagerImpl::draw(std::string key) {
	if (m_funcs.find(key) == m_funcs.end()) {
		drawError();
		return;
	}
	m_funcs[key]();

}

void DrawManager::DrawManagerImpl::drawError() {
	static const Font font(10);
	const String text = L"err";
	const int32 w = font(text).region().w;
	const int32 h = font(text).region().h;
	font(text).draw(Window::Width()-w, Window::Height()-h);

}

void DrawManager::DrawManagerImpl::drawHome(void) {
	static const Font font(30);
	home_image->resize(Window::Width(), Window::Height()).draw();
}