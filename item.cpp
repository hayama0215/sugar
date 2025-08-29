#include"item.h"
Item::Item() {
	loadModel("model/item.mqo");//�A�C�e����
	for (int i = 0; i < COLOR_NUM; i++) {
		time[i] = 0;
		pos[i] = VGet(0, 0, 0);
	}
	milk = new Model;//�~���N
	milk->loadModel("model/���p�b�N500/���p�b�N1.mqo");
	for (int i = 0; i < 3; i++) candy[i] = new Model;//�L�����f�B�[
	candy[0]->loadModel("model/candy/candyB.pmx");
	candy[1]->loadModel("model/candy/candyR.pmx");
	candy[2]->loadModel("model/candy/candyY.pmx");
	for (int i = 0;i < COLOR_NUM;i++) {
		stick[i] = new Model;//�X�e�B�b�N
		stick[i]->loadModel("model/�X�e�[�W/suginoko_v100/suginoko.mqo");
	}
	bom = new Model;//�{��
	bom->loadModel("model/�X�e�[�W (3)/bom.mqo");
}
void Item::init() {
	for (int i = 0; i < COLOR_NUM; i++) {
		milkpos[i] = VGet(0, -100, 0);
		for (int n = 0; n < 3; n++) {
			candypos[i][n] = VGet(0, -100, 0);
			candyrot[i][n] = VGet(0, 0, 0);
			isCandy[i][n] = false;
		}
		stickpos[i] = stickcenterpos[i] = VGet(0, -100, 0);
		stickrot[i] = VGet(0, 0, 0);
		isStick[i] = false;
		bompos[i] = VGet(0, -100, 0);
		bomrot[i] = VGet(0,0 , 0);
		isBom[i] = isBom2[i] = false;
		bomSpeed[i] = 5;
		bomUpSpeed[i] = 0.5;
	}
}
void Item::ctrl() {
	rot.y += 0.02f;
	for (int i = 0; i < ITEM_MAX; i++) {
		if (pos[i].y == -20) {
			time[i]++;
		}
		if (time[i] == ITEM_lINTERVAL) {
			pos[i].y = 10;
			time[i] = 0;
		}
	}
	for (int i = 0; i < COLOR_NUM; i++) {
		for (int n = 0; n < 3; n++) {//�L�����f�B�[
			if (!isCandy[i][n]) {
				MATRIX mat;
				mat = MGetRotY(rot.y+(ToRadian(120)*n));				//Y����]�s��̍쐬
				VECTOR axisZ = VGet(0, 0, 1.0f);	//���޸��
				axisZ = VTransform(axisZ, mat);	//�������޸�ق����߂�
				VECTOR dis;
				dis = VScale(axisZ, 10.0f);
				candypos[i][n] = VAdd(candypos[i][n], dis);
			}
			if (isCandy[i][n]) {
				candypos[i][n].x -= sinf(candyrot[i][n].y) * (SHOT_SPEED);
				candypos[i][n].z -= cosf(candyrot[i][n].y) * (SHOT_SPEED);
			}
			if (candypos[i][n].x > MAP_MAX_X || candypos[i][n].z > MAP_MAX_Z || candypos[i][n].x < -MAP_MAX_X || candypos[i][n].z < -MAP_MAX_Z) {
				candypos[i][n] = VGet(0, -100, 0);
			}
		}
		if (isStick[i]) {
			stickrot[i].y += 0.16f;
			stickrot[i].x = ToRadian(90);
			stickpos[i].y = 5;
			MATRIX mat;
			mat = MGetRotY(stickrot[i].y);				//Y����]�s��̍쐬
			VECTOR axisZ = VGet(0, 0, 1.0f);	//���޸��
			axisZ = VTransform(axisZ, mat);	//�������޸�ق����߂�
			VECTOR dis2[2];
			dis2[0] = VScale(axisZ, 7.0f);
			stickpos[i] = VAdd(stickpos[i], dis2[0]);
			stickcenterpos[i] = stickpos[i];
			dis2[1] = VScale(axisZ, 12.0f);
			stickcenterpos[i] = VAdd(stickcenterpos[i], dis2[1]);
		}
		else {
			stickrot[i].y += 0.03f;
			stickrot[i].x = 0;
		}
		if (isBom2[i]) {
			if(bomSpeed[i]>0)bomSpeed[i] -= 0.01f;
			bomUpSpeed[i] -= 0.02f;
			bompos[i].x -= sinf(bomrot[i].y) * (bomSpeed[i]);
			bompos[i].z -= cosf(bomrot[i].y) * (bomSpeed[i]);
			bompos[i].y += bomUpSpeed[i];
		}
	}

}

void Item::draw() {
	Rotation(rot);
	for (int i = 0; i < ITEM_MAX; i++)showModel(pos[i]);
	for (int i = 0; i < COLOR_NUM; i++) {
		milk->showModel(milkpos[i]);
		milk->Rotation(rot);
		for (int n = 0; n < 3; n++) {
			candy[n]->showModel(candypos[i][n]);
			candy[n]->Rotation(rot);
			candy[n]->setScale(2);
		}

		stick[i]->showModel(stickpos[i]);
		stick[i]->Rotation(stickrot[i]);

		bom->showModel(bompos[i]);
	}
}