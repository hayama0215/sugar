#include"camera.h"
Camera::Camera() {
	SetCameraNearFar(1.0f, 1000.0f);	//��ׂ�Z�͈�(1�`1000)
	LightHandle = CreateDirLightHandle(VGet(-1.0f, 0.0f, -1.0f));
	for (int i = 0;i < PLAYER_NUM;i++) cameraPos[i] = lookPos[i] = VGet(0, 0, 0);
}
void Camera::setCamera(VECTOR cPos, VECTOR lPos)
{
	SetDrawAreaFull();
	SetCameraScreenCenter(WND_W / 2, WND_H / 2);//�\�������Ɉړ�
	cameraPos[0] = cPos;
	lookPos[0] = lPos;
	//�J�����ʒu�ƒ����ʒu�̐ݒ�
	SetCameraPositionAndTarget_UpVecY(cameraPos[0], lookPos[0]);
}

//TPS�J����
void Camera::ctrl(VECTOR pos, VECTOR rot, int index)
{
	MATRIX mat1;	//�e�s��

	//�ʒu����ݒ�
	cameraPos[index] = lookPos[index] = pos;

	mat1 = MGetRotY(rot.y);				//Y����]�s��̍쐬
	VECTOR axisZ = VGet(0, 0, 1.0f);	//���޸��
	axisZ = VTransform(axisZ, mat1);	//�������޸�ق����߂�

	//��׈ʒu�ƒ����ʒu������
	VECTOR pos1, pos2;
	pos1 = VScale(axisZ, 50.0f);	//��׋���
	pos2 = VScale(axisZ, 40.0f);	//��������

	cameraPos[index] = VAdd(cameraPos[index], pos1);	//��׈ʒu
	lookPos[index] = VSub(lookPos[index], pos2);		//�����ʒu

	//Y���W���Œ肷��
	cameraPos[index].y += 30.0f;
	lookPos[index].y += 10.0f;
}

void Camera::draw(int index) {
	if (index == 0) {
		SetDrawArea(0, 0, WND_W / 2, WND_H); // ��������\��
		SetCameraScreenCenter(WND_W / 4, WND_H / 2);//�\�������Ɉړ�
		//�J�����ʒu�ƒ����ʒu�̐ݒ�
		SetCameraPositionAndTarget_UpVecY(cameraPos[index], lookPos[index]);
	}
	if (index == 1) {
		SetDrawArea(WND_W / 2, 0, WND_W, WND_H); // �E������\��
		SetCameraScreenCenter(WND_W - WND_W / 4, WND_H / 2);//�\�����E�Ɉړ�
		//�J�����ʒu�ƒ����ʒu�̐ݒ�
		SetCameraPositionAndTarget_UpVecY(cameraPos[index], lookPos[index]);
	}
}