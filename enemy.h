#pragma once
#include"model.h"
class Enemy {
public:
	Enemy();//�ݽ�׸�
	~Enemy() {};//�޽�׸�
	void init();//����������
	void load();//���f���ǂݍ���
	void ctrl();//���쏈��
	void draw();//�\������
	inline VECTOR getPos(int index) {//���W��z��̌ʂŕԂ��imodel�̃I�[�o�[���[�h
		return pos[index];
	}
	inline void initPos(int map) {//�}�b�v���Ƃɏ����l��ς���
		if (map == 1) {
			pos[0] = VGet(MAP_MAX_X - 210, 0, -350);
			pos[1] = VGet(MAP_MAX_X - 160, 0, -350);
			pos[2] = VGet(MAP_MAX_X - 235, 0, -380);
			pos[3] = VGet(MAP_MAX_X - 185, 0, -380);
		}
		if (map == 2) {
			pos[0] = VGet(MAP_MAX_X - 210, 0, -380);
			pos[1] = VGet(MAP_MAX_X - 160, 0, -380);
			pos[2] = VGet(MAP_MAX_X - 235, 0, -410);
			pos[3] = VGet(MAP_MAX_X - 185, 0, -410);
		}
		if (map == 3) {
			pos[0] = VGet(MAP_MAX_X - 250, 0, -60);
			pos[1] = VGet(MAP_MAX_X - 200, 0, -60);
			pos[2] = VGet(MAP_MAX_X - 225, 0, -90);
			pos[3] = VGet(MAP_MAX_X - 275, 0, -90);
		}
	}
	inline VECTOR getRotation(int index) {//��]�ʂ�z��̌ʂŕԂ��imodel�̃I�[�o�[���[�h
		return rot[index];
	}
	inline void randColor(int c1, int c2) {
		for (int i = 0; i < ENEMY_NUM; ++i) {
			for (int n = 0; n < ENEMY_NUM; ++n) {
				if (color[i] == color[n]||color[i] == c1||color[i] == c2) {//�G�̐F�����Ԃ��Ă����烉���_����
					color[i] = GetRand(COLOR_NUM - 1);
				}
			}
		}
	}
	inline int getColor(int index) {
		return color[index];
	}

	inline VECTOR getTopPos(int index) {//��[�̍��W��Ԃ�
		return topPos[index];
	}
	inline VECTOR getbootPos(int index) {//���̍��W��Ԃ�
		return bootPos[index];
	}
	inline VECTOR getRPos(int index, int num) {//���E���̍��W��Ԃ�
		return rightPos[index][num];
	}
	inline VECTOR getLookPos(int index) {
		return lookPos[index];
	}
	inline void reset(int index) {
		pos[index] = oldpos[index];
	}
	inline void hitTop(int index) {//��[�ɓ����������̐ݒ�
		pos[index] = oldpos[index];
		speed[index] = -speedMax[index] / 5;
		pos[index].x -= sinf(rot[index].y) * (speed[index]);
		pos[index].z -= cosf(rot[index].y) * (speed[index]);
		rot[index].y -= 0.01;
	}
	inline void hitBoot(int index) {//���ɓ����������̐ݒ�
		pos[index] = oldpos[index];
		speed[index] = speedMax[index] / 5;
		pos[index].x -= sinf(rot[index].y) * (speed[index]);
		pos[index].z -= cosf(rot[index].y) * (speed[index]);
	}
	inline void hitR(int index, int num) {//���E�ɓ����������̐ݒ�
		if (num == 0)rot[index].y -= 0.01;
		if (num == 1)rot[index].y += 0.01;
	}
	inline void hitLook(int index, int num) {//���E�̎��_�ʒu�ɓ����������̐ݒ�
		if (num == 0) rot[index].y += rotUp[index];
		if (num == 1) rot[index].y -= rotUp[index];
	}

