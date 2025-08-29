#pragma once
#include"global.h"

class Model {
public:
	Model();//�ݽ�׸�
	~Model();//�޽�׸�
	bool loadModel(const char* fileName);//���f���ǂݍ���
	void showModel(VECTOR mhPos);//���f���\��
	void setScale(float Scale);//���f���T�C�Y�ݒ�
	void Rotation(VECTOR rot);//���f�������ݒ�

	//�R���W����(�����蔻��)����ݒ肷��
	void setupCollInfo();
	//���W��Ԃ�
	inline VECTOR getPos() {
		return pos;
	}
	//���f���n���h���̎擾
	inline int getMHandle() {
		return mhModel;
	}
	//��]�̎擾
	inline VECTOR getRotation() {
		return rot;
	}
	
private:
	int mhModel;//���f���p�n���h��
protected://�p����p
	VECTOR oldpos;//�Փˎ��ɖ߂��p�̍��W

	VECTOR pos;//���W
	VECTOR rot;	//��]
};

class Image {
public:
	Image();//�ݽ�׸�
	~Image() {};//�޽�׸�
	bool loadImage(const char* fileName);//�摜�ǂݍ���
	
	void showImage();//���f���\��
	void showImage(VECTOR pos);//���f���\�����W���͍���
	void drawBillboard(VECTOR pos, float size, float angle);//�摜(���ײ�)������ް�ޕ\��(1���摜�p)

	//��������L���ɂ���
	inline void alphaOn() {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}
	//�������𖳌��ɂ���
	inline void alphaOff() {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
private:
	int gHandle;//�摜�p�n���h��
	int addAlpha;	//�����x�̉����Z�l
protected://�p����p
	VECTOR pos;		//�\���ʒu
	int alpha;		//�����x
};