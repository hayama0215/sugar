#include"game.h"
#include"collision.h"
#include"sound.h"
#include"camera.h"
#include"item.h"
#include"dust.h"
#include"enemy.h"
#include"player.h"
#include"stage.h"

//��̃I�u�W�F�N�g��
class Sound* se[4];//�T�E���hse
class Camera* camera;//�J����
class Item* item;//�A�C�e��
class Dust*	dust[COLOR_NUM];//����
class Enemy* enemy;//�G
class Player* player;//�v���C���[
class Stage* stage;//�X�e�[�W

Game::Game(){
	//���g������
	for (int i = 0; i < 4;i++) se[i] = new Sound;
	se[0]->loadSound("sound/����3.mp3");
	se[1]->loadSound("sound/�A�C�e��.mp3");
	se[2]->loadSound("sound/�X�^�[�g����.mp3");
	se[3]->loadSound("sound/�L�����Z��.mp3");
	camera = new Camera;
	item = new Item;
	for (int i = 0; i < COLOR_NUM;i++) {
		dust[i] = new Dust;
		Color[i] = 0;
	}
	enemy = new Enemy;
	player = new Player;
	stage = new Stage;
	init();
}

Game::~Game(){
	for (int i = 0; i < 4; i++) delete se[i];
	delete camera;
	for (int i = 0; i < COLOR_NUM; i++) delete dust[i];
	delete item;
	delete enemy;
	delete player;
	delete stage;
}

void Game::init() {
	camera->setCamera(VGet(MAP_MAX_X - 190, 25, -300), VGet(MAP_MAX_X - 190, 20, -320));
	item->init();
	enemy->init();
	player->init();
	stage->init();
	time = 0;
}