	inline void onisMove() {
		for (int i = 0; i < ENEMY_NUM; i++) isMove[i] = true;
	}
	inline bool getisMove(int index) {
		return isMove[index];
	}
	inline void defon(int index) {
		if (speed[index] > 0)isDef[index] = true;
	}
	inline void defoff(int index) {
		if (speed[index] > 0)isDef[index] = false;
	}
	inline void onSlip(int index) {
		isSlip[index] = true;
	}
	inline void setItem(int index) {//�A�C�e������ɓ��ꂽ��
		if (item[index] == 0) {
			for (int n = 0;n < 3;n++) isCandy[index][n] = false;
			isBom2[index] = false;
			item[index] = GetRand(3) + 1;
			time[index] = 200 + (GetRand(4) * 200);
		}
	}
	inline int getItem(int index) {
		return item[index];
	}
	inline void onDash(int index) {
		isDash[index] = true;
		time[index] = 150;
	}
	inline bool getisDash(int index) {//�_�b�V�����g������
		return isDash[index];
	}
	inline void setCandy(int index) {//�L�����f�B�[����肵���狅���ő吔�ɃZ�b�g����
		if (candy[index] == 0)candy[index] = 3;
	}
	inline void offisCandy(int index, int num) {//�L�����f�B�[���g���؂�
		isCandy[index][num] = false;
	}
	inline bool getisCandy(int index, int num) {
		return isCandy[index][num];
	}
	inline bool getisStick(int index) {//�X�e�B�b�N���g������
		return isStick[index];
	}
	inline void offStick(int index) {
		isStick[index] = false;
	}
	inline bool getisBom(int index) {//�{�����g������
		return isBom[index];
	}
	inline void offBom(int index) {
		isBom[index] = false;
	}
	inline bool getisBom2(int index) {//�{���𓊂�����
		return isBom2[index];
	}
	inline void offBom2(int index) {
		isBom2[index] = false;
	}
	//����p
	inline int getCheck(int index) {
		return check[index];
	}
	inline void checkSet(int index, int nun) {
		check[index] = nun;
	}
	inline void checkAdd(int index, int nun) {
		if (check[index] == nun - 1) check[index] = nun;
	}
	inline void trackAdd(int index) {
		if (check[index] == 8) {
			check[index] = 0;
			track[index]++;
		}
	}
	inline int getTrack(int index) {
		return track[index];
	}
	inline void setDistance(int index, VECTOR checkpos) {//�`�F�b�N�|�C���g�Ƃ̋��������
		distanceVec[index] = VSub(checkpos, pos[index]);
		distance[index] = VSize(distanceVec[index]);
	}
	inline float getDistanse(int index) {//�`�F�b�N�|�C���g�Ƃ̋�����n��
		return distance[index];
	}
	inline bool getisGoal(int index) {
		return isGoal[index];
	}
private:
	Model* enemy[ENEMY_NUM];
	int color[ENEMY_NUM];
	//�ړ��p
	VECTOR oldpos[ENEMY_NUM];
	VECTOR pos[ENEMY_NUM];
	VECTOR rot[ENEMY_NUM];		//��]
	float speed[ENEMY_NUM];//�ړ��̉����p
	float angle[ENEMY_NUM];//��]�̉����p
	bool isMove[ENEMY_NUM];//������=true
	bool isDef[ENEMY_NUM];//�_�[�g�]�[���ɓ����Ă�=true
	bool isSlip[ENEMY_NUM];//�X���b�v����=true
	bool isGoal[ENEMY_NUM];//�S�[������=true
	//�Œ�ϐ�
	const float speedMax[COLOR_NUM] = { 1.58f,1.59f,1.59f,1.58f,1.55f,1.56f };//�Ԃ��Ƃ̉������E�l
	const float speedUp[COLOR_NUM] = { 0.01f,0.02f,0.02f,0.01f,0.01f,0.02f };//�Ԃ��Ƃ̉������x
	const float speedDef[COLOR_NUM] = { 0.7f,0.5f,0.4f,0.4f,0.7f,0.5f };//�Ԃ��Ƃ̌����������̑��x
	const float rotUp[COLOR_NUM] = { 0.015f,0.013f,0.012f,0.012f,0.015f,0.013f };//�Ԃ��Ƃ̉�]�������x
	//�A�C�e���p
	int item[ENEMY_NUM];//�����Ă���A�C�e���̔ԍ�
	float time[ENEMY_NUM];//�A�C�e���C���^�[�o�����Ԍv���p
	float rtime[ENEMY_NUM];//�����_���C���^�[�o�����Ԍv���p
	bool isDash[ENEMY_NUM];//�_�b�V�����Ă�=true
	bool isCandy[ENEMY_NUM][3];//�L�����f�B�[���g����=true :[player][candyNum]
	int candy[ENEMY_NUM];//�����Ă���L�����f�B�[�̐�
	bool isStick[ENEMY_NUM];//�X�e�B�b�N���g����=true
	bool isBom[ENEMY_NUM];//�{�����g����=true
	bool isBom2[ENEMY_NUM];//�{���𓊂��Ďg����=true
	//����p
	int check[ENEMY_NUM]; //�`�F�b�N�|�C���g
	int track[ENEMY_NUM]; //����
	int rank[ENEMY_NUM]; //����
	VECTOR distanceVec[ENEMY_NUM];//�`�F�b�N�|�C���g�Ƃ̋���(VECTOR
	float distance[ENEMY_NUM]; //�`�F�b�N�|�C���g�Ƃ̋���(float
	//�G�̓����蔻��
	VECTOR topPos[ENEMY_NUM]; //�G�̐擪��pos
	VECTOR bootPos[ENEMY_NUM]; //�G�̍Ō����pos
	VECTOR rightPos[ENEMY_NUM][2]; //�G�̍��E��pos�@[player][���E]
	VECTOR lookPos[ENEMY_NUM]; //�G�̍��E��pos�@[player]

};				