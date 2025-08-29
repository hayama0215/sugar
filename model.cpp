#include"model.h"
Model::Model() {
	pos = VGet(0, 0, 0);
	rot = VGet(0, 0, 0);
}
Model::~Model() {
	MV1DeleteModel(mhModel);
}

bool Model::loadModel(const char* fileName) {
	mhModel = MV1LoadModel(fileName);
	if (mhModel == -1) {
		ErrMsg("���f���̓Ǎ��ݎ��s", fileName);
		return false;
	}
	return true;
}
void Model::showModel(VECTOR mhPos) {
	MV1SetPosition(mhModel, mhPos);
	MV1DrawModel(mhModel);
}
void Model::setScale(float Scale) {
	MV1SetScale(mhModel, VGet(Scale, Scale, Scale));
}
void Model::Rotation(VECTOR rot) {
	MV1SetRotationXYZ(mhModel, rot);
}
//�R���W����(�����蔻��)����ݒ肷��
void Model::setupCollInfo(){
	MV1SetupCollInfo(mhModel, -1, 8, 8, 8);
}

Image::Image() {
	pos = VGet(0, 0, 0);
	alpha = 255;	//���S�s����

}
bool Image::loadImage(const char* fileName) {
	gHandle = LoadGraph(fileName);
	if (gHandle == -1)
	{
		ErrMsg("�摜�t�@�C���̓ǂݍ��ݎ��s", fileName);
		return false;
	}
	return true;
}

void Image::showImage() {
	DrawGraph(pos.x, pos.y, gHandle, TRUE);
}
void Image::showImage(VECTOR pos) {
	DrawGraph(pos.x, pos.y, gHandle, TRUE);
}

//�摜(���ײ�)�̃r���{�[�h�\��(1���摜�p)
void Image::drawBillboard(
	VECTOR pos, float size, float angle)
{
	DrawBillboard3D(
		pos,		//�\���ʒu
		0.5f, 0.5f,	//�摜�̒��S�ʒu
		size,		//�\������摜����
		angle,		//�\������p�x
		gHandle,	//�摜�����
		TRUE);		//�����x(TRUE:�L��)
}