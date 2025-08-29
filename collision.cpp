#include "collision.h"

//�����蔻��(��)
bool Collision::hitCheck_Sphere(
	VECTOR center1, float r1, VECTOR center2, float r2)
{
	//���S���̒��������߂�
	//a^2 + b^2 + c^2
	float centerLength =
		(center1.x - center2.x) * (center1.x - center2.x)		//a^2
		+ (center1.y - center2.y) * (center1.y - center2.y)		//b^2
		+ (center1.z - center2.z) * (center1.z - center2.z);	//b^2

	//���a�̑����Z��2�悵�����̂ƒ��S���̒������ׂ�
	//a^2+b^2+c^2 < (r1+r2)^2
	if (centerLength < (r1 + r2) * (r1 + r2)) {
		return true;	//�������Ă���
	}
	return false;	//�O��Ă���
}

//Sphere(��)�̕\��
void Collision::drawSphere(VECTOR pos, float r)
{
	DrawSphere3D(
		pos,			//�\���ʒu
		r,				//���a
		8,				//������
		DIFFUSE_COLOR,	//�ި̭��ސF(���̂̐F)
		SPECULAR_COLOR,	//��߷�װ�F(���˂����F)
		FALSE);			//TRUE:�h��Ԃ��@FALSE:�ڰѕ\��
}

//�����蔻��(�J�v�Z��)
bool Collision::collCheck_Capsule(int MHandle, VECTOR pos1, VECTOR pos2, float r)
{
	MV1_COLL_RESULT_POLY_DIM hitPolyDim;	//���茋�ʍ\����

	hitPolyDim = MV1CollCheck_Capsule(
		MHandle,	//�\��setupCollInfo�������������
		-1,			//���肷���ڰєԍ�(�S�̂Ȃ�-1)
		pos1,		//�Ԃ����Ă����޼ު�Ă̏�̒��S���W
		pos2,		//�Ԃ����Ă����޼ު�Ẳ��̒��S���W
		r);			//�Ԃ����Ă����޼ު�Ă̔��a
	if (hitPolyDim.HitNum >= 1) {
		//1��غ�݈ȏ㓖�����Ă��鎞
		return true;	//�Փ�
	}
	return false;	//�O��
}
//�J�v�Z���̕\��
void Collision::drawCapsule(VECTOR pos1, VECTOR pos2, float r)
{
	DrawCapsule3D(
		pos1,			//��߾ق̏�̈ʒu
		pos2,			//��߾ق̉��̈ʒu
		r,				//���a
		8,				//������
		DIFFUSE_COLOR,	//�ި̭��ސF(���̂̐F)
		SPECULAR_COLOR,	//��߷�װ�F(���˂����F)
		FALSE);			//TRUE:�h��Ԃ��@FALSE:�ڰѕ\��
}

bool Collision::hitCheckLineX(VECTOR pos1, VECTOR pos2, float size) {//���ƃ��f���̓����蔻��X
	if (pos2.x - size < pos1.x && pos2.x + size > pos1.x && pos1.z >= pos2.z-5 && pos1.z <= pos2.z + 5) {
		return true;
	}
	return false;
}
bool Collision::hitCheckLineZ(VECTOR pos1, VECTOR pos2, float size) {//���ƃ��f���̓����蔻��Z
	if (pos2.z - size < pos1.z && pos2.z + size > pos1.z && pos1.x >= pos2.x-5 && pos1.x <= pos2.x + 5) {
		return true;
	}
	return false;
}