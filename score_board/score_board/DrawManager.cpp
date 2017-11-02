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




DrawManager::DrawManagerImpl::DrawManagerImpl(std::shared_ptr<ShowStatusManager> set_ssm) {
	ssm = set_ssm;

	m_funcs["home"]			= [&]() { this->drawHome(); };
	m_funcs["preshow"]		= [&]() { this->drawHome(); };
	m_funcs["opening"]		= [&]() { this->drawHome(); };
	m_funcs["newgame"]		= [&]() { this->drawHome(); };
	m_funcs["l_interview"]	= [&]() { this->drawHome(); };
	m_funcs["r_interview"]	= [&]() { this->drawHome(); };
	m_funcs["game"]			= [&]() { this->drawGame(); };
	m_funcs["result"]		= [&]() { this->drawResult(); };
	m_funcs["vgoal"]		= [&]() { this->drawVgoal(); };
	m_funcs["interview"]	= [&]() { this->drawInterview(); };

	home_image.reset(new Texture(L"resource/home.png"));
	result_image.reset(new Texture(L"resource/result_image.png"));
	winner_image.reset(new Texture(L"resource/winner.png"));

	FontManager::Register(L"resource/GAU_Over_Drive.TTF");
	FontManager::Register(L"resource/SoukouMincho.ttf");
	FontManager::Register(L"resource/CAMELIAB.TTF");


	for (size_t i = 0; i < score_font.size(); i++) {
		score_font[i] = Font( (int32)((i+1)*3.2), L"Cameliabold" );
		//score_font[i] = Font( (int32)((i+1)*3.2), L"GauFontOverDrive" );
		//score_font[i] = Font( (int32)((i+1)*3.2), L"装甲明朝" );
	}

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
	font(text).draw(Window::Width()-w, Window::Height()-h*2);
}

void DrawManager::DrawManagerImpl::drawScore(int b_width, int b_height, int b_x, int b_y, String score[2]) {
	const double width = (double)Window::Width();
	const double height = (double)Window::Height();

	const double scale_x = width / 1920.0;
	const double scale_y = height / 1080.0;

	// 設定値
	const double rect_w = b_width * scale_x;
	const double rect_h = b_height * scale_y;
	const double rect_x = b_x * scale_x;
	const double rect_y = b_y * scale_y;

	// フォントの描画位置
	Vec2 score_pos[2] = { Vec2(), Vec2() };
	score_pos[0].x = rect_x + rect_w / 2;
	score_pos[0].y = rect_y + rect_h / 2;
	score_pos[1].x = width - rect_x - rect_w / 2;
	score_pos[1].y = rect_y + rect_h / 2;

	// 得点ボックス用のインスタンス
	const Rect rect0((int)rect_x, (int)rect_y, (int)rect_w, (int)rect_h);                         
	const Rect rect1((int)(width - rect_x - rect_w), (int)rect_y, (int)rect_w, (int)rect_h);

	// 得点ボックスの描画
	rect0.draw(Palette::White);
	rect0.drawFrame(0, 50 * scale_x, Palette::Blue);
	rect1.draw(Palette::White);
	rect1.drawFrame(0, 50 * scale_x, Palette::Red);

	// フォントサイズの決定
	const double font_size = 127 * b_height / 400 * scale_y;
	size_t font_index = score_font.size() - 1;
	for (size_t i = 0; i < score_font.size(); i++) {
		if (font_size <= score_font[i].size()) {
			font_index = i;
			break;
		}
	}

	// 得点の表示
	for (int i = 0; i < 2; i++) {
		score_font[font_index](score[i]).drawCenter(score_pos[i], Palette::Black);
	}
}

void DrawManager::DrawManagerImpl::drawHome(void) {
	home_image->resize(Window::Width(), Window::Height()).draw();
}

void DrawManager::DrawManagerImpl::drawInterview() {
	int t = (int)ssm->getShowTime();
	if (t > 1000 - 1) {
		winner_image->scale(Window::Width() / 1920.0).draw();
	} else {
		winner_image->scale(Window::Width() / 1920.0).draw(0,0, Alpha(t*255/1000));
	}
}

