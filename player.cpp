#include"player.h"
Player::Player() {
	//�T�E���h
	for (int i = 0; i < 2; i++) se[i] = new Sound;
	se[0]->loadSound("sound/�S�[��.mp3");
	se[1]->loadSound("sound/�X���b�v.mp3");
	for (int i = 0; i < PLAYER_NUM; i++) {
		player[i] = new Model;
		color[i] = 0;
		////�ړ��p
		oldpos[i] = pos[i] = VGet(0, 0, 0);
		//�v���C���[�̓����蔻��
		topPos[i] = bootPos[i] = lookPos[i] = VGet(0, 0, 0);
		for (int n = 0;n < 2;n++)rightPos[i][n];
	}
}

void Player::init() {
	for (int i = 0; i < PLAYER_NUM; i++) {
		//�ړ��p
		rot[i] = VGet(0, ToRadian(180), 0);
		speed[i] = angle[i] = 0;
		isMove[i] = isDef[i] = isSlip[i] = isGoal[i] = false;
		//�A�C�e���p
		item[i] = 0;//�A�C�e���ԍ� 0�F�Ȃ��@1�F�_�b�V���@�Q�F�L�����f�B�[�@3�F�X�e�B�b�N �S�F�{��
		time[i] = 0;
		for (int n = 0; n < 3; n++) isDash[i] = isCandy[i][n] = isStick[i] = isBom[i] = isBom2[i] = false;//�A�C�e�����g���Ă���=true
		candy[i] = 0;
		//����p
		check[i] = track[i] = rank[i] = 0;
		distanceVec[i] = VGet(0, 0, 0);
		distance[i] = 0;
	}
}
void Player::load() {//�F�ɉ������Ԃ�ǂݍ���
	for (int i = 0; i < PLAYER_NUM; i++) {
		if (color[i] == 0) player[i]->loadModel("model/car/car.mqo");
		if (color[i] == 1) player[i]->loadModel("model/car/car (1).mqo");
		if (color[i] == 2) player[i]->loadModel("model/car/car (2).mqo");
		if (color[i] == 3) player[i]->loadModel("model/car/car (3).mqo");
		if (color[i] == 4) player[i]->loadModel("model/car/car (4).mqo");
		if (color[i] == 5) player[i]->loadModel("model/car/car (5).mqo");
	}
}

