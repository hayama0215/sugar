#pragma once
#include"global.h"

#define DIFFUSE_COLOR GetColor(255,0,0)  //�ި̭��ސF(�g�U���ːF)
#define SPECULAR_COLOR GetColor(255,0,0) //��߷�װ�F(���ʔ��ːF)

class Collision {
public:
	//�����蔻��(��:�v�Z��)
	bool hitCheck_Sphere(VECTOR center1, float r1,VECTOR center2, float r2);
	void drawSphere(VECTOR pos, float r);

	//�����蔻��(�J�v�Z��)
	bool collCheck_Capsule(int MHandle, VECTOR pos1, VECTOR pos2, float r);
	void drawCapsule(VECTOR pos1, VECTOR pos2, float r);	//��߾�


	bool hitCheckLineX(VECTOR pos1, VECTOR pos2,float size);//���Ƃ̓����蔻��
	bool hitCheckLineZ(VECTOR pos1, VECTOR pos2,float size);//���Ƃ̓����蔻��
};