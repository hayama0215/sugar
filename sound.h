#pragma once
#include "global.h"

class Sound{
public:
	Sound() {};	//�ݽ�׸�
	~Sound();	//�޽�׸�

	bool loadSound(const char* fileName);//�T�E���h�Ǎ���
	void stopBGM();//bgm���~�߂�
	void playBGM();//bgm�𗬂�
	void SE_Play();//���ʉ��iSE�j�̍Đ��֐�
private:

	int SHandle;	//����������
};