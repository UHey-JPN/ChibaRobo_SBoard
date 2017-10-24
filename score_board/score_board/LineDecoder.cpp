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
				// �������̍s�ŏ��߂Ẳ��s�R�[�h
				line_available = true;
			}
			line_ended = true;
			queue.pop_front(); // �o�b�t�@�������
		}
		else {
			if (line_available == true) {
				// �s�o�b�t�@���܂��ǂݏo���Ă��Ȃ��̂ŏ������I�����Ė߂�
				break;
			}
			else {
				// ���s�R�[�h�ȊO���s�o�b�t�@�̖����ɓ����B
				// NULL�Ȃ�s��ǂݏo������̂Ȃ̂ŁA�V�����s�o�b�t�@�����B
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
