#pragma once
#include"collision.h"
class Game :public Collision {
public:
	Game();//ｺﾝｽﾄﾗｸﾀ
	~Game();//ﾃﾞｽﾄﾗｸﾀ
	void init();//初期化処理
	void ctrl();//操作処理
	void draw();//表示処理
private:
	int Color[COLOR_NUM];
	float time;//時間計測用
	DINPUT_JOYSTATE input[2];//コントローラー変数

};