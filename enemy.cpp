#include"enemy.h"
Enemy::Enemy() {
	for (int i = 0;i < ENEMY_NUM;i++) {
		enemy[i] = new Model;
		color[i] = 0;
		//�ړ��p
		oldpos[i] = pos[i] = VGet(0, 0, 0);
		//�G�̓����蔻��
		topPos[i] = bootPos[i] = VGet(0, 0, 0);
		for (int n = 0;n < 2;n++)rightPos[i][n];
	}
}
void Enemy::init() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		//�ړ��p
		rot[i] = VGet(0, ToRadian(180), 0);
		speed[i] = angle[i] = 0;
		isMove[i] = isDef[i] = isSlip[i] = isGoal[i] = false;
		//�A�C�e���p
		item[i] = 0;//�A�C�e���ԍ� 0�F�Ȃ��@1�F�_�b�V���@�Q�F�L�����f�B�[�@3�F�X�e�B�b�N �S�F�{��
		time[i] = rtime[i] = 0;
		for (int n = 0;n < 3;n++) isDash[i] = isCandy[i][n] = isStick[i] = isBom[i] = isBom2[i] = false;//�A�C�e�����g���Ă���=true
		candy[i] = 0;
		//����p
		check[i] = track[i] = rank[i] = 0;
		distanceVec[i] = VGet(0, 0, 0);
		distance[i] = 0;
	}
}
void Enemy::load() {//�F�ɉ������Ԃ�ǂݍ���
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (color[i] == 0) {
			enemy[i]->loadModel("model/car/car.mqo");
		}if (color[i] == 1) {
			enemy[i]->loadModel("model/car/car (1).mqo");
		}if (color[i] == 2) {
			enemy[i]->loadModel("model/car/car (2).mqo");
		}if (color[i] == 3) {
			enemy[i]->loadModel("model/car/car (3).mqo");
		}if (color[i] == 4) {
			enemy[i]->loadModel("model/car/car (4).mqo");
		}if (color[i] == 5) {
			enemy[i]->loadModel("model/car/car (5).mqo");
		}
	}
}
void Enemy::ctrl() {
	for (int i = 0;i < ENEMY_NUM;i++) {
		oldpos[i] = pos[i];
		if (isMove[i]) {
			rtime[i]--;
			if (rtime[i] <= 0) {
				rot[i].y += GetRand(3) * 0.02 - GetRand(3) * 0.02;
				rtime[i] = 200;
			}
			if (speed[i] < speedMax[color[i]])speed[i] += speedUp[color[i]];
			pos[i].x -= sinf(rot[i].y) * (speed[i]);
			pos[i].z -= cosf(rot[i].y) * (speed[i]);
			if (speed[i] > speedMax[color[i]])speed[i] -= speedUp[color[i]];

			if (item[i] == 1) {//�_�b�V���ݒ�
				time[i]--;
				if (time[i] <= 0) {
					if (!isDash[i]) {
						item[i] = 0;
						isDash[i] = true;
						time[i] = 200;
					}
				}
			}
			if (item[i] == 2) {//�L�����f�B�[�ݒ�
				time[i]--;
				if (time[i] <= 0) {
					candy[i]--;
					isCandy[i][candy[i]] = true;
					time[i] = SHOT_INTERVAL + (GetRand(4) * 200);
				}
				if (candy[i] <= 0) {
					item[i] = 0;
				}
			}
			if (item[i] == 3) {
				time[i]--;
				if (time[i] <= 0) {
					if (!isStick[i]) {
						isStick[i] = true;
						time[i] = 400;
					}
				}
			}
			if (item[i] == 4) {
				time[i]--;
				if (time[i] <= 0) {
					isBom[i] = true;
					item[i] = 0;
				}
			}
		}
		//�R�[�i�[�ݒ�
		if (isDef[i]) {
			if (speed[i] > speedDef[color[i]]) speed[i] -= 0.1f;
		}
		//�_�b�V���ݒ�
		if (isDash[i]) {
			speed[i] = 2.5;
			time[i]--;
			if (time[i] <= 0) {
				speed[i] = speedMax[color[i]];
				isDash[i] = false;
			}
		}//�X���b�v�ݒ�
		if (isSlip[i]) {
			isMove[i] = false;
			angle[i] += 0.1;
			if (speed[i] > 0)speed[i] -= 0.1f;
			if (angle[i] >= ToRadian(720)) {
				angle[i] = 0;
				isSlip[i] = false;
				isMove[i] = true;
			}
		}//�X�e�B�b�N�ݒ�
		if (isStick[i]) {
			time[i]--;
			if (time[i] <= 0) {
				item[i] = 0;
				isStick[i] = false;
			}
		}
		//�S�[���ݒ�
		if (track[i] == GOAL_TRACK) {
			isGoal[i] = true;
			isMove[i] = false;
		}
		if (isGoal[i]) {
			if (speed[i] < speedMax[color[i]])speed[i] += speedUp[i];
			pos[i].x -= sinf(rot[i].y) * (speed[i]);
			pos[i].z -= cosf(rot[i].y) * (speed[i]);
		}
		//�G�̑O�㓖���蔻��
		MATRIX mat;
		mat = MGetRotY(rot[i].y);				//Y����]�s��̍쐬
		VECTOR axisZ = VGet(0, 0, 1.0f);	//���޸��
		axisZ = VTransform(axisZ, mat);	//�������޸�ق����߂�
		VECTOR dis[ENEMY_NUM][2];
		//���
		bootPos[i] = pos[i];
		dis[i][0] = VScale(axisZ, 5.0f);	//��׋���
		bootPos[i] = VAdd(bootPos[i], dis[i][0]);	//��׈ʒu
		//�O
		topPos[i] = pos[i];
		dis[i][1] = VScale(axisZ, -5.2f);	//��׋���
		topPos[i] = VAdd(topPos[i], dis[i][1]);	//��׈ʒu
		//���E
		VECTOR dis2[ENEMY_NUM][2];
		VECTOR axisZ2[2];
		axisZ2[0] = VGet(1.2f, 0, 2.0f);	//���޸�ف@�E�P�@�O1.6
		axisZ2[1] = VGet(-1.0f, 0, 2.6f);	//���޸�ف@���P�@�O1.6
		for (int n = 0;n < 2;n++) {
			axisZ2[n] = VTransform(axisZ2[n], mat);	//�������޸�ق����߂�
			rightPos[i][n] = pos[i];
			dis2[i][n] = VScale(axisZ2[n], -3.2f);	//��׋���
			rightPos[i][n] = VAdd(rightPos[i][n], dis2[i][n]);	//��׈ʒu
		}
		//�ڐ���
		lookPos[i] = pos[i];
		VECTOR axisZ3[ENEMY_NUM];
		VECTOR dis3[ENEMY_NUM];
		axisZ3[0] = VGet(10, 0, 60.0f);	//���޸��
		axisZ3[1] = VGet(-10, 0, 60.0f);	//���޸��
		axisZ3[2] = VGet(60, 0, 70.0f);	//���޸��
		axisZ3[3] = VGet(-60, 0, 70.0f);	//���޸��
		axisZ3[i] = VTransform(axisZ3[i], mat);	//�������޸�ق����߂�
		dis3[i] = VScale(axisZ3[i], -1.0f);	//��׋���
		lookPos[i] = VAdd(lookPos[i], dis3[i]);	//��׈ʒu
	}
}
void Enemy::draw() {
	for (int i = 0;i < ENEMY_NUM;i++) {
		enemy[i]->Rotation(VGet(rot[i].x, rot[i].y - angle[i], rot[i].x));
		enemy[i]->showModel(pos[i]);
	}
}