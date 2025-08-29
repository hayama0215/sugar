#pragma once
#include"model.h"
class Enemy {
public:
	Enemy();//ｺﾝｽﾄﾗｸﾀ
	~Enemy() {};//ﾃﾞｽﾄﾗｸﾀ
	void init();//初期化処理
	void load();//モデル読み込み
	void ctrl();//操作処理
	void draw();//表示処理
	inline VECTOR getPos(int index) {//座標を配列の個別で返す（modelのオーバーロード
		return pos[index];
	}
	inline void initPos(int map) {//マップごとに初期値を変える
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
	inline VECTOR getRotation(int index) {//回転量を配列の個別で返す（modelのオーバーロード
		return rot[index];
	}
	inline void randColor(int c1, int c2) {
		for (int i = 0; i < ENEMY_NUM; ++i) {
			for (int n = 0; n < ENEMY_NUM; ++n) {
				if (color[i] == color[n]||color[i] == c1||color[i] == c2) {//敵の色がかぶっていたらランダムに
					color[i] = GetRand(COLOR_NUM - 1);
				}
			}
		}
	}
	inline int getColor(int index) {
		return color[index];
	}

	inline VECTOR getTopPos(int index) {//先端の座標を返す
		return topPos[index];
	}
	inline VECTOR getbootPos(int index) {//後ろの座標を返す
		return bootPos[index];
	}
	inline VECTOR getRPos(int index, int num) {//左右側の座標を返す
		return rightPos[index][num];
	}
	inline VECTOR getLookPos(int index) {
		return lookPos[index];
	}
	inline void reset(int index) {
		pos[index] = oldpos[index];
	}
	inline void hitTop(int index) {//先端に当たった時の設定
		pos[index] = oldpos[index];
		speed[index] = -speedMax[index] / 5;
		pos[index].x -= sinf(rot[index].y) * (speed[index]);
		pos[index].z -= cosf(rot[index].y) * (speed[index]);
		rot[index].y -= 0.01;
	}
	inline void hitBoot(int index) {//後ろに当たった時の設定
		pos[index] = oldpos[index];
		speed[index] = speedMax[index] / 5;
		pos[index].x -= sinf(rot[index].y) * (speed[index]);
		pos[index].z -= cosf(rot[index].y) * (speed[index]);
	}
	inline void hitR(int index, int num) {//左右に当たった時の設定
		if (num == 0)rot[index].y -= 0.01;
		if (num == 1)rot[index].y += 0.01;
	}
	inline void hitLook(int index, int num) {//左右の視点位置に当たった時の設定
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
	inline void setItem(int index) {//アイテムを手に入れたら
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
	inline bool getisDash(int index) {//ダッシュを使ったら
		return isDash[index];
	}
	inline void setCandy(int index) {//キャンディーを入手したら球を最大数にセットする
		if (candy[index] == 0)candy[index] = 3;
	}
	inline void offisCandy(int index, int num) {//キャンディーを使い切る
		isCandy[index][num] = false;
	}
	inline bool getisCandy(int index, int num) {
		return isCandy[index][num];
	}
	inline bool getisStick(int index) {//スティックを使ったら
		return isStick[index];
	}
	inline void offStick(int index) {
		isStick[index] = false;
	}
	inline bool getisBom(int index) {//ボムを使ったら
		return isBom[index];
	}
	inline void offBom(int index) {
		isBom[index] = false;
	}
	inline bool getisBom2(int index) {//ボムを投げたら
		return isBom2[index];
	}
	inline void offBom2(int index) {
		isBom2[index] = false;
	}
	//周回用
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
	inline void setDistance(int index, VECTOR checkpos) {//チェックポイントとの距離を取る
		distanceVec[index] = VSub(checkpos, pos[index]);
		distance[index] = VSize(distanceVec[index]);
	}
	inline float getDistanse(int index) {//チェックポイントとの距離を渡す
		return distance[index];
	}
	inline bool getisGoal(int index) {
		return isGoal[index];
	}
private:
	Model* enemy[ENEMY_NUM];
	int color[ENEMY_NUM];
	//移動用
	VECTOR oldpos[ENEMY_NUM];
	VECTOR pos[ENEMY_NUM];
	VECTOR rot[ENEMY_NUM];		//回転
	float speed[ENEMY_NUM];//移動の加速用
	float angle[ENEMY_NUM];//回転の加速用
	bool isMove[ENEMY_NUM];//動ける=true
	bool isDef[ENEMY_NUM];//ダートゾーンに入ってる=true
	bool isSlip[ENEMY_NUM];//スリップした=true
	bool isGoal[ENEMY_NUM];//ゴールした=true
	//固定変数
	const float speedMax[COLOR_NUM] = { 1.58f,1.59f,1.59f,1.58f,1.55f,1.56f };//車ごとの加速限界値
	const float speedUp[COLOR_NUM] = { 0.01f,0.02f,0.02f,0.01f,0.01f,0.02f };//車ごとの加速速度
	const float speedDef[COLOR_NUM] = { 0.7f,0.5f,0.4f,0.4f,0.7f,0.5f };//車ごとの減速した時の速度
	const float rotUp[COLOR_NUM] = { 0.015f,0.013f,0.012f,0.012f,0.015f,0.013f };//車ごとの回転加速速度
	//アイテム用
	int item[ENEMY_NUM];//持っているアイテムの番号
	float time[ENEMY_NUM];//アイテムインターバル時間計測用
	float rtime[ENEMY_NUM];//ランダムインターバル時間計測用
	bool isDash[ENEMY_NUM];//ダッシュしてる=true
	bool isCandy[ENEMY_NUM][3];//キャンディーを使った=true :[player][candyNum]
	int candy[ENEMY_NUM];//持っているキャンディーの数
	bool isStick[ENEMY_NUM];//スティックを使った=true
	bool isBom[ENEMY_NUM];//ボムを使った=true
	bool isBom2[ENEMY_NUM];//ボムを投げて使った=true
	//周回用
	int check[ENEMY_NUM]; //チェックポイント
	int track[ENEMY_NUM]; //何周
	int rank[ENEMY_NUM]; //順位
	VECTOR distanceVec[ENEMY_NUM];//チェックポイントとの距離(VECTOR
	float distance[ENEMY_NUM]; //チェックポイントとの距離(float
	//敵の当たり判定
	VECTOR topPos[ENEMY_NUM]; //敵の先頭のpos
	VECTOR bootPos[ENEMY_NUM]; //敵の最後尾のpos
	VECTOR rightPos[ENEMY_NUM][2]; //敵の左右のpos　[player][左右]
	VECTOR lookPos[ENEMY_NUM]; //敵の左右のpos　[player]

};				