void Player::ctrl() {
	//�v���C���[�P
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input[0]);
	if (isMove[0]) {
		//�ړ��ݒ�(W�F�i�ށ@S�F�o�b�N A D:���E)
		if (CheckHitKey(KEY_INPUT_W) || input[0].Buttons[2]>1 || input[0].Buttons[3]>1) {
			if (speed[0] < speedMax[color[0]])speed[0]+= speedUp[color[0]];
			pos[0].x -= sinf(rot[0].y) * (speed[0]);
			pos[0].z -= cosf(rot[0].y) * (speed[0]);
			if (speed[0] > speedMax[color[0]])speed[0] -= speedUp[color[0]];
		}
		else {
			if (speed[0] > 0)speed[0] -= speedUp[color[0]];
			pos[0].x -= sinf(rot[0].y) * (speed[0]);
			pos[0].z -= cosf(rot[0].y) * (speed[0]);
		}
		if (CheckHitKey(KEY_INPUT_S) || input[0].Buttons[0] > 1 || input[0].Buttons[1] > 1) {
			if (speed[0] > -0.1)speed[0] -= speedUp[color[0]];
		}
		else {
			if (speed[0] <= 0)speed[0] += speedUp[color[0]];
		}
		if (CheckHitKey(KEY_INPUT_A) || input[0].X<-1) {
			rot[0].y -= rotUp[color[0]];
			if (angle[0] < 1.2) angle[0] += 0.002;
		}
		else if (CheckHitKey(KEY_INPUT_D) || input[0].X>1) {
			rot[0].y += rotUp[color[0]];
			if (angle[0] > -1.2)angle[0] -= 0.002;
		}
		else {
			if (angle[0] > 0) angle[0] -= 0.01;
			if (angle[0] < 0) angle[0] += 0.01;
		}
		//�A�C�e���ݒ�(�V�t�g�F�g��)
		if (CheckHitKey(KEY_INPUT_LSHIFT) || input[0].Buttons[6] > 1 || input[0].Buttons[7] > 1) {
			if (item[0] == 1) {
				if (!isDash[0]) {
					item[0] = 0;
					isDash[0] = true;
					time[0] = 200;
				}
			}
			if (item[0] == 2) {
				time[0]--;
				if (time[0] <= 0) {
					candy[0]--;
					isCandy[0][candy[0]] = true;
					time[0] = SHOT_INTERVAL;
					if (candy[0] <= 0) item[0] = 0;
				}
			}
			if (item[0] == 3) {
				if (!isStick[0]) {
					isStick[0] = true;
					time[0] = 300;
				}
			}
			if (item[0] == 4) {
				if (CheckHitKey(KEY_INPUT_W) || input[0].Buttons[2] > 1 || input[0].Buttons[3] > 1) {
					isBom[0] = isBom2[0] = true;
					item[0] = 0;
				}
				else {
					isBom[0] = true;
					item[0] = 0;
				}
			}
		}
		else {
			if (item[0] == 2) time[0] = 0;
		}
	}
	//�v���C���[�Q
	GetJoypadDirectInputState(DX_INPUT_PAD2, &input[1]);
	if (isMove[1]) {
		//�ړ��ݒ�(���F�i�ށ@���F�o�b�N ����:���E)
		if (CheckHitKey(KEY_INPUT_UP) || input[1].Buttons[2] > 1 || input[1].Buttons[3] > 1) {
			if (speed[1] < speedMax[color[1]])speed[1] += speedUp[color[1]];
			pos[1].x -= sinf(rot[1].y) * (speed[1]);
			pos[1].z -= cosf(rot[1].y) * (speed[1]);
			if (speed[1] > speedMax[color[1]])speed[1] -= speedUp[color[1]];
		}
		else {
			if (speed[1] > 0)speed[1] -= speedUp[color[1]];
			pos[1].x -= sinf(rot[1].y) * (speed[1]);
			pos[1].z -= cosf(rot[1].y) * (speed[1]);
		}
		if (CheckHitKey(KEY_INPUT_DOWN) || input[1].Buttons[0] > 1 || input[1].Buttons[1] > 1) {
			if (speed[1] > -0.1)speed[1] -= speedUp[color[1]];
		}
		else {
			if (speed[1] <= 0)speed[1] += speedUp[color[1]];
		}
		if (CheckHitKey(KEY_INPUT_LEFT) || input[1].X < -1) {
			rot[1].y -= rotUp[color[1]];
			if (angle[1] < 1.2) angle[1] += 0.002;
		}
		else if (CheckHitKey(KEY_INPUT_RIGHT) || input[1].X > 1) {
			rot[1].y += rotUp[color[1]];
			if (angle[1] > -1.2)angle[1] -= 0.002;
		}
		else {
			if (angle[1] > 0) angle[1] -= 0.01;
			if (angle[1] < 0) angle[1] += 0.01;
		}
		if (CheckHitKey(KEY_INPUT_RSHIFT) || input[1].Buttons[6] > 1 || input[1].Buttons[7] > 1) {
			if (item[1] == 1) {
				if (!isDash[1]) {
					item[1] = 0;
					isDash[1] = true;
					time[1] = 200;
				}
			}
			if (item[1] == 2) {
				time[1]--;
				if (time[1] <= 0) {
					candy[1]--;
					isCandy[1][candy[1]] = true;
					time[1] = SHOT_INTERVAL;
				}
				if (candy[1] <= 0) item[1] = 0;
			}
			if (item[1] == 3) {
				if (!isStick[1]) {
					isStick[1] = true;
					time[1] = 400;
				}
			}
			if (item[1] == 4) {
				if (CheckHitKey(KEY_INPUT_UP) || input[1].Buttons[2] > 1 || input[1].Buttons[3] > 1) {
					isBom[1] = isBom2[1] = true;
					item[1] = 0;
				}
				else {
					isBom[1] = true;
					item[1] = 0;
				}
			}
		}
		else {
			if (item[1] == 2) time[1] = 0;
		}
	}
	for (int i = 0;i < PLAYER_NUM;i++) {
		oldpos[i] = pos[i];
		//�v���C���[�̑O�㓖���蔻��
		MATRIX mat;
		mat = MGetRotY(rot[i].y);				//Y����]�s��̍쐬
		VECTOR axisZ = VGet(0, 0, 1.0f);	//���޸��
		axisZ = VTransform(axisZ, mat);	//�������޸�ق����߂�
		VECTOR dis[PLAYER_NUM][2];
		//���
		bootPos[i] = pos[i];
		dis[i][0] = VScale(axisZ, 5.0f);	//��׋���
		bootPos[i] = VAdd(bootPos[i], dis[i][0]);	//��׈ʒu
		//�O
		topPos[i] = pos[i];
		dis[i][1] = VScale(axisZ, -3.2f);	//��׋���
		topPos[i] = VAdd(topPos[i], dis[i][1]);	//��׈ʒu
		//���E
		VECTOR dis2[PLAYER_NUM][2];
		VECTOR axisZ2[PLAYER_NUM];
		axisZ2[0] = VGet(0.3f, 0, 1.5f);	//���޸�ف@�E0.5�@�O1.5
		axisZ2[1] = VGet(-0.3f, 0, 1.5f);	//���޸�ف@��0.5�@�O1.5
		for (int n = 0;n < 2;n++) {
			axisZ2[n] = VTransform(axisZ2[n], mat);	//�������޸�ق����߂�
			rightPos[i][n] = pos[i];
			dis2[i][n] = VScale(axisZ2[n], -3.2f);	//��׋���
			rightPos[i][n] = VAdd(rightPos[i][n], dis2[i][n]);	//��׈ʒu
		}
		//�ڐ���
		lookPos[i] = pos[i];
		VECTOR axisZ3[PLAYER_NUM];
		VECTOR dis3[PLAYER_NUM];
		axisZ3[0] = VGet(10, 0, 60.0f);	//���޸��
		axisZ3[1] = VGet(-10, 0, 60.0f);	//���޸��
		axisZ3[i] = VTransform(axisZ3[i], mat);	//�������޸�ق����߂�
		dis3[i] = VScale(axisZ3[i], -1.0f);	//��׋���
		lookPos[i] = VAdd(lookPos[i], dis3[i]);	//��׈ʒu
		//�R�[�i�[�ݒ�
		if (isDef[i]) {
			if (speed[i] > speedDef[i]) speed[i] -= 0.1f;
		}
		//�X���b�v�ݒ�
		if (isSlip[i]) {
			isMove[i] = false;
			angle[i] += 0.1;
			if (speed[i] > 0)speed[i] -= 0.1f;
			if (angle[i] >= ToRadian(720)) {
				angle[i] = 0;
				isSlip[i] = false;
				isMove[i] = true;
			}
		}
		//�_�b�V���ݒ�
		if (isDash[i]) {
			speed[i] = 2.5;
			time[i]--;
			if (time[i] <= 0) {
				speed[i] = speedMax[color[i]];
				isDash[i] = false;
			}
		}
		//�X�e�B�b�N�ݒ�
		if (isStick[i]) {
			time[i]--;
			if (time[i] <= 0) {
				item[i] = 0;
				isStick[i] = false;
			}
		}
		//�S�[���ݒ�
		if (track[i] >= GOAL_TRACK) {
			isGoal[i] = true;
			isMove[i] = false;
			se[0]->SE_Play();
		}
		if (isGoal[i]) {
			if (speed[i] < speedMax[color[i]])speed[i] += speedUp[i];
			pos[i].x -= sinf(rot[i].y) * (speed[i]);
			pos[i].z -= cosf(rot[i].y) * (speed[i]);
		}
	}
}

void Player::draw() {
	for (int i = 0;i < PLAYER_NUM;i++) {
		player[i]->Rotation(VGet(rot[i].x, rot[i].y - angle[i], rot[i].x));
		player[i]->showModel(pos[i]);
	}
}