void Game::ctrl() {
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input[0]);//�R���g���[���[�̓��͏󋵂��擾
	GetJoypadDirectInputState(DX_INPUT_PAD2, &input[1]);
	switch (stage->getMode()){
	case Mode::TITLE:
		for (int i = 0;i < 2;i++) {
			if (input[i].Buttons[2] > 1 || input[i].Buttons[3] > 1 || GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || CheckHitKey(KEY_INPUT_LSHIFT)) {
				if (time == 0) {
					time++;
					if (stage->getbuttonNum(0) == 0) stage->onMenu();
					if (stage->getbuttonNum(0) == 1) {
						stage->setMode(Mode::SETTING);
						se[0]->SE_Play();
						init();
					}
					if (time == 30)time = 0;
				}
			}
			else time = 0;
		}
		stage->ctrl();
		break;
	case Mode::SETTING:
		for (int i = 0;i < PLAYER_NUM;i++) {
			if (input[i].Buttons[2] > 1 || input[i].Buttons[3] > 1 || GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN)) {
				if (time == 0) {
					time++;
					if (stage->getChenge(0) && stage->getChenge(1)) {
						stage->setMode(Mode::PLAY);
						init();
						se[2]->SE_Play();
						item->initPos(stage->getMap());//�A�C�e���������l�ɔ�΂�
						//�v���C���[�ݒ�
						player->initPos(stage->getMap());//�v���C���[�������l�ɔ�΂�
						for (int n = 0;n < PLAYER_NUM;n++)player->setColor(n, Color[n]);
						player->load();//stage�ŕς����Ԃ�player�Ŏg��
						//�G�ݒ�
						enemy->initPos(stage->getMap());//�G�������l�ɔ�΂�
						enemy->randColor(player->getColor(0), player->getColor(1));//�G�̐F�������_���Őݒ肷��
						enemy->load();//�ς����F�����[�h����
						for (int e = 0;e < ENEMY_NUM;e++) {
							Color[e + PLAYER_NUM] = enemy->getColor(e);
							stage->setColor(e + PLAYER_NUM, Color[e + PLAYER_NUM]);
						}
						stage->uiLoad();
					}
					if (stage->getbuttonNum(0) == 6 || stage->getbuttonNum(1) == 6) {
						stage->setMode(Mode::TITLE);
						se[3]->SE_Play();
						init();
					}
				}
			}
			else time = 0;
			
			if (CheckHitKey(KEY_INPUT_LSHIFT) || input[0].Buttons[6] > 1 || input[0].Buttons[7] > 1) {
				if (stage->getbuttonNum(0) != 6) {
					stage->onChenge(0);
					if(Color[0] != stage->getbuttonNum(0)) se[0]->SE_Play();
				}
				Color[0] = stage->getbuttonNum(0);
			}
			if (CheckHitKey(KEY_INPUT_RSHIFT) || input[1].Buttons[6] > 1 || input[1].Buttons[7] > 1) {
				if (stage->getbuttonNum(1) != 6) {
					stage->onChenge(1);
					if (Color[1] != stage->getbuttonNum(1)) se[0]->SE_Play();
				}
				Color[1] = stage->getbuttonNum(1);
			}
			if (stage->getChenge(0)) {
				if (input[0].Buttons[0] > 1 || input[0].Buttons[1] > 1 || CheckHitKey(KEY_INPUT_S) || input[0].Y > 1 || CheckHitKey(KEY_INPUT_W) || input[0].Y < -1 || CheckHitKey(KEY_INPUT_A) || input[0].X < -1|| CheckHitKey(KEY_INPUT_D) || input[0].X > 1) {
					se[3]->SE_Play();
					stage->offChenge(0);
				}
			}
			if (stage->getChenge(1)){
				if (input[1].Buttons[0] > 1 || input[1].Buttons[1] > 1|| CheckHitKey(KEY_INPUT_DOWN) || input[1].Y > 1 || CheckHitKey(KEY_INPUT_UP) || input[1].Y < -1 || CheckHitKey(KEY_INPUT_LEFT) || input[1].X < -1 || CheckHitKey(KEY_INPUT_RIGHT) || input[1].X > 1) {
					se[3]->SE_Play();
					stage->offChenge(1);
				}
			}
			stage->setColor(i, Color[i]);
		}
		stage->ctrl();
		break;
	case Mode::PLAY:
		stage->ctrl();
		if (65 < stage->getTime() && stage->getTime() < 75) {
			player->onisMove();
			enemy->onisMove();
		}
		player->ctrl();
		VECTOR playerCollision[PLAYER_NUM],playerTopCollision[PLAYER_NUM],playerbootCollision[PLAYER_NUM],playerRCollision[PLAYER_NUM][2], playerLookCollision[PLAYER_NUM];//�v���C���[�̓����蔻��͈̔͐ݒ�
		enemy->ctrl();
		VECTOR enemyCollision[ENEMY_NUM], enemyTopCollision[ENEMY_NUM], enemybootCollision[ENEMY_NUM], enemyRCollision[ENEMY_NUM][2], enemyLookCollision[ENEMY_NUM];//�G�̓����蔻��͈̔͐ݒ�

		for (int i = 0; i < PLAYER_NUM; i++) {//�v���C���[�̐ݒ�
			camera->ctrl(player->getPos(i), player->getRotation(i), i);//�J�������v���C���[��ǔ�
			playerCollision[i] = player->getPos(i);//�v���C���[���W
			playerTopCollision[i] = player->getTopPos(i);//��[�̍��W
			playerTopCollision[i].y += 6;
			playerbootCollision[i] = player->getbootPos(i);//���̍��W
			playerbootCollision[i].y += 6;
			for (int n = 0; n < 2; n++) {
				playerRCollision[i][n] = player->getRPos(i, n);//���E�̍��W
				playerRCollision[i][n].y += 6;
			}
			playerLookCollision[i] = player->getLookPos(i);//�ڐ���̍��W
			//�v���C���[�ƕǂ̔���
			if (collCheck_Capsule(stage->getMHandle(), playerTopCollision[i], playerTopCollision[i], 4)) player->hitTop(i);//�O�����������ꍇ
			if (collCheck_Capsule(stage->getMHandle(), playerbootCollision[i], playerbootCollision[i], 5)) player->hitBoot(i);//��낪���������ꍇ
			if (collCheck_Capsule(stage->getMHandle(), playerRCollision[i][0], playerRCollision[i][0], 5)) player->hitR(i, 0);//�E�����������ꍇ
			else if (collCheck_Capsule(stage->getMHandle(), playerRCollision[i][1], playerRCollision[i][1], 5)) player->hitR(i, 1);//�������������ꍇ
			else {
				if (player->getisMove(i) || player->getisGoal(i)) {
					if (collCheck_Capsule(stage->getMHandleLoad(0), playerTopCollision[i], playerLookCollision[i], 60) && player->getisGoal(i)) player->hitLook(i, 0);//���_���W�����������ꍇ
					if (collCheck_Capsule(stage->getMHandleLoad(1), playerTopCollision[i], playerLookCollision[i], 60) && player->getisGoal(i)) player->hitLook(i, 1);//���_���W�����������ꍇ
				}
			}
			//�v���C���[���m�̓����蔻��
			if (hitCheck_Sphere(playerTopCollision[0], 4, playerTopCollision[1], 4)) {//�O���m�����������ꍇ
				player->hitTop(0);
				player->hitTop(1);
			}
			if (hitCheck_Sphere(playerbootCollision[0], 5, playerbootCollision[1], 5)) {//��듯�m�����������ꍇ
				player->hitBoot(0);
				player->hitBoot(1);
			}
			if (hitCheck_Sphere(playerTopCollision[0], 4, playerbootCollision[1], 5)) {//�O�ƌ�낪���������ꍇ
				player->hitTop(0);
				player->hitBoot(1);
			}
			if (hitCheck_Sphere(playerbootCollision[0], 5, playerTopCollision[1], 4)) {//���ƑO�����������ꍇ
				player->hitBoot(0);
				player->hitTop(1);
			}
			for (int n = 0; n < 2; n++) {
				for (int r = 0; r < 2; r++) {
					if (hitCheck_Sphere(playerRCollision[0][n], 5, playerRCollision[1][r], 5)) {//�E�ƍ������������ꍇ
						player->hitR(0, n);
						player->hitR(1, r);
					}
				}
				if (hitCheck_Sphere(playerRCollision[0][n], 5, playerTopCollision[1], 4)) {//���E�ƑO�����������ꍇ
					player->hitR(0, n);
					player->hitTop(1);
				}
				if (hitCheck_Sphere(playerTopCollision[0], 4, playerRCollision[1][n], 5)) {//�O�ƍ��E�����������ꍇ
					player->hitTop(0);
					player->hitR(1, n);
				}
				if (hitCheck_Sphere(playerRCollision[0][n], 5, playerbootCollision[1], 5)) {//���E�ƌ�낪���������ꍇ
					player->hitR(0, n);
					player->hitBoot(1);
				}
				if (hitCheck_Sphere(playerbootCollision[0], 5, playerRCollision[1][n], 5)) {//���ƍ��E�����������ꍇ
					player->hitBoot(0);
					player->hitR(1, n);
				}
			}
			for (int e = 0;e < ENEMY_NUM;e++) {//�G�̐ݒ�
				enemyCollision[e] = enemy->getPos(e);//���W
				enemyTopCollision[e] = enemy->getTopPos(e);//��[�̍��W
				enemyTopCollision[e].y += 6;
				enemybootCollision[e] = enemy->getbootPos(e);//���̍��W
				enemybootCollision[e].y += 6;
				for (int n = 0; n < 2; n++) {
					enemyRCollision[e][n] = enemy->getRPos(e, n);//���E�̍��W
					enemyRCollision[e][n].y += 6;
				}
				enemyLookCollision[e] = enemy->getLookPos(e);//�ڐ���̍��W
				//�G�ƕǂ̔���
				if (collCheck_Capsule(stage->getMHandle(), enemyTopCollision[e], enemyTopCollision[e], 4)) enemy->hitTop(e);//�O�����������ꍇ
				if (collCheck_Capsule(stage->getMHandle(), enemybootCollision[e], enemybootCollision[e], 5)) enemy->hitBoot(e);//��낪���������ꍇ

				if (collCheck_Capsule(stage->getMHandle(), enemyRCollision[e][0], enemyRCollision[e][0], 5)) enemy->hitR(e, 0);//�E�����������ꍇ
				else if (collCheck_Capsule(stage->getMHandle(), enemyRCollision[e][1], enemyRCollision[e][1], 5)) enemy->hitR(e, 1);//�������������ꍇ
				else {
					if (enemy->getisMove(e)|| enemy->getisGoal(e)) {
						if (collCheck_Capsule(stage->getMHandleLoad(0), enemyTopCollision[e], enemyLookCollision[e], 70)) enemy->hitLook(e, 0);//���_���W�����������ꍇ
						if (collCheck_Capsule(stage->getMHandleLoad(1), enemyTopCollision[e], enemyLookCollision[e], 70)) enemy->hitLook(e, 1);//���_���W�����������ꍇ
					}
				}
				//�G���m�̓����蔻��
				for (int h = 0; h < ENEMY_NUM; h++) {
					if (e != h) {//�����̓����蔻��Ɠ�����Ȃ��p
						if (hitCheck_Sphere(enemyTopCollision[e], 4, enemyTopCollision[h], 4)) {//�O���m�����������ꍇ
							enemy->hitTop(e);
							enemy->hitTop(h);
						}
						if (hitCheck_Sphere(enemybootCollision[e], 5, enemybootCollision[h], 5)) {//��듯�m�����������ꍇ
							enemy->hitBoot(e);
							enemy->hitBoot(h);
						}
						else if (hitCheck_Sphere(enemyTopCollision[e], 4, enemybootCollision[h], 5)) {//�O�ƌ�낪���������ꍇ
							enemy->hitTop(e);
							enemy->hitBoot(h);
						}
						else if (hitCheck_Sphere(enemybootCollision[e], 5, enemyTopCollision[h], 4)) {//���ƑO�����������ꍇ
							enemy->hitBoot(e);
							enemy->hitTop(h);
						}
						for (int n = 0; n < 2; n++) {
							for (int r = 0; r < 2; r++) {
								if (hitCheck_Sphere(enemyRCollision[e][n], 5, enemyRCollision[h][r], 5)) {//�E�ƍ������������ꍇ
									enemy->hitR(e, n);
									enemy->hitR(h, r);
								}
							}
							if (hitCheck_Sphere(enemyRCollision[e][n], 3, enemyTopCollision[h], 4)) {//���E�ƑO�����������ꍇ
								enemy->hitR(e, n);
								enemy->hitTop(h);
							}
							else if (hitCheck_Sphere(enemyTopCollision[e], 4, enemyRCollision[h][n], 3)) {//�O�ƍ��E�����������ꍇ
								enemy->hitTop(e);
								enemy->hitR(h, n);
							}
							else if (hitCheck_Sphere(enemyRCollision[e][n], 3, enemybootCollision[h], 5)) {//���E�ƌ�낪���������ꍇ
								enemy->hitR(e, n);
								enemy->hitBoot(h);
							}
							else if (hitCheck_Sphere(enemybootCollision[e], 5, enemyRCollision[h][n], 3)) {//���ƍ��E�����������ꍇ
								enemy->hitBoot(e);
								enemy->hitR(h, n);
							}
						}
					}
				}
				//�v���C���[�ƓG�̓����蔻��
				if (hitCheck_Sphere(playerTopCollision[i], 4, enemyTopCollision[e], 4)) {//�O���m�����������ꍇ
					player->hitTop(i);
					enemy->hitTop(e);
				}
				else if (hitCheck_Sphere(playerbootCollision[i], 5, enemybootCollision[e], 5)) {//��듯�m�����������ꍇ
					player->hitBoot(i);
					enemy->hitBoot(e);
				}
				else if (hitCheck_Sphere(playerTopCollision[i], 4, enemybootCollision[e], 5)) {//�O�ƌ�낪���������ꍇ
					player->hitTop(i);
					enemy->hitBoot(e);
				}
				else if (hitCheck_Sphere(playerbootCollision[i], 5, enemyTopCollision[e], 4)) {//���ƑO�����������ꍇ
					player->hitBoot(i);
					enemy->hitTop(e);
				}
				for (int n = 0; n < 2; n++) {
					for (int r = 0; r < 2; r++) {
						if (hitCheck_Sphere(playerRCollision[i][n], 5, enemyRCollision[e][r], 5)) {//�E�ƍ������������ꍇ
							player->hitR(i, n);
							enemy->hitR(e, r);
						}
					}
					if (hitCheck_Sphere(playerRCollision[i][n], 3, enemyTopCollision[e], 4)) {//���E�ƑO�����������ꍇ
						player->hitR(i, n);
						enemy->hitTop(e);
					}
					else if (hitCheck_Sphere(playerTopCollision[i], 4, enemyRCollision[e][n], 3)) {//�O�ƍ��E�����������ꍇ
						player->hitTop(i);
						enemy->hitR(e, n);
					}
					else if (hitCheck_Sphere(playerRCollision[i][n], 3, enemybootCollision[e], 5)) {//���E�ƌ�낪���������ꍇ
						player->hitR(i, n);
						enemy->hitBoot(e);
					}
					else if (hitCheck_Sphere(playerbootCollision[i], 5, enemyRCollision[e][n], 3)) {//���ƍ��E�����������ꍇ
						player->hitBoot(i);
						enemy->hitR(e, n);
					}
				}
				//�_�b�V�������Ƃ��ɕ�������
				if (player->getisDash(i)) {//�v���C���[
					dust[i]->setPosition(playerCollision[i]);
					dust[i]->ctrl();
				}
				if (enemy->getisDash(e)) {//�G
					dust[e + PLAYER_NUM]->setPosition(enemyCollision[e]);
					dust[e + PLAYER_NUM]->ctrl();
				}
				//�A�C�e���{�b�N�X�ݒ�
				for (int n = 0; n < ITEM_MAX; n++) {
					if (hitCheck_Sphere(playerCollision[i], 5, item->getPos(n), 8)) {//�v���C���[
						item->getItem(n);
						player->setItem(i);
						se[1]->SE_Play();
					}
					if (hitCheck_Sphere(enemyCollision[e], 5, item->getPos(n), 8)) {//�G
						item->getItem(n);
						enemy->setItem(e);
					}
				}
				//�_�b�V���A�C�e���ݒ�
				if (player->getItem(i) == 1) item->setMilk(i, playerbootCollision[i]);//�v���C���[
				else item->removeMilk(i);
				if (enemy->getItem(e) == 1) item->setMilk(e + PLAYER_NUM, enemybootCollision[e]);//�G
				else item->removeMilk(e + PLAYER_NUM);
				VECTOR dashCollision[6];//�_�b�V���I�u�W�F�N�g�̓����蔻��
				for (int n = 0; n < 6; n++) {
					dashCollision[n] = stage->getDashPos(n);
					if (hitCheck_Sphere(playerCollision[i], 5, dashCollision[n], 5)) player->onDash(i);//�v���C���[
					if (hitCheck_Sphere(enemyCollision[e], 5, dashCollision[n], 5)) enemy->onDash(e);//�G
				}
				//�L�����f�B�[�ݒ�
				for (int n = 0;n < 3;n++) {
					item->setisCandy(i, n, player->getisCandy(i, n));//�v���C���[
					if (player->getItem(i) == 2) {
						item->setCandy(i, n, playerCollision[i], player->getRotation(i));
						player->setCandy(i);
					}
					item->setisCandy(e + PLAYER_NUM, n, enemy->getisCandy(e, n));//�G
					if (enemy->getItem(e) == 2) {
						item->setCandy(e + PLAYER_NUM, n, enemyCollision[e], enemy->getRotation(e));
						enemy->setCandy(e);
					}
					VECTOR candyCollision[COLOR_NUM][3];//�L�����f�B�[�̓����蔻��
					candyCollision[i][n] = item->getCandypos(i, n);//�v���C���[
					candyCollision[i][n].y -= 6;
					candyCollision[e + PLAYER_NUM][n] = item->getCandypos(e + PLAYER_NUM, n);//�G
					candyCollision[e + PLAYER_NUM][n].y -= 6;
					if (hitCheck_Sphere(playerCollision[0], 5, candyCollision[1][n], 2) && player->getisCandy(1, n)) {//�v���C���[���m��1��0�ɓ��������ꍇ
						player->onSlip(0);
						item->removeCandy(1, n);
					}
					if (hitCheck_Sphere(playerCollision[1], 5, candyCollision[0][n], 2) && player->getisCandy(0, n)) {//�v���C���[���m��0���P�ɓ��������ꍇ
						player->onSlip(1);
						item->removeCandy(0, n);
					}
					if (hitCheck_Sphere(playerCollision[i], 5, candyCollision[e + PLAYER_NUM][n], 2) && enemy->getisCandy(e + PLAYER_NUM, n)) {//�G���v���C���[�ɓ��������ꍇ
						player->onSlip(i);
						item->removeCandy(e + PLAYER_NUM, n);
					}
					if (hitCheck_Sphere(enemyCollision[e], 5, candyCollision[i][n], 2) && player->getisCandy(i, n)) {//�v���C���[���G�ɓ��������ꍇ
						enemy->onSlip(e);
						item->removeCandy(i, n);
					}
					for (int h = 0; h < ENEMY_NUM; h++) {
						if (e != h) {//�����̓����蔻��Ɠ�����Ȃ��p
							if (hitCheck_Sphere(enemyCollision[h], 5, candyCollision[e + PLAYER_NUM][n], 2) && enemy->getisCandy(e + PLAYER_NUM, n)) {//�G���m���v���C���[�ɓ��������ꍇ
								enemy->onSlip(h);
								item->removeCandy(e + PLAYER_NUM, n);
							}
						}
					}
				}
				//�X�e�B�b�N�ݒ�
				item->setisStick(i, player->getisStick(i));//�v���C���[
				if (player->getItem(i) == 3) item->setStick(i, playerCollision[i]);
				else {
					item->removeStick(i);
					player->offStick(i);
				}
				item->setisStick(e + PLAYER_NUM, enemy->getisStick(e));//�G
				if (enemy->getItem(e) == 3) item->setStick(e + PLAYER_NUM, enemyCollision[e]);
				else {
					item->removeStick(e + PLAYER_NUM);
					enemy->offStick(e);
				}
				VECTOR stickCollision[COLOR_NUM];//�X�e�B�b�N�̓����蔻��
				stickCollision[i] = item->getStickpos(i);
				stickCollision[e + PLAYER_NUM] = item->getStickpos(e + PLAYER_NUM);
				if (hitCheck_Sphere(playerCollision[0], 5, stickCollision[1], 5)) player->onSlip(0);//�v���C���[���m��1��0�ɓ��������ꍇ
				if (hitCheck_Sphere(playerCollision[1], 5, stickCollision[0], 5)) player->onSlip(1);//�v���C���[���m��0��1�ɓ��������ꍇ
				if (hitCheck_Sphere(playerCollision[i], 5, stickCollision[e + PLAYER_NUM], 5)) player->onSlip(i);//�G���v���C���[�ɓ��������ꍇ
				if (hitCheck_Sphere(enemyCollision[e], 5, stickCollision[i], 5)) enemy->onSlip(e);//�v���C���[���G�ɓ��������ꍇ
				for (int h = 0; h < ENEMY_NUM; h++) {
					if (e != h) {//�����̓����蔻��Ɠ�����Ȃ��p
						if (hitCheck_Sphere(enemyCollision[h], 5, stickCollision[e + PLAYER_NUM], 5)) enemy->onSlip(h);//�G���m�����������ꍇ
					}
				}
				//�{���ݒ�
				item->setisBom(i, player->getisBom(i), player->getisBom2(i));//�v���C���[
				if (player->getItem(i) == 4) item->setBom(i, playerbootCollision[i], player->getRotation(i));
				else {
					item->setBompos(i);
					if (item->getBompos(i).y <= 0) player->offBom2(i);
				}
				item->setisBom(e + PLAYER_NUM, enemy->getisBom(e), enemy->getisBom2(e));//�G
				if (enemy->getItem(e) == 4) item->setBom(e + PLAYER_NUM, enemybootCollision[e], enemy->getRotation(e));
				else {
					item->setBompos(e + PLAYER_NUM);
					if (item->getBompos(e + PLAYER_NUM).y <= 0) enemy->offBom2(e);
				}
				VECTOR bomCollision[COLOR_NUM];//�{���̓����蔻��
				bomCollision[i] = item->getBompos(i);
				bomCollision[i].y += 3;
				bomCollision[e + PLAYER_NUM] = item->getBompos(e + PLAYER_NUM);
				bomCollision[e + PLAYER_NUM].y += 3;
				for (int n = 0; n < COLOR_NUM; n++) {
					if (hitCheck_Sphere(playerTopCollision[i], 4, bomCollision[n], 3)) {//�v���C���[
						player->onSlip(i);
						if(n < PLAYER_NUM) player->offBom(n);
						else enemy->offBom(n - PLAYER_NUM);
					}
					if (hitCheck_Sphere(enemyTopCollision[e], 4, bomCollision[n], 3)) {//�G
						enemy->onSlip(e);
						if(n < PLAYER_NUM) player->offBom(n);
						else enemy->offBom(n - PLAYER_NUM);
					}
				}
				for (int n = 0; n < 4;n++) {
					VECTOR bomCollision[4];
					bomCollision[n] = stage->getBomPos(n);
					if (hitCheck_Sphere(playerCollision[i], 5, bomCollision[n], 3)) {//�v���C���[
						player->onSlip(i);
						stage->hitBom(n);
					}
					if (hitCheck_Sphere(enemyCollision[e], 5, bomCollision[n], 3)) {//�G
						enemy->onSlip(e);
						stage->hitBom(n);
					}
				}

			}
		}
		//�A�C�e���ݒ�
		item->ctrl();

		if (player->getisGoal(0) && player->getisGoal(1)) {//�v���C���[��l�Ƃ��S�[�������ꍇ
			time++;
			if (time > 700) {
				if (stage->getMap() == 3) {//�ŏI�X�e�[�W�ŏI���
					stage->setMode(Mode::FIN);
					init();
				}
				else {
					init();
					player->initPos(stage->getMap());
					enemy->initPos(stage->getMap());
					item->initPos(stage->getMap());
					stage->setMode(Mode::PLAY);
				}
			}
		}
		else {
			//�R�[�i�[�G���A�ݒ�
			for (int i = 0; i < PLAYER_NUM; i++) {//�v���C���[
				if (collCheck_Capsule(stage->getMHandle2(), playerCollision[i], playerCollision[i], 5)) player->defon(i);
				else player->defoff(i);
				for (int e = 0;e < ENEMY_NUM;e++) {//�G
					if (collCheck_Capsule(stage->getMHandle2(), enemyCollision[e], enemyCollision[e], 5)) enemy->defon(e);
					else enemy->defoff(e);
					//�`�F�b�N�|�C���g�Ƃ̋���
					player->setDistance(i, stage->getCheck(player->getCheck(i) + 1));//�v���C���[
					if (hitCheckLineX(playerTopCollision[i], stage->getCheck(1), stage->getSize(1))) player->checkSet(i, 1);//X�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineZ(playerTopCollision[i], stage->getCheck(2), stage->getSize(2))) player->checkAdd(i, 2);//Z�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineZ(playerTopCollision[i], stage->getCheck(3), stage->getSize(3))) player->checkAdd(i, 3);//Z�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineX(playerTopCollision[i], stage->getCheck(4), stage->getSize(4))) player->checkAdd(i, 4);//X�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineX(playerTopCollision[i], stage->getCheck(5), stage->getSize(5))) player->checkAdd(i, 5);//X�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineZ(playerTopCollision[i], stage->getCheck(6), stage->getSize(6))) player->checkAdd(i, 6);//Z�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineZ(playerTopCollision[i], stage->getCheck(7), stage->getSize(7))) player->checkAdd(i, 7);//Z�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineX(playerTopCollision[i], stage->getCheck(8), stage->getSize(8))) player->checkAdd(i, 8);//X�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineX(playerTopCollision[i], stage->getCheck(0), stage->getSize(0))) player->trackAdd(i);//X�����̐��i�`�F�b�N�|�C���g�j
					stage->setUiPos(i, player->getCheck(i), player->getTrack(i), player->getDistanse(i), player->getisGoal(i));
					player->setRank(i, stage->getRank(i));

					enemy->setDistance(e, stage->getCheck(enemy->getCheck(e) + 1));//�G
					if (hitCheckLineX(enemyTopCollision[e], stage->getCheck(1), stage->getSize(1))) enemy->checkSet(e, 1);//X�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineZ(enemyTopCollision[e], stage->getCheck(2), stage->getSize(2))) enemy->checkAdd(e, 2);//Z�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineZ(enemyTopCollision[e], stage->getCheck(3), stage->getSize(3))) enemy->checkAdd(e, 3);//Z�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineX(enemyTopCollision[e], stage->getCheck(4), stage->getSize(4))) enemy->checkAdd(e, 4);//X�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineX(enemyTopCollision[e], stage->getCheck(5), stage->getSize(5))) enemy->checkAdd(e, 5);//X�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineZ(enemyTopCollision[e], stage->getCheck(6), stage->getSize(6))) enemy->checkAdd(e, 6);//Z�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineZ(enemyTopCollision[e], stage->getCheck(7), stage->getSize(7))) enemy->checkAdd(e, 7);//Z�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineX(enemyTopCollision[e], stage->getCheck(8), stage->getSize(8))) enemy->checkAdd(e, 8);//X�����̐��i�`�F�b�N�|�C���g�j
					if (hitCheckLineX(enemyTopCollision[e], stage->getCheck(0), stage->getSize(0))) enemy->trackAdd(e);//X�����̐��i�`�F�b�N�|�C���g�j
					stage->setUiPos(e + PLAYER_NUM, enemy->getCheck(e), enemy->getTrack(e), enemy->getDistanse(e), enemy->getisGoal(e));
				}
			}
		}
		if (CheckHitKey(KEY_INPUT_T)) {
			stage->setMode(Mode::TITLE);
			init();
		}
		break;
	case Mode::FIN:
		for (int i = 0;i < PLAYER_NUM;i++) {
			if (input[i].Buttons[2] > 1 || input[i].Buttons[3] > 1 || GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN)) {
				if (time == 0) {
					se[0]->SE_Play();
					time++;
				}
			}
			if (time > 0) time++;
			if (time == 200) {
				stage->setMode(Mode::TITLE);
				init();
			}
		}
		stage->ctrl();
		break;
	}
}
void Game::draw() {
	switch (stage->getMode())
	{
	case Mode::TITLE:
		stage->show();
		break;
	case Mode::SETTING:
		stage->show();
		break;
	case Mode::PLAY:
		for (int i = 0; i < PLAYER_NUM; i++) {
			camera->draw(i);
			item->draw();
			for (int n = 0; n < PLAYER_NUM; n++) {
				if (player->getisDash(n)) dust[n]->draw();
			}
			for (int e = 0; e < ENEMY_NUM; e++) {
				if (enemy->getisDash(e)) dust[e + PLAYER_NUM]->draw();
			}
			enemy->draw();
			player->draw();
			stage->show();
		}
		break;
	case Mode::FIN:
		stage->show();
		break;
	}
}