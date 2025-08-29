#pragma once
#include"model.h"
class Item :public Model {
public:
	Item();//�ݽ�׸�
	~Item() {};//�޽�׸�
	void init();//����������
	void ctrl();//���쏈��
	void draw();//�\������

	inline VECTOR getPos(int index) {//���W��z��̌ʂŕԂ��imodel�̃I�[�o�[���[�h�j
		return pos[index];
	}
	inline void getItem(int index) {//�A�C�e������͂����珰���ɉB��
		pos[index].y = -20;
	}
	inline void initPos(int map) {//�X�e�[�W���ƂɃA�C�e���̈ʒu��ς���
		if (map == 1) {
			pos[0] = VGet(-MAP_MAX_X + 400, 10, 50);
			pos[1] = VGet(-MAP_MAX_X + 360, 10, 50);
			pos[2] = VGet(-MAP_MAX_X + 320, 10, 50);
			pos[3] = VGet(-MAP_MAX_X + 280, 10, 50);
			pos[4] = VGet(-MAP_MAX_X + 380, 10, 80);
			pos[5] = VGet(-MAP_MAX_X + 340, 10, 80);
			pos[6] = VGet(50, 10, -MAP_MAX_X + 100);
		}
		if (map == 2) {
			pos[0] = VGet(-120, 10, -400);
			pos[1] = VGet(-120, 10, -450);
			pos[2] = VGet(-120, 10, -500);
			pos[3] = VGet(-180, 10, -420);
			pos[4] = VGet(-180, 10, -470);
			pos[5] = VGet(-310, 10, -MAP_MAX_X + 200);
			pos[6] = VGet(0, -10, 0);
		}
		if (map == 3) {
			pos[0] = VGet(20, 10, -180);
			pos[1] = VGet(60, 10, -180);
			pos[2] = VGet(100, 10, -180);
			pos[3] = VGet(40, 10, -110);
			pos[4] = VGet(80, 10, -110);
			pos[5] = VGet(-510, 10, MAP_MAX_X - 200);
			pos[6] = VGet(-500, 10, MAP_MAX_X - 150);
		}
	}

	inline void setMilk(int index,VECTOR pos) {//�R�[�q�[�������v���C���[�̓��̏��
		milkpos[index] = pos;
		milkpos[index].y += 6;
	}
	inline void removeMilk(int index) {//�g���Ă��Ȃ��Ƃ��͏����ɉB��
		milkpos[index] = VGet(0, -100, 0);
	}

	inline void setCandy(int index,int num, VECTOR pos,VECTOR rot) {//�L�����f�B�[���v���C���[��
		if (!isCandy[index][num]) {
			candyrot[index][num] = rot;
			candypos[index][num] = pos;
			candypos[index][num].y += 5;
		}
	}
	inline void setisCandy(int index,int num, bool iscandy ){//�L�����f�B�[���g��ꂽ
		isCandy[index][num] = iscandy;
	}
	inline void removeCandy(int index,int num) {//�L�����f�B�[���g���I����
		candypos[index][num] = VGet(0, -100, 0);
		isCandy[index][num] = false;
	}
	inline VECTOR getCandypos(int index, int num) {//�L�����f�B�[�̍��W��z��̌ʂŕԂ�
		return candypos[index][num];
	}

	inline void setStick(int index, VECTOR pos) {//�X�e�B�b�N���v���C���[�̓��̏��
		stickpos[index] = pos;
		stickpos[index].y += 7;
	}
	inline void setisStick(int index, bool isstick) {//�X�e�B�b�N���g��ꂽ
		isStick[index] = isstick;
	}
	inline void removeStick(int index) {//�X�e�B�b�N���g���I����
		stickpos[index] = VGet(0, -100, 0);
		stickcenterpos[index] = VGet(0, -100, 0);
	}
	inline VECTOR getStickpos(int index) {//�X�e�B�b�N�̍��W��z��̌ʂŕԂ�
		return stickcenterpos[index];
	}

	inline void setBom(int index, VECTOR pos,VECTOR rot) {//�{�����v���C���[�̓��̏��
		bomrot[index] = rot;
		bompos[index] = pos;
		bompos[index].y += 7;
	}
	inline void setisBom(int index, bool isbom,bool isbom2) {//�{�����g��ꂽ
		isBom[index] = isbom;
		isBom2[index] = isbom2;
	}
	inline void setBompos(int index) {
		if (isBom[index] && !isBom2[index]) {//�{�����g��ꂽ
			bompos[index].y = 0;
			bomSpeed[index] = 5;
			bomUpSpeed[index] = 0.5;
		}
		else if(!isBom[index]){//�{�����g���I����
			bompos[index] = VGet(0, -100, 0);
		}
		
	}
	inline VECTOR getBompos(int index) {//�{���̍��W��z��̌ʂŕԂ�
		return	bompos[index];
	}
private:
	float time[ITEM_MAX];//�A�C�e���̃��X�|�[���J�E���g�p
	VECTOR pos[ITEM_MAX];//�A�C�e�����̍��W�imodel�̃I�[�o�[���[�h�j
	
	Model* milk;//�~���N�̃��f��
	VECTOR milkpos[COLOR_NUM];//�~���N�̍��W

	Model* candy[3];//�L�����f�B�[�̃��f��
	VECTOR candypos[COLOR_NUM][3];//�L�����f�B�[�̍��W
	VECTOR candyrot[COLOR_NUM][3];//�L�����f�B�[�̉�]��
	bool isCandy[COLOR_NUM][3];//�L�����f�B�[���g���Ă���=true
	
	Model* stick[COLOR_NUM];//�X�e�B�b�N�̃��f��
	VECTOR stickpos[COLOR_NUM];//�X�e�B�b�N�̍��W
	VECTOR stickcenterpos[COLOR_NUM];//�X�e�B�b�N�̓����蔻��̍��W
	VECTOR stickrot[COLOR_NUM];//�X�e�B�b�N�̉�]��
	bool isStick[COLOR_NUM];//�X�e�B�b�N���g���Ă���=true

	Model* bom;//�{���̃��f��
	VECTOR bompos[COLOR_NUM];//�{���̍��W
	VECTOR bomrot[COLOR_NUM];//�{���̉�]��
	bool isBom[COLOR_NUM];//�{�����g���Ă���=true
	bool isBom2[COLOR_NUM];//�{���𓊂��Ďg���Ă���=true
	float bomSpeed[COLOR_NUM];//�{����O�ɔ�΂��p
	float bomUpSpeed[COLOR_NUM];//�{������ɔ�΂��p
};