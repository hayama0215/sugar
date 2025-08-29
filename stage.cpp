#include"stage.h"
Stage::Stage() {
	mode = Mode::TITLE;
	map = 0;
	//�T�E���h
	bgm = new Sound;
	for (int i = 0; i < 5;i++)se[i] = new Sound;
	se[0]->loadSound("sound/�I��2.mp3");
	se[1]->loadSound("sound/����3.mp3");
	se[2]->loadSound("sound/�J�E���g�_�E�� (1).mp3");
	se[3]->loadSound("sound/�J�E���g�_�E�� (2).mp3");
	se[4]->loadSound("sound/�L�����Z��.mp3");
	//TITLE
	title = new Image;
	title->loadImage("image/title.png");
	for (int i = 0;i < PLAYER_NUM;i++) {
		pin[i] = new Image;
		pinPos[i] = VGet(0, 0, 0);
		buttonNum[i] = up[i] = right[i] = 0;//buttonNum 0:���j���[�@1:�X�^�[�g
	}
	for (int i = 0; i < 8; i++)	Bottun[i] = new Image;//�I����ʂ̃{�^���摜
	Bottun[2]->loadImage("image/color (2).png");
	Bottun[3]->loadImage("image/bottun (2).png");
	Bottun[4]->loadImage("image/color (3).png");
	Bottun[5]->loadImage("image/color (4).png");
	Bottun[6]->loadImage("image/color (5).png");
	Bottun[7]->loadImage("image/bottun (3).png");
	bPos[2] = VGet(440,70,0);
	bPos[3] = VGet(910,70,0);	
	bPos[4] = VGet(20,160,0);
	bPos[5] = VGet(230,160,0);
	bPos[6] = VGet(440,160,0);
	bPos[7] = VGet(910,460,0);
	pin[0]->loadImage("image/pin.png");	
	pin[1]->loadImage("image/pin2.png");
	menu = new Image;
	menu->loadImage("image/menu.png");
	//SETTING
	for (int i = 0; i < COLOR_NUM; i++) {
		car[i] = new Model;
	}
	pos[0] = VGet(MAP_MAX_X - 170, 0, -350);
	pos[1] = VGet(MAP_MAX_X - 210, 0, -350);
	for (int i = 0; i < PLAYER_NUM; i++) {
		rot[i] = VGet(0, 0, 0);
		isChange[i] = false;
		color[i] = 0;
		ok[i] = new Image;
	}
	car[0]->loadModel("model/car/car.mqo");
	car[1]->loadModel("model/car/car (1).mqo");
	ok[0]->loadImage("image/ok.png");
	ok[1]->loadImage("image/ok2.png");
	//PLAY
	time = 0;
	for (int i = 0; i < 4;i++) count[i] = new Image;
	corner = new Model;
	for (int i = 0; i < COLOR_NUM; i++) rankui[i] = new Image;//�����ɕ\�����鏇��UI
	rankui[0]->loadImage("image/rank (1).png");
	rankui[1]->loadImage("image/rank (2).png");
	rankui[2]->loadImage("image/rank (3).png");
	rankui[3]->loadImage("image/rank (4).png");
	rankui[4]->loadImage("image/rank (5).png");
	rankui[5]->loadImage("image/rank (6).png");
	//����p
	for (int i = 0;i < 2;i++) load[i] = new Model;//�����ŃJ�[�u���Ȃ���p�̓����蔻�胂�f��
	for (int i = 0; i < 9;i++) {
		checkPos[i] = VGet(0, 0, 0);
		csize[i] = 0;
	}
	//�t�B�[���h�ɒu���A�C�e��
	dash = new Model;
	dash->loadModel("model/�X�e�[�W (2)/dash.mqo");
	for (int i = 0;i < 6;i++) dashPos[i] = VGet(0, 0, 0);
	bom = new Model;
	bom->loadModel("model/�X�e�[�W (3)/bom.mqo");
	for (int i = 0;i < 4;i++) {
		bomPos[i] = VGet(0, 0, 0);
		btime[i] = 0;
	}
	objRot = VGet(0, 0, 0);
	//��ʏ�ɕ\������UI
	course = new Image;
	course->loadImage("image/course.png");
	for (int i = 0;i < COLOR_NUM;i++) {
		ui[i] = new Image;
		uiPos[i] = VGet(0, 0, 0);
		rank[i] = 0;
	}
	for (int i = 0;i < 2;i++) rankbord[i] = new Image;
	rankbord[0]->loadImage("image/rankbord.jpg");
	rankbord[1]->loadImage("image/rankbord2.png");
	goal = new Image;//�S�[���������ɕ\������e�L�X�g�C���[�W
	goal->loadImage("image/goal.png");
	//FIN
	oukan = new Model;
	oukan->loadModel("model/oukan.mqo");
	orot = VGet(0, 0, 0);
}
	
