#pragma once
#include"model.h"
class Item :public Model {
public:
	Item();//ｺﾝｽﾄﾗｸﾀ
	~Item() {};//ﾃﾞｽﾄﾗｸﾀ
	void init();//初期化処理
	void ctrl();//操作処理
	void draw();//表示処理

	inline VECTOR getPos(int index) {//座標を配列の個別で返す（modelのオーバーロード）
		return pos[index];
	}
	inline void getItem(int index) {//アイテムを入力したら床下に隠す
		pos[index].y = -20;
	}
	inline void initPos(int map) {//ステージごとにアイテムの位置を変える
		if (map == 1) {
			pos[0] = VGet(-MAP_MAX_X + 400, 10, 50);
			pos[1] = VGet(-MAP_MAX_X + 360, 10, 50);
			pos[2] = VGet(-MAP_MAX_X + 320, 10, 50);
			pos[3] = VGet(-MAP_MAX_X + 280, 10, 50);
			pos[4] = VGet(-MAP_MAX_X + 380, 10, 80);
			pos[5] = VGet(-MAP_MAX_X + 340, 10, 80);
			pos[6] = VGet(50, 10, -MAP_MAX_X + 100);
		}
		if (map == 2) {
			pos[0] = VGet(-120, 10, -400);
			pos[1] = VGet(-120, 10, -450);
			pos[2] = VGet(-120, 10, -500);
			pos[3] = VGet(-180, 10, -420);
			pos[4] = VGet(-180, 10, -470);
			pos[5] = VGet(-310, 10, -MAP_MAX_X + 200);
			pos[6] = VGet(0, -10, 0);
		}
		if (map == 3) {
			pos[0] = VGet(20, 10, -180);
			pos[1] = VGet(60, 10, -180);
			pos[2] = VGet(100, 10, -180);
			pos[3] = VGet(40, 10, -110);
			pos[4] = VGet(80, 10, -110);
			pos[5] = VGet(-510, 10, MAP_MAX_X - 200);
			pos[6] = VGet(-500, 10, MAP_MAX_X - 150);
		}
	}

	inline void setMilk(int index,VECTOR pos) {//コーヒー牛乳をプレイヤーの頭の上に
		milkpos[index] = pos;
		milkpos[index].y += 6;
	}
	inline void removeMilk(int index) {//使っていないときは床下に隠す
		milkpos[index] = VGet(0, -100, 0);
	}

	inline void setCandy(int index,int num, VECTOR pos,VECTOR rot) {//キャンディーをプレイヤーに
		if (!isCandy[index][num]) {
			candyrot[index][num] = rot;
			candypos[index][num] = pos;
			candypos[index][num].y += 5;
		}
	}
	inline void setisCandy(int index,int num, bool iscandy ){//キャンディーが使われた
		isCandy[index][num] = iscandy;
	}
	inline void removeCandy(int index,int num) {//キャンディーを使い終えた
		candypos[index][num] = VGet(0, -100, 0);
		isCandy[index][num] = false;
	}
	inline VECTOR getCandypos(int index, int num) {//キャンディーの座標を配列の個別で返す
		return candypos[index][num];
	}

	inline void setStick(int index, VECTOR pos) {//スティックをプレイヤーの頭の上に
		stickpos[index] = pos;
		stickpos[index].y += 7;
	}
	inline void setisStick(int index, bool isstick) {//スティックが使われた
		isStick[index] = isstick;
	}
	inline void removeStick(int index) {//スティックを使い終えた
		stickpos[index] = VGet(0, -100, 0);
		stickcenterpos[index] = VGet(0, -100, 0);
	}
	inline VECTOR getStickpos(int index) {//スティックの座標を配列の個別で返す
		return stickcenterpos[index];
	}

	inline void setBom(int index, VECTOR pos,VECTOR rot) {//ボムをプレイヤーの頭の上に
		bomrot[index] = rot;
		bompos[index] = pos;
		bompos[index].y += 7;
	}
	inline void setisBom(int index, bool isbom,bool isbom2) {//ボムが使われた
		isBom[index] = isbom;
		isBom2[index] = isbom2;
	}
	inline void setBompos(int index) {
		if (isBom[index] && !isBom2[index]) {//ボムが使われた
			bompos[index].y = 0;
			bomSpeed[index] = 5;
			bomUpSpeed[index] = 0.5;
		}
		else if(!isBom[index]){//ボムを使い終えた
			bompos[index] = VGet(0, -100, 0);
		}
		
	}
	inline VECTOR getBompos(int index) {//ボムの座標を配列の個別で返す
		return	bompos[index];
	}
private:
	float time[ITEM_MAX];//アイテムのリスポーンカウント用
	VECTOR pos[ITEM_MAX];//アイテム箱の座標（modelのオーバーロード）
	
	Model* milk;//ミルクのモデル
	VECTOR milkpos[COLOR_NUM];//ミルクの座標

	Model* candy[3];//キャンディーのモデル
	VECTOR candypos[COLOR_NUM][3];//キャンディーの座標
	VECTOR candyrot[COLOR_NUM][3];//キャンディーの回転量
	bool isCandy[COLOR_NUM][3];//キャンディーを使っている=true
	
	Model* stick[COLOR_NUM];//スティックのモデル
	VECTOR stickpos[COLOR_NUM];//スティックの座標
	VECTOR stickcenterpos[COLOR_NUM];//スティックの当たり判定の座標
	VECTOR stickrot[COLOR_NUM];//スティックの回転量
	bool isStick[COLOR_NUM];//スティックを使っている=true

	Model* bom;//ボムのモデル
	VECTOR bompos[COLOR_NUM];//ボムの座標
	VECTOR bomrot[COLOR_NUM];//ボムの回転量
	bool isBom[COLOR_NUM];//ボムを使っている=true
	bool isBom2[COLOR_NUM];//ボムを投げて使っている=true
	float bomSpeed[COLOR_NUM];//ボムを前に飛ばす用
	float bomUpSpeed[COLOR_NUM];//ボムを上に飛ばす用
};