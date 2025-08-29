#pragma once
#include"model.h"
#include"sound.h"
class Player {
public:
	Player();//ｺﾝｽﾄﾗｸﾀ
	~Player() {};//ﾃﾞｽﾄﾗｸﾀ
	void init();//初期化処理
	void load();//モデル読み込み
	void ctrl();//操作処理
	void draw();//表示処理

	inline void setColor(int index, int clr) {
		color[index] = clr;
	}
	inline int getColor(int index) {
		return color[index];
	}
	//当たり判定
	inline VECTOR getPos(int index) {//座標を配列の個別で返す（modelのオーバーロード
		return pos[index];
	}
	inline void initPos(int map) {//マップごとに初期値を変える
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
 	inline VECTOR getRotation(int index) {//回転量を配列の個別で返す（modelのオーバーロード
		return rot[index];
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
	}
	inline void hitBoot(int index) {//後ろに当たった時の設定
		pos[index] = oldpos[index];
		speed[index] = speedMax[index] / 5;
		pos[index].x -= sinf(rot[index].y) * (speed[index]);
		pos[index].z -= cosf(rot[index].y) * (speed[index]);
	}
	inline void hitR(int index,int num) {//左右に当たった時の設定
		pos[index] = oldpos[index];
		if(num==0) rot[index].y -= rotUp[index];
		if(num==1) rot[index].y += rotUp[index];
	}
	inline void hitLook(int index, int num) {//左右の視点位置に当たった時の設定
		if (num == 0) rot[index].y += rotUp[index];
		if (num == 1) rot[index].y -= rotUp[index];
	}
	//アイテム用
	inline void setItem(int index) {//アイテムを手に入れたら
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
	inline bool getisDash(int index) {//ダッシュを使ったら
		return isDash[index];
	}
	inline void setCandy(int index) {//キャンディーを入手したら球を最大数にセットする
		if(candy[index] == 0)candy[index] = 3;
	}
	inline void offisCandy(int index, int num) {//キャンディーを使い切る
		isCandy[index][num] = false;
	}
	inline bool getisCandy(int index,int num) {
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
	
	//周回用
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
	
	inline void setDistance(int index, VECTOR checkpos) {//チェックポイントとの距離を取る
		distanceVec[index] = VSub(checkpos, pos[index]);
		distance[index] = VSize(distanceVec[index]);
	}
	inline float getDistanse(int index) {//チェックポイントとの距離を渡す
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
	int color[PLAYER_NUM];//車の色
	//サウンド
	Sound* se[2];
	//移動用
	VECTOR oldpos[PLAYER_NUM];
	VECTOR pos[PLAYER_NUM];//座標
	VECTOR rot[PLAYER_NUM];//回転
	float speed[PLAYER_NUM];//移動の加速用
	float angle[PLAYER_NUM];//回転の加速用
	bool isMove[PLAYER_NUM];//動ける=true
	bool isDef[PLAYER_NUM];//ダートゾーンに入ってる=true
	bool isSlip[PLAYER_NUM];//スリップした=true
	bool isGoal[PLAYER_NUM];//ゴールした=true
	DINPUT_JOYSTATE input[PLAYER_NUM];//コントローラー設定
	//固定変数
	const float speedMax[COLOR_NUM] = {1.52f,1.54f,1.55f,1.54f,1.51f,1.53f};//車ごとの加速限界値
	const float speedUp[COLOR_NUM] = {0.011f,0.012f,0.013f,0.013f,0.011f,0.013f};//車ごとの加速速度
	const float speedDef[COLOR_NUM] = {0.7f,0.5f,0.4f,0.4f,0.7f,0.5f};//車ごとの減速した時の速度
	const float rotUp[COLOR_NUM] = { 0.011f,0.011f,0.01f,0.01f,0.012f,0.011f };//車ごとの回転加速速度
	//アイテム用
	int item[PLAYER_NUM];//持っているアイテムの番号
	float time[PLAYER_NUM];//インターバル時間計測用
	bool isDash[PLAYER_NUM];//ダッシュしてる=true
	bool isCandy[PLAYER_NUM][3];//キャンディーを使った=true :[player][candyNum]
	int candy[PLAYER_NUM];//持っているキャンディーの数
	bool isStick[PLAYER_NUM];//スティックを使った=true
	bool isBom[PLAYER_NUM];//ボムを使った=true
	bool isBom2[PLAYER_NUM];//ボムを投げて使った=true
	//周回用
	int check[PLAYER_NUM]; //チェックポイント
	int track[PLAYER_NUM]; //何周
	int rank[PLAYER_NUM]; //順位
	VECTOR distanceVec[PLAYER_NUM];//チェックポイントとの距離(VECTOR
	float distance[PLAYER_NUM]; //チェックポイントとの距離(float
	//プレイヤーの当たり判定
	VECTOR topPos[PLAYER_NUM]; //プレイヤーの先頭のpos
	VECTOR bootPos[PLAYER_NUM]; //プレイヤーの最後尾のpos
	VECTOR rightPos[PLAYER_NUM][2]; //プレイヤーの左右のpos　[player][左右]
	VECTOR lookPos[PLAYER_NUM]; //プレイヤーの左右のpos　[player]

};

