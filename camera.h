#pragma once
#include"model.h"
class Camera :public Model {
public:
	Camera();//�ݽ�׸�
	~Camera() {};//�޽�׸�
	void setCamera(VECTOR cPos,VECTOR lPos);	//��׈ʒu�̍X�V
	void ctrl(VECTOR pos, VECTOR rot,int index);//���쏈��
	void draw(int index);//�\������
private:

	VECTOR cameraPos[2], lookPos[2];	//��׈ʒu�A�����ʒu
	int LightHandle;//2�ڂ̃��C�g�̃n���h��
};