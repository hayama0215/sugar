#pragma once
#include "DxLib.h"
#include<stdlib.h>
#include<time.h>
#include<Math.h>
#include <cmath>	//数学関数用

//マクロ定義
#define WND_W	1200			//ｳｨﾝﾄﾞｳ幅
#define WND_H	600		//ｳｨﾝﾄﾞｳ高さ

#define ErrMsg(s, f) MessageBox(NULL, s, f, MB_OK);
#define ToRadian(x)(x*DX_PI_F /180.0f)	//度→ﾗｼﾞｱﾝ変換

#define SPEED_MAX 1.0f //最大の速度
#define PLAYER_NUM 2 //プレイヤーの数
#define ITEM_MAX 7 
#define ITEM_lINTERVAL 250
#define SHOT_INTERVAL 60
#define SHOT_SPEED 5
#define GOAL_TRACK 3
#define ENEMY_NUM 4
#define COLOR_NUM 6//車の色の種類

// マップ範囲
#define MAP_MAX_X 1000.0f
#define MAP_MAX_Z 1000.0f

//画面の遷移の列挙隊
enum class Mode
{
	TITLE,
	SETTING,
	PLAY,
	FIN,
};
