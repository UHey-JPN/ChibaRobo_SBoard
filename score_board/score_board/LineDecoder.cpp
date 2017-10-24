#include "LineDecoder.h"


void LineDecoder::input(const std::string &in) {
	for (unsigned int i = 0; i < in.size(); i++) {
		queue.push_back(in[i]);
	}
	update();
}

void LineDecoder::update() {
	while (queue.size() > 0) {
		char c = queue[0];
		if (c == '\r' || c == '\n') {
			if (line_ended == false) {
				// 処理中の行で初めての改行コード
				line_available = true;
			}
			line_ended = true;
			queue.pop_front(); // バッファから消去
		}
		else {
			if (line_available == true) {
				// 行バッファをまだ読み出していないので処理を終了して戻る
				break;
			}
			else {
				// 改行コード以外を行バッファの末尾に入れる。
				// NULLなら行を読み出した後のなので、新しく行バッファを作る。
				line_buf.push_back(queue.front());
				queue.pop_front();
			}
			line_ended = false;
		}
	}
}

bool LineDecoder::getLine(std::string &result) {
	if (line_available == true) {
		result.clear();
		result.assign(line_buf);
		line_buf.clear();
		line_available = false;
		update();
		return true;
	}
	else {
		return false;
	}
}
