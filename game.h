#pragma once
#include"collision.h"
class Game :public Collision {
public:
	Game();//�ݽ�׸�
	~Game();//�޽�׸�
	void init();//����������
	void ctrl();//���쏈��
	void draw();//�\������
private:
	int Color[COLOR_NUM];
	float time;//���Ԍv���p
	DINPUT_JOYSTATE input[2];//�R���g���[���[�ϐ�

};