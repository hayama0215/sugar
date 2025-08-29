#include"enemy.h"
Enemy::Enemy() {
	for (int i = 0;i < ENEMY_NUM;i++) {
		enemy[i] = new Model;
		color[i] = 0;
		//移動用
		oldpos[i] = pos[i] = VGet(0, 0, 0);
		//敵の当たり判定
		topPos[i] = bootPos[i] = VGet(0, 0, 0);
		for (int n = 0;n < 2;n++)rightPos[i][n];
	}
}
void Enemy::init() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		//移動用
		rot[i] = VGet(0, ToRadian(180), 0);
		speed[i] = angle[i] = 0;
		isMove[i] = isDef[i] = isSlip[i] = isGoal[i] = false;
		//アイテム用
		item[i] = 0;//アイテム番号 0：なし　1：ダッシュ　２：キャンディー　3：スティック ４：ボム
		time[i] = rtime[i] = 0;
		for (int n = 0;n < 3;n++) isDash[i] = isCandy[i][n] = isStick[i] = isBom[i] = isBom2[i] = false;//アイテムを使っている=true
		candy[i] = 0;
		//周回用
		check[i] = track[i] = rank[i] = 0;
		distanceVec[i] = VGet(0, 0, 0);
		distance[i] = 0;
	}
}
void Enemy::load() {//色に応じた車を読み込む
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

			if (item[i] == 1) {//ダッシュ設定
				time[i]--;
				if (time[i] <= 0) {
					if (!isDash[i]) {
						item[i] = 0;
						isDash[i] = true;
						time[i] = 200;
					}
				}
			}
			if (item[i] == 2) {//キャンディー設定
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
		//コーナー設定
		if (isDef[i]) {
			if (speed[i] > speedDef[color[i]]) speed[i] -= 0.1f;
		}
		//ダッシュ設定
		if (isDash[i]) {
			speed[i] = 2.5;
			time[i]--;
			if (time[i] <= 0) {
				speed[i] = speedMax[color[i]];
				isDash[i] = false;
			}
		}//スリップ設定
		if (isSlip[i]) {
			isMove[i] = false;
			angle[i] += 0.1;
			if (speed[i] > 0)speed[i] -= 0.1f;
			if (angle[i] >= ToRadian(720)) {
				angle[i] = 0;
				isSlip[i] = false;
				isMove[i] = true;
			}
		}//スティック設定
		if (isStick[i]) {
			time[i]--;
			if (time[i] <= 0) {
				item[i] = 0;
				isStick[i] = false;
			}
		}
		//ゴール設定
		if (track[i] == GOAL_TRACK) {
			isGoal[i] = true;
			isMove[i] = false;
		}
		if (isGoal[i]) {
			if (speed[i] < speedMax[color[i]])speed[i] += speedUp[i];
			pos[i].x -= sinf(rot[i].y) * (speed[i]);
			pos[i].z -= cosf(rot[i].y) * (speed[i]);
		}
		//敵の前後当たり判定
		MATRIX mat;
		mat = MGetRotY(rot[i].y);				//Y軸回転行列の作成
		VECTOR axisZ = VGet(0, 0, 1.0f);	//軸ﾍﾞｸﾄﾙ
		axisZ = VTransform(axisZ, mat);	//向きのﾍﾞｸﾄﾙを求める
		VECTOR dis[ENEMY_NUM][2];
		//後ろ
		bootPos[i] = pos[i];
		dis[i][0] = VScale(axisZ, 5.0f);	//ｶﾒﾗ距離
		bootPos[i] = VAdd(bootPos[i], dis[i][0]);	//ｶﾒﾗ位置
		//前
		topPos[i] = pos[i];
		dis[i][1] = VScale(axisZ, -5.2f);	//ｶﾒﾗ距離
		topPos[i] = VAdd(topPos[i], dis[i][1]);	//ｶﾒﾗ位置
		//左右
		VECTOR dis2[ENEMY_NUM][2];
		VECTOR axisZ2[2];
		axisZ2[0] = VGet(1.2f, 0, 2.0f);	//軸ﾍﾞｸﾄﾙ　右１　前1.6
		axisZ2[1] = VGet(-1.0f, 0, 2.6f);	//軸ﾍﾞｸﾄﾙ　左１　前1.6
		for (int n = 0;n < 2;n++) {
			axisZ2[n] = VTransform(axisZ2[n], mat);	//向きのﾍﾞｸﾄﾙを求める
			rightPos[i][n] = pos[i];
			dis2[i][n] = VScale(axisZ2[n], -3.2f);	//ｶﾒﾗ距離
			rightPos[i][n] = VAdd(rightPos[i][n], dis2[i][n]);	//ｶﾒﾗ位置
		}
		//目線先
		lookPos[i] = pos[i];
		VECTOR axisZ3[ENEMY_NUM];
		VECTOR dis3[ENEMY_NUM];
		axisZ3[0] = VGet(10, 0, 60.0f);	//軸ﾍﾞｸﾄﾙ
		axisZ3[1] = VGet(-10, 0, 60.0f);	//軸ﾍﾞｸﾄﾙ
		axisZ3[2] = VGet(60, 0, 70.0f);	//軸ﾍﾞｸﾄﾙ
		axisZ3[3] = VGet(-60, 0, 70.0f);	//軸ﾍﾞｸﾄﾙ
		axisZ3[i] = VTransform(axisZ3[i], mat);	//向きのﾍﾞｸﾄﾙを求める
		dis3[i] = VScale(axisZ3[i], -1.0f);	//ｶﾒﾗ距離
		lookPos[i] = VAdd(lookPos[i], dis3[i]);	//ｶﾒﾗ位置
	}
}
void Enemy::draw() {
	for (int i = 0;i < ENEMY_NUM;i++) {
		enemy[i]->Rotation(VGet(rot[i].x, rot[i].y - angle[i], rot[i].x));
		enemy[i]->showModel(pos[i]);
	}
}