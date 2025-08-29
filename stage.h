#pragma once
#include"model.h"
#include"sound.h"

class Stage :public Model{
public:
	Stage();
	~Stage() {};
	void init();
	void ctrl();
	void show();
	inline Mode getMode() {
		return mode;
	}
	//�T�E���h
	inline void setMode(Mode set) {
		mode = set;
	}
	inline int getMap() {
		return map;
	}
	//TITLE
	inline VECTOR getbottuntPos(int index) {
		return bPos[index];
	}
	inline int getbuttonNum(int index) {
		return buttonNum[index];
	}
	inline void onMenu() {
		if (time == 0 && !isMenu) {
			isMenu = true;
			time = 30;
			se[1]->SE_Play();
		}
	}
	inline bool getMenu() {
		return isMenu;
	}
	//SETTING
	inline void onChenge(int index) {
		isChange[index] = true;
	}
	inline void offChenge(int index) {
		isChange[index] = false;
	}
	inline void setColor(int index, int col) {
		color[index] = col;
	}
	inline void uiLoad() {
		for (int i = 0; i < COLOR_NUM; i++) {
			if (color[i] == 0) ui[i]->loadImage("image/player.png");
			if (color[i] == 1) ui[i]->loadImage("image/player (1).png");
			if (color[i] == 2) ui[i]->loadImage("image/player (2).png");
			if (color[i] == 3) ui[i]->loadImage("image/player (3).png");
			if (color[i] == 4) ui[i]->loadImage("image/player (4).png");
			if (color[i] == 5) ui[i]->loadImage("image/player (5).png");
		}
	}
	inline bool getChenge(int index) {
		return isChange[index];
	}
	//PLAY
	inline float getTime() {
		return time;
	}
	inline int getMHandle2() {
		return corner->getMHandle();
	}
	//����p
	inline float getSize(int index) {
		return csize[index];
	}
	inline VECTOR getCheck(int index) {
		return checkPos[index];
	}
	inline void setUiPos(int index, int chc, int trk,float dis,bool gol) {
		check[index] = chc;
		track[index] = trk;
		distance[index] = dis;
		isGoal[index] = gol;
	}
	inline int getRank(int index) {
		return rank[index];
	}
	inline int getMHandleLoad(int index) {
		return load[index]->getMHandle();
	}
	//�A�C�e���p
	inline VECTOR getDashPos(int index) {
		return dashPos[index];
	}
	inline VECTOR getBomPos(int index) {
		return bomPos[index];
	}
	inline void hitBom(int index) {
		bomPos[index].y = -20;
	}
private:
	Mode mode;//���[�h�̊֐�
	int map;//�}�b�v�̎��
	//�T�E���h
	Sound* bgm;
	Sound* se[5];

	//TITLE
	Image* title;
	Image* pin[PLAYER_NUM];//�I����ʂ̃J�[�\���摜
	VECTOR pinPos[PLAYER_NUM];//�I����ʂ̃J�[�\���ʒu
	Image* Bottun[8];//�I����ʂ̃{�^���摜
	VECTOR bPos[8];//�I����ʂ̃{�^���ʒu
	int buttonNum[PLAYER_NUM];//�I����ʂ̃{�^���̔ԍ�
	int up[PLAYER_NUM];//�㉺�L�[���������u�Ԃ̏��������邽�߂̕ϐ�
	int right[PLAYER_NUM];//���E�L�[���������u�Ԃ̏��������邽�߂̕ϐ�
	Image* menu;
	bool isMenu;//���j���[���J���Ă��遁true

	//SETTING
	Model* car[COLOR_NUM];//�I����ʂŕ\������ԃ��f��
	VECTOR pos[PLAYER_NUM];//�Ԃ̕\���ʒu
	VECTOR rot[PLAYER_NUM];//�Ԃ̉�]��
	bool isChange[PLAYER_NUM];//�F�����Ȃ��悤�ɑI���������A���ĂȂ���������
	int color[COLOR_NUM];//�v���C���[�̑I�񂾐F
	Image* ok[PLAYER_NUM];//�F��I�����I������\������郂�f��
	
	DINPUT_JOYSTATE input[PLAYER_NUM];//�R���g���[���[�ϐ�

	//PLAY
	float time;
	Image* count[4];//�X�^�[�g�J�E���g�_�E����UI
	Model* corner;//�R�[�i�[�G���A�̃��f��
	Image* rankui[COLOR_NUM];//�����ɕ\�����鏇��UI

	//����p
	Model* load[2];//�����ŃJ�[�u���Ȃ���p�̓����蔻�胂�f��
	VECTOR checkPos[9];//�`�F�b�N�|�C���g���C���̍��W
	float csize[9];//�`�F�b�N�|�C���g�̃T�C�Y
	int check[COLOR_NUM]; //�`�F�b�N�|�C���g
	int track[COLOR_NUM]; //����
	int rank[COLOR_NUM]; //����
	float distance[COLOR_NUM]; //�`�F�b�N�|�C���g�Ƃ̋���(float
	bool isGoal[COLOR_NUM];//�S�[������=true
	int sortedIndices[COLOR_NUM]; // �\�[�g���ꂽ�C���f�b�N�X��ێ�

	//�t�B�[���h�ɒu���A�C�e��
	Model* dash;//�G���ƃ_�b�V���o����
	VECTOR dashPos[6];//�_�b�V���̍��W
	Model* bom;//�G���ƃX���b�v����
	VECTOR bomPos[4];//�{���̍��W
	int btime[4];//�{���������Ă��畜�A����܂ł̃J�E���g
	VECTOR objRot;//�A�C�e���̉�]��

	//��ʏ�ɕ\������UI
	Image* course;//��ɕ\�������
	Image* ui[COLOR_NUM];//�L�����ɍ��킹�Đi�܂���UI
	VECTOR uiPos[COLOR_NUM];//UI�̍��W
	Image* rankbord[2];//�X�R�A��\������{�[�h
	Image* goal;//�S�[���������ɕ\������e�L�X�gUI

	//FIN
	Model* oukan;//�D���҂ɂ��Ԃ��鉤��
	VECTOR orot;//���������v���C���[�ɔ킹�鉤���̉�]��	
	int point[COLOR_NUM];//�����_
};