void Stage::init() {
	switch (mode)
	{
	case Mode::TITLE:
		isMenu = false;
		time = 0;
		bgm->stopBGM();//bgm���~�߂�
		bgm->loadSound("sound/title.mp3");//�V����bgm��ǂݍ���
		bgm->playBGM();//bgm�𗬂�
		map = 0;
		buttonNum[0] = 1;
		SetBackgroundColor(80, 60, 40);
		loadModel("model/�X�e�[�W/stage.mqo");
		pinPos[0] = VGet((WND_W / 2) - 100, WND_H - 200, 0);
		Bottun[0]->loadImage("image/bottun.png");
		bPos[0] = VGet((WND_W / 2)-100, WND_H -300, 0);
		Bottun[1]->loadImage("image/bottun (1).png");
		bPos[1] = VGet((WND_W / 2)-100, WND_H - 200, 0);
		for (int i = 0; i < 2; i++) {
			isChange[i] = false;
			rot[i] = VGet(0, ToRadian(180), 0);
		}
		break;
	case Mode::SETTING:
		Bottun[0]->loadImage("image/color.png");
		Bottun[1]->loadImage("image/color (1).png");
		buttonNum[0] = 0;
		buttonNum[1] = 1;
		
		bPos[0] = VGet(20,70,0);
		bPos[1] = VGet(230,70,0);
		break;
	case Mode::PLAY:
		time = 0;
		for (int i = 0; i < COLOR_NUM; i++) uiPos[i] = VGet(WND_W / 2 - 300, 35, 0);
		map++;
		switch (map) {
		case 1:
			bgm->stopBGM();
			bgm->loadSound("sound/bgm (1).mp3");
			bgm->playBGM();
			SetBackgroundColor(80, 60, 40);
			count[0]->loadImage("image/3.png");
			count[1]->loadImage("image/2.png");
			count[2]->loadImage("image/1.png");
			count[3]->loadImage("image/go.png");

			loadModel("model/�X�e�[�W/stage.mqo");
			setupCollInfo();	//�����蔻��̍쐬
			corner->loadModel("model/�X�e�[�W/load.mqo");
			corner->setupCollInfo();	//�����蔻��̍쐬
			load[0]->loadModel("model/�X�e�[�W/loadin.mqo");
			load[0]->setupCollInfo();	//�����蔻��̍쐬
			load[1]->loadModel("model/�X�e�[�W/loadout.mqo");
			load[1]->setupCollInfo();	//�����蔻��̍쐬

			checkPos[0] = VGet(MAP_MAX_X - 170, 0, -340);
			csize[0] = 170;
			checkPos[1] = VGet(MAP_MAX_X - 150, 0, 400);
			csize[1] = 150;
			checkPos[2] = VGet(MAP_MAX_X - 320, 0, MAP_MAX_Z - 300);
			csize[2] = 300;
			checkPos[3] = VGet(-MAP_MAX_X + 470, 0, MAP_MAX_Z - 480);
			csize[3] = 120;
			checkPos[4] = VGet(-MAP_MAX_X + 210, 0, 320);
			csize[4] = 210;
			checkPos[5] = VGet(-MAP_MAX_X + 250, 0, -MAP_MAX_Z + 300);
			csize[5] = 250;

			checkPos[6] = VGet(-400, 0, -MAP_MAX_Z + 140);
			csize[6] = 140;
			checkPos[7] = VGet(MAP_MAX_X - 320, 0, -MAP_MAX_Z + 160);
			csize[7] = 160;
			checkPos[8] = VGet(MAP_MAX_X - 170, 0, -MAP_MAX_Z + 310);
			csize[8] = 170;

			for (int i = 0; i < 6; i++) dashPos[i] = VGet(0, -100, 0);
			for (int i = 0; i < 4; i++) bomPos[i] = VGet(0, -100, 0);
			break;
		case 2:
			bgm->stopBGM();
			bgm->loadSound("sound/bgm (2).mp3");
			bgm->playBGM();
			SetBackgroundColor(0, 120, 100);
			count[0]->loadImage("image/3.png");
			count[1]->loadImage("image/2.png");
			count[2]->loadImage("image/1.png");
			count[3]->loadImage("image/go.png");

			loadModel("model/�X�e�[�W (2)/stage2.mqo");
			setupCollInfo();	//�����蔻��̍쐬
			corner->loadModel("model/�X�e�[�W (2)/load2.mqo");
			corner->setupCollInfo();	//�����蔻��̍쐬
			load[0]->loadModel("model/�X�e�[�W (2)/loadin2.mqo");
			load[0]->setupCollInfo();	//�����蔻��̍쐬
			load[1]->loadModel("model/�X�e�[�W (2)/loadout2.mqo");
			load[1]->setupCollInfo();	//�����蔻��̍쐬

			checkPos[0] = VGet(MAP_MAX_X - 200, 0, -370);
			csize[0] = 200;
			checkPos[1] = VGet(MAP_MAX_X - 250, 0, 500);
			csize[1] = 250;
			checkPos[2] = VGet(500, 0, MAP_MAX_Z - 300);
			csize[2] = 300;
			checkPos[3] = VGet(-MAP_MAX_X + 400, 0, MAP_MAX_Z - 350);
			csize[3] = 350;
			checkPos[4] = VGet(-MAP_MAX_X + 200, 0, 0);
			csize[4] = 200;
			checkPos[5] = VGet(-MAP_MAX_X + 150, 0, -500);
			csize[5] = 150;
			checkPos[6] = VGet(-600, 0, -MAP_MAX_Z + 250);
			csize[6] = 250;
			checkPos[7] = VGet(300, 0, -MAP_MAX_Z + 200);
			csize[7] = 200;
			checkPos[8] = VGet(MAP_MAX_X - 300, 0, -500);
			csize[8] = 300;

			dashPos[0] = VGet(230, 0, -250);
			dashPos[1] = VGet(240, 0, 170);
			dashPos[2] = VGet(-500, 0, -730);
			dashPos[3] = VGet(-220, 0, 130);
			dashPos[4] = VGet(-290, 0, -130);
			dashPos[5] = VGet(400, 0, 850);
			for (int i = 0; i < 4; i++) bomPos[i] = VGet(0, -100, 0);

			break;
		case 3:
			bgm->stopBGM();
			bgm->loadSound("sound/bgm (2).mp3");
			bgm->playBGM();
			SetBackgroundColor(150, 200, 100);
			count[0]->loadImage("image/3.png");
			count[1]->loadImage("image/2.png");
			count[2]->loadImage("image/1.png");
			count[3]->loadImage("image/go.png");

			loadModel("model/�X�e�[�W (3)/stage3.mqo");
			setupCollInfo();	//�����蔻��̍쐬
			corner->loadModel("model/�X�e�[�W (3)/load3.mqo");
			corner->setupCollInfo();	//�����蔻��̍쐬
			load[0]->loadModel("model/�X�e�[�W (3)/loadin3.mqo");
			load[0]->setupCollInfo();	//�����蔻��̍쐬
			load[1]->loadModel("model/�X�e�[�W (3)/loadout3.mqo");
			load[1]->setupCollInfo();	//�����蔻��̍쐬

			checkPos[0] = VGet(MAP_MAX_X - 220, 0, -50);
			csize[0] = 220;
			checkPos[1] = VGet(MAP_MAX_X - 300, 0, 200);
			csize[1] = 300;
			checkPos[2] = VGet(0, 0, MAP_MAX_Z - 200);
			csize[2] = 200;
			checkPos[3] = VGet(-MAP_MAX_X + 470, 0, MAP_MAX_Z - 180);
			csize[3] = 180;
			checkPos[4] = VGet(-MAP_MAX_X + 250, 0, 520);
			csize[4] = 250;
			checkPos[5] = VGet(-MAP_MAX_X + 350, 0, -MAP_MAX_Z + 400);
			csize[5] = 350;
			checkPos[6] = VGet(-200, 0, -MAP_MAX_Z + 140);
			csize[6] = 140;
			checkPos[7] = VGet(290, 0, -MAP_MAX_Z + 280);
			csize[7] = 280;
			checkPos[8] = VGet(MAP_MAX_X - 320, 0, -310);
			csize[8] = 320;

			for (int i = 0; i < 2; i++) dashPos[i] = VGet(0, -100, 0);
			dashPos[2] = VGet(-450, 30, -760);
			bomPos[0] = VGet(-450, 0, 800);
			bomPos[1] = VGet(-410, 0, 850);
			bomPos[2] = VGet(-720, 0, 580);
			bomPos[3] = VGet(-840, 0, 480);
			
			break;
		}
		break;
	case Mode::FIN:
		SetBackgroundColor(150, 120, 100);
		loadModel("model/�X�e�[�W/stage.mqo");
		bgm->stopBGM();
		bgm->loadSound("sound/���U���g.mp3");
		bgm->playBGM();
		for (int e = 2; e < ENEMY_NUM+2; e++) {
			if (color[e] == 0) car[e]->loadModel("model/car/car.mqo");
			if (color[e] == 1) car[e]->loadModel("model/car/car (1).mqo");
			if (color[e] == 2) car[e]->loadModel("model/car/car (2).mqo");
			if (color[e] == 3) car[e]->loadModel("model/car/car (3).mqo");
			if (color[e] == 4) car[e]->loadModel("model/car/car (4).mqo");
			if (color[e] == 5) car[e]->loadModel("model/car/car (5).mqo");
		}
		break;
	default:
		break;
	}
}
void Stage::ctrl() {
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input[0]);
	GetJoypadDirectInputState(DX_INPUT_PAD2, &input[1]);
	switch (mode)
	{
	case Mode::TITLE:
		if (!isMenu) {
			if (CheckHitKey(KEY_INPUT_W) || input[0].Y < -1 || CheckHitKey(KEY_INPUT_UP) || input[1].Y < -1) {
				if (up[0] == 0) {
					buttonNum[0]++;
					se[0]->SE_Play();
					if (up[0] <= 20) up[0]++;
				}
			}
			else if (CheckHitKey(KEY_INPUT_S) || input[0].Y > 1|| CheckHitKey(KEY_INPUT_DOWN) || input[1].Y > 1) {
				if (up[0] == 0) {
					buttonNum[0]--;
					se[0]->SE_Play();
					if (up[0] <= 20) up[0]++;
				}
			}
			else {
				up[0] = 0;
			}
			if (buttonNum[0] <= 0) buttonNum[0] = 0;
			if (buttonNum[0] >= 1) buttonNum[0] = 1;
			if (buttonNum[0] == 0) pinPos[0] = VGet((WND_W / 2) - 105, WND_H - 205, 0);
			if (buttonNum[0] == 1) pinPos[0] = VGet((WND_W / 2) - 105, WND_H - 305, 0);
		}
		if (time >=0) {
			time--;
		}
		if (time < 0)time = 0;
		if (isMenu) {
			if (time == 0) {
				for (int i = 0; i < 2; i++) {
					if (input[i].Buttons[2] > 1 || input[i].Buttons[3] > 1 || GetMouseInput() & MOUSE_INPUT_LEFT || CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || CheckHitKey(KEY_INPUT_LSHIFT)) {
						isMenu = false;
						time = 30;
						se[4]->SE_Play();

					}
				}
			}
		}
		break;
	case Mode::SETTING:

		if (!isChange[0]) {
			if (CheckHitKey(KEY_INPUT_A) || input[0].X < -1) {
				if (right[0] == 0) {
					buttonNum[0]--;
					if (buttonNum[0] == buttonNum[1]) {
						if (buttonNum[0] != 6 || buttonNum[1] != 0) buttonNum[0]--;
						if (buttonNum[1] == 0) buttonNum[0] = 1;
					}
					se[0]->SE_Play();
					if (right[0] <= 20) right[0]++;
				}
			}
			else if (CheckHitKey(KEY_INPUT_D) || input[0].X > 1) {
				if (right[0] == 0) {
					buttonNum[0]++;
					if (buttonNum[0] == buttonNum[1] && buttonNum[0] != 6) buttonNum[0]++;
					se[0]->SE_Play();
					if (right[0] <= 20) right[0]++;
				}
			}
			else {
				right[0] = 0;
			}
			if (CheckHitKey(KEY_INPUT_W) || input[0].Y < -1) {
				if (up[0] == 0) {
					buttonNum[0] -= 3;
					if (buttonNum[0] == buttonNum[1]) {
						if (buttonNum[0] != 6 || buttonNum[1] != 0) buttonNum[0] += 3;
						if (buttonNum[1] == 0) buttonNum[0] = 1;
					}
					se[0]->SE_Play();
					if (up[0] <= 20) up[0]++;
				}
			}
			else if (CheckHitKey(KEY_INPUT_S) || input[0].Y > 1) {
				if (up[0] == 0) {
					buttonNum[0] += 3;
					if (buttonNum[0] == buttonNum[1] && buttonNum[0] != 6) buttonNum[0] -= 3;
					se[0]->SE_Play();
					if (up[0] <= 20) up[0]++;
				}
			}
			else {
				up[0] = 0;
			}
		}
		if (!isChange[1]) {
			if (CheckHitKey(KEY_INPUT_LEFT) || input[1].X < -1) {
				if (right[1] == 0) {
					buttonNum[1]--;
					if (buttonNum[0] == buttonNum[1]) {
						if (buttonNum[1] != 6 || buttonNum[0] != 0) buttonNum[1]--;
						if (buttonNum[0] == 0) buttonNum[1] = 1;
					}
					se[0]->SE_Play();
					if (right[1] <= 20) right[1]++;
				}
			}
			else if (CheckHitKey(KEY_INPUT_RIGHT) || input[1].X > 1) {
				if (right[1] == 0) {
					buttonNum[1]++;
					if (buttonNum[0] == buttonNum[1] && buttonNum[1] != 6) buttonNum[1]++;
					se[0]->SE_Play();
					if (right[1] <= 20) right[1]++;
				}
			}
			else {
				right[1] = 0;
			}
			if (CheckHitKey(KEY_INPUT_UP) || input[1].Y < -1) {
				if (up[1] == 0) {
					buttonNum[1] -= 3;
					if (buttonNum[0] == buttonNum[1]) {
						if (buttonNum[1] != 6 || buttonNum[0] == 0) buttonNum[1] += 3;
						if (buttonNum[0] == 0) buttonNum[1] = 1;
					}
					se[0]->SE_Play();
					if (up[1] <= 20) up[1]++;
				}
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) || input[1].Y > 1) {
				if (up[1] == 0) {
					buttonNum[1] += 3;
					if (buttonNum[0] == buttonNum[1] && buttonNum[1] != 6) buttonNum[1] -= 3;
					se[0]->SE_Play();
					if (up[1] <= 20) up[1]++;
				}
			}
			else {
				up[1] = 0;
			}
		}
		for (int i = 0; i < PLAYER_NUM; i++){
			if (isChange[i]) {
				if (color[i] == 0) car[i]->loadModel("model/car/car.mqo");
				if (color[i] == 1) car[i]->loadModel("model/car/car (1).mqo");
				if (color[i] == 2) car[i]->loadModel("model/car/car (2).mqo");
				if (color[i] == 3) car[i]->loadModel("model/car/car (3).mqo");
				if (color[i] == 4) car[i]->loadModel("model/car/car (4).mqo");
				if (color[i] == 5) car[i]->loadModel("model/car/car (5).mqo");
			}
			if (buttonNum[i] <= 0) buttonNum[i] = 0;
			if (buttonNum[i] >= 6) buttonNum[i] = 6;

			if (buttonNum[i] == 0) pinPos[i] = VGet(15, 65, 0);
			if (buttonNum[i] == 1) pinPos[i] = VGet(225, 65, 0);
			if (buttonNum[i] == 2) pinPos[i] = VGet(435, 65, 0);
			if (buttonNum[i] == 3) pinPos[i] = VGet(15, 155, 0);
			if (buttonNum[i] == 4) pinPos[i] = VGet(225, 155, 0);
			if (buttonNum[i] == 5) pinPos[i] = VGet(435, 155, 0);
			if (buttonNum[i] == 6) pinPos[i] = VGet(905, 455, 0);
			if (buttonNum[i] == 7) pinPos[i] = VGet(905, 65, 0);
		}
		break;
	case Mode::PLAY:
		if(time < 80)time += 0.12f;//�J�E���g�_�E���ݒ�
		if(time>=15&&time<=25) se[2]->SE_Play();
		if(time>=30&&time<=40) se[2]->SE_Play();
		if(time>=45&&time<=55) se[2]->SE_Play();
		if(time>=60&&time<=70) se[3]->SE_Play();

		objRot.y+=0.01;//�A�C�e������]������
		for (int i = 0; i < 4; i++) {
			if (bomPos[i].y == -20) {
				btime[i]++;
			}
			if (btime[i] == 500) {
				bomPos[i].y = 0;
				btime[i] = 0;
			}
		}
		for (int i = 0; i < COLOR_NUM; i++) {//���ʐݒ�
			if (!isGoal[i]){
				uiPos[i].x = WND_W / 2 - (300 - 25 * check[i]) + 200 * track[i] - distance[i] / 50;//���UI�v���C���[�̈ړ�
			}
		}
		// ������: sortedIndices �� 0 ���� 5 ���i�[
		for (int i = 0; i < COLOR_NUM; ++i) {
			sortedIndices[i] = i;
		}
		// �o�u���\�[�g���g���ăC���f�b�N�X���\�[�g
		for (int i = 0; i < COLOR_NUM - 1; ++i) {
			for (int j = 0; j < COLOR_NUM - i - 1; ++j) {
				if (track[sortedIndices[j]] < track[sortedIndices[j + 1]]) {// �C���f�b�N�X�����ւ�track�`�F�b�N��ʂ������������ق���1
					int temp = sortedIndices[j];
					sortedIndices[j] = sortedIndices[j + 1];
					sortedIndices[j + 1] = temp;
				}
				if (track[sortedIndices[j]] == track[sortedIndices[j + 1]]) {
					if (check[sortedIndices[j]] < check[sortedIndices[j + 1]]) {// �C���f�b�N�X�����ւ�check�`�F�b�N��ʂ������������ق���1
						int temp = sortedIndices[j];
						sortedIndices[j] = sortedIndices[j + 1];
						sortedIndices[j + 1] = temp;
					}
					if (check[sortedIndices[j]] == check[sortedIndices[j + 1]]) {
						if (distance[sortedIndices[j]] > distance[sortedIndices[j + 1]]) {// �C���f�b�N�X�����ւ�distance�̋������Z�������P
							int temp = sortedIndices[j];
							sortedIndices[j] = sortedIndices[j + 1];
							sortedIndices[j + 1] = temp;
						}
					}
				}
			}
		}
		// rank �z��ɏ��ʂ�����U��
		for (int i = 0; i < COLOR_NUM; ++i) rank[sortedIndices[i]] = i; // �\�[�g���ꂽ�C���f�b�N�X�̏��ʂ����̃C���f�b�N�X�Ɋi�[
		for (int i = 0; i < COLOR_NUM; ++i) {
			if (!isGoal[0] || !isGoal[1]) {//�v���C���[�������S�[�����Ă��Ȃ�
				if (track[i] >= GOAL_TRACK) {
					if (!isGoal[i]) {
						point[i] += 15 - rank[i] * 3;
						isGoal[i] = true;
					}
				}
			}
			else {
				if (!isGoal[i]) {//�v���C���[�������S�[��������G���I��点��
					point[i] += 15 - rank[i] * 3;
					isGoal[i] = true;
				}
			}
		}
		break;
	case Mode::FIN:
		orot.y+=0.01;
		// ������: sortedIndices �� 0 ���� 5 ���i�[
		for (int i = 0; i < COLOR_NUM; ++i) sortedIndices[i] = i;
		// �o�u���\�[�g���g���ăC���f�b�N�X���\�[�g
		for (int i = 0; i < COLOR_NUM - 1; ++i) {
			for (int j = 0; j < COLOR_NUM - i - 1; ++j) {
				if (point[sortedIndices[j]] < point[sortedIndices[j + 1]]) {// �C���f�b�N�X�����ւ�point�����������P
					int temp = sortedIndices[j];
					sortedIndices[j] = sortedIndices[j + 1];
					sortedIndices[j + 1] = temp;
				}
			}
		}
		// rank �z��ɏ��ʂ�����U��
		for (int i = 0; i < COLOR_NUM; ++i) {
			rank[sortedIndices[i]] = i; // �\�[�g���ꂽ�C���f�b�N�X�̏��ʂ����̃C���f�b�N�X�Ɋi�[
		}
		break;
	}
}
void Stage::show() {
	switch (mode)
	{
	case Mode::TITLE:
		showModel(VGet(0, 0, 0));
		title->showImage(VGet(WND_W / 2-200, 50, 0));
		for (int i = 0; i < 2; i++) Bottun[i]->showImage(bPos[i]);
		pin[0]->showImage(pinPos[0]);
		for (int i = 0; i < 2; i++) {
			car[i]->Rotation(rot[i]);
			car[i]->showModel(pos[i]);
		}
		if(isMenu)menu->showImage(VGet(WND_W / 2 - 350, 50, 0));
		break;
	case Mode::SETTING:
		showModel(VGet(0, 0, 0));

		for (int i = 0; i < 2; i++) {
			car[i]->Rotation(rot[i]);
			car[i]->showModel(pos[i]);
			pin[i]->showImage(pinPos[i]);
		}
		if(isChange[0]&&isChange[1]) pin[0]->showImage(VGet(905, 65, 0));
		for (int i = 0; i < 8; i++) Bottun[i]->showImage(bPos[i]);
		if(isChange[0])ok[0]->showImage(VGet(340, 450, 0));
		if(isChange[1])ok[1]->showImage(VGet(780, 450, 0));
		break;
	case Mode::PLAY:
		showModel(VGet(0, 0, 0));
		course->showImage(VGet(WND_W / 2-300, 35, 0));
		for (int i = 0; i < COLOR_NUM; i++) ui[i]->showImage(uiPos[i]);
		if ((20<time)&&(time<30)) {
			count[0]->showImage(VGet(WND_W / 4, 200, 0));
			count[0]->showImage(VGet(WND_W - WND_W / 4, 200, 0));
		}
		if ((35<time)&&(time<45)) {
			count[1]->showImage(VGet(WND_W / 4, 200, 0));
			count[1]->showImage(VGet(WND_W - WND_W / 4, 200, 0));
		}
		if ((50<time)&&(time<60)) {
			count[2]->showImage(VGet(WND_W / 4, 200, 0));
			count[2]->showImage(VGet(WND_W - WND_W / 4, 200, 0));
		}
		if ((65<time)&&(time<75)) {
			count[3]->showImage(VGet(200, 200, 0));
			count[3]->showImage(VGet(850, 200, 0));
		}

		for (int i = 0; i < 6;i++) dash->showModel(dashPos[i]);
		dash->Rotation(objRot);
		for (int i = 0; i < 4;i++) bom->showModel(bomPos[i]);
		bom->Rotation(objRot);
		if (isGoal[0] && isGoal[1]) rankbord[0]->showImage(VGet(WND_W / 2 - 100, 200, 0));
		for (int i = 0; i < COLOR_NUM; i++) {
			if (isGoal[0] && isGoal[1]) ui[rank[i]]->showImage(VGet(WND_W / 2 - 10, 230 + (i * 45), 0));
		}
		if (isGoal[0])goal->showImage(VGet(200, 200, 0));
		if (isGoal[1])goal->showImage(VGet(850, 200, 0));
		rankui[rank[0]]->showImage(VGet(20, WND_H - 50, 0));
		rankui[rank[1]]->showImage(VGet(620, WND_H - 50, 0));
		SetFontSize(40);
		DrawFormatString(450, WND_H - 50, GetColor(255, 255, 255), "Lap %d/%d", track[0], GOAL_TRACK);
		DrawFormatString(1050, WND_H - 50, GetColor(255, 255, 255), "Lap %d/%d", track[1], GOAL_TRACK);
		break;
	case Mode::FIN:
		showModel(VGet(0, 0, 0));
		for (int i = 0; i < COLOR_NUM; i++) {
			if (rank[i] == 0) {
				car[i]->Rotation(rot[i]);
				car[i]->showModel(VGet(MAP_MAX_X - 190, 0, -360));
			}
			if (rank[i] == 1) {
				car[i]->Rotation(VGet(0, ToRadian(220), 0));
				car[i]->showModel(VGet(MAP_MAX_X - 220, 0, -350));
			}
			if (rank[i] == 2) {
				car[i]->Rotation(VGet(0, ToRadian(140), 0));
				car[i]->showModel(VGet(MAP_MAX_X - 160, 0, -350));
			}
		}
		rankbord[1]->showImage(VGet(40, 70, 0));
		for (int i = 0; i < COLOR_NUM; i++) {
			ui[rank[i]]->showImage(VGet(100, 100 + (i * 45), 0));
			DrawFormatString(160, 100 + (i * 45), GetColor(255, 255, 255), "%d", point[i]);\
		}
		oukan->showModel(VGet(MAP_MAX_X - 190, 15, -360));
		oukan->Rotation(orot);
		oukan->setScale(2);
		Bottun[7]->showImage(VGet(910, 70, 0));
		pin[0]->showImage(VGet(905, 65, 0));

		break;
	}
}