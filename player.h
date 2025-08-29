#pragma once
#include"model.h"
#include"sound.h"
class Player {
public:
	Player();//�ݽ�׸�
	~Player() {};//�޽�׸�
	void init();//����������
	void load();//���f���ǂݍ���
	void ctrl();//���쏈��
	void draw();//�\������

	inline void setColor(int index, int clr) {
		color[index] = clr;
	}
	inline int getColor(int index) {
		return color[index];
	}
	//�����蔻��
	inline VECTOR getPos(int index) {//���W��z��̌ʂŕԂ��imodel�̃I�[�o�[���[�h
		return pos[index];
	}
	inline void initPos(int map) {//�}�b�v���Ƃɏ����l��ς���
		if (map == 1) {
			pos[0] = VGet(MAP_MAX_X - 210, 0, -410);
			pos[1] = VGet(MAP_MAX_X - 160, 0, -410);
		}
		if (map == 2) {
			pos[0] = VGet(MAP_MAX_X - 210, 0, -440);
			pos[1] = VGet(MAP_MAX_X - 160, 0, -440);
		}
		if (map == 3) {
			pos[0] = VGet(MAP_MAX_X - 250, 0, -120);
			pos[1] = VGet(MAP_MAX_X - 200, 0, -120);
		}
	}
 	inline VECTOR getRotation(int index) {//��]�ʂ�z��̌ʂŕԂ��imodel�̃I�[�o�[���[�h
		return rot[index];
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
	}
	inline void hitBoot(int index) {//���ɓ����������̐ݒ�
		pos[index] = oldpos[index];
		speed[index] = speedMax[index] / 5;
		pos[index].x -= sinf(rot[index].y) * (speed[index]);
		pos[index].z -= cosf(rot[index].y) * (speed[index]);
	}
	inline void hitR(int index,int num) {//���E�ɓ����������̐ݒ�
		pos[index] = oldpos[index];
		if(num==0) rot[index].y -= rotUp[index];
		if(num==1) rot[index].y += rotUp[index];
	}
	inline void hitLook(int index, int num) {//���E�̎��_�ʒu�ɓ����������̐ݒ�
		if (num == 0) rot[index].y += rotUp[index];
		if (num == 1) rot[index].y -= rotUp[index];
	}
	//�A�C�e���p
	inline void setItem(int index) {//�A�C�e������ɓ��ꂽ��
		if (item[index] == 0) {
			for (int n = 0;n < 3;n++) isCandy[index][n]=false;
			isBom2[index]=false;
			item[index] = GetRand(3) + 1;
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
		if(candy[index] == 0)candy[index] = 3;
	}
	inline void offisCandy(int index, int num) {//�L�����f�B�[���g���؂�
		isCandy[index][num] = false;
	}
	inline bool getisCandy(int index,int num) {
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
	
	inline void onSlip(int index) {
		isSlip[index] = true;
		se[1]->SE_Play();
	}
	inline void defon(int index) {
		if (speed[index] > 0)isDef[index] = true;
	}
	inline void defoff(int index) {
		if (speed[index] > 0)isDef[index] = false;
	}
	
	inline void onisMove() {
		for (int i = 0; i < 2; i++) isMove[i] = true;
	}
	inline bool getisMove(int index) {
		return isMove[index];
	}
	
	//����p
	inline void checkSet(int index, int nun) {
		check[index] = nun;
	}
	inline void checkAdd(int index, int nun) {
		if (check[index] == nun - 1) check[index] = nun;
	}
	inline int getCheck(int index) {
		return check[index];
	}

	inline void trackAdd(int index) {
		if (check[index] == 8) {
			check[index] = 0;
			track[index] ++;
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

	inline void setRank(int index,int rnk) {
		rank[index] = rnk;
	}
	
	inline bool getisGoal(int index) {
		return isGoal[index];
	}
private:
	Model* player[PLAYER_NUM];
	int color[PLAYER_NUM];//�Ԃ̐F
	//�T�E���h
	Sound* se[2];
	//�ړ��p
	VECTOR oldpos[PLAYER_NUM];
	VECTOR pos[PLAYER_NUM];//���W
	VECTOR rot[PLAYER_NUM];//��]
	float speed[PLAYER_NUM];//�ړ��̉����p
	float angle[PLAYER_NUM];//��]�̉����p
	bool isMove[PLAYER_NUM];//������=true
	bool isDef[PLAYER_NUM];//�_�[�g�]�[���ɓ����Ă�=true
	bool isSlip[PLAYER_NUM];//�X���b�v����=true
	bool isGoal[PLAYER_NUM];//�S�[������=true
	DINPUT_JOYSTATE input[PLAYER_NUM];//�R���g���[���[�ݒ�
	//�Œ�ϐ�
	const float speedMax[COLOR_NUM] = {1.52f,1.54f,1.55f,1.54f,1.51f,1.53f};//�Ԃ��Ƃ̉������E�l
	const float speedUp[COLOR_NUM] = {0.011f,0.012f,0.013f,0.013f,0.011f,0.013f};//�Ԃ��Ƃ̉������x
	const float speedDef[COLOR_NUM] = {0.7f,0.5f,0.4f,0.4f,0.7f,0.5f};//�Ԃ��Ƃ̌����������̑��x
	const float rotUp[COLOR_NUM] = { 0.011f,0.011f,0.01f,0.01f,0.012f,0.011f };//�Ԃ��Ƃ̉�]�������x
	//�A�C�e���p
	int item[PLAYER_NUM];//�����Ă���A�C�e���̔ԍ�
	float time[PLAYER_NUM];//�C���^�[�o�����Ԍv���p
	bool isDash[PLAYER_NUM];//�_�b�V�����Ă�=true
	bool isCandy[PLAYER_NUM][3];//�L�����f�B�[���g����=true :[player][candyNum]
	int candy[PLAYER_NUM];//�����Ă���L�����f�B�[�̐�
	bool isStick[PLAYER_NUM];//�X�e�B�b�N���g����=true
	bool isBom[PLAYER_NUM];//�{�����g����=true
	bool isBom2[PLAYER_NUM];//�{���𓊂��Ďg����=true
	//����p
	int check[PLAYER_NUM]; //�`�F�b�N�|�C���g
	int track[PLAYER_NUM]; //����
	int rank[PLAYER_NUM]; //����
	VECTOR distanceVec[PLAYER_NUM];//�`�F�b�N�|�C���g�Ƃ̋���(VECTOR
	float distance[PLAYER_NUM]; //�`�F�b�N�|�C���g�Ƃ̋���(float
	//�v���C���[�̓����蔻��
	VECTOR topPos[PLAYER_NUM]; //�v���C���[�̐擪��pos
	VECTOR bootPos[PLAYER_NUM]; //�v���C���[�̍Ō����pos
	VECTOR rightPos[PLAYER_NUM][2]; //�v���C���[�̍��E��pos�@[player][���E]
	VECTOR lookPos[PLAYER_NUM]; //�v���C���[�̍��E��pos�@[player]

};

