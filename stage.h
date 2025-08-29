#pragma once
#include"model.h"
#include"sound.h"

class Stage :public Model{
public:
	Stage();
	~Stage() {};
	void init();
	void ctrl();
	void show();
	inline Mode getMode() {
		return mode;
	}
	//サウンド
	inline void setMode(Mode set) {
		mode = set;
	}
	inline int getMap() {
		return map;
	}
	//TITLE
	inline VECTOR getbottuntPos(int index) {
		return bPos[index];
	}
	inline int getbuttonNum(int index) {
		return buttonNum[index];
	}
	inline void onMenu() {
		if (time == 0 && !isMenu) {
			isMenu = true;
			time = 30;
			se[1]->SE_Play();
		}
	}
	inline bool getMenu() {
		return isMenu;
	}
	//SETTING
	inline void onChenge(int index) {
		isChange[index] = true;
	}
	inline void offChenge(int index) {
		isChange[index] = false;
	}
	inline void setColor(int index, int col) {
		color[index] = col;
	}
	inline void uiLoad() {
		for (int i = 0; i < COLOR_NUM; i++) {
			if (color[i] == 0) ui[i]->loadImage("image/player.png");
			if (color[i] == 1) ui[i]->loadImage("image/player (1).png");
			if (color[i] == 2) ui[i]->loadImage("image/player (2).png");
			if (color[i] == 3) ui[i]->loadImage("image/player (3).png");
			if (color[i] == 4) ui[i]->loadImage("image/player (4).png");
			if (color[i] == 5) ui[i]->loadImage("image/player (5).png");
		}
	}
	inline bool getChenge(int index) {
		return isChange[index];
	}
	//PLAY
	inline float getTime() {
		return time;
	}
	inline int getMHandle2() {
		return corner->getMHandle();
	}
	//周回用
	inline float getSize(int index) {
		return csize[index];
	}
	inline VECTOR getCheck(int index) {
		return checkPos[index];
	}
	inline void setUiPos(int index, int chc, int trk,float dis,bool gol) {
		check[index] = chc;
		track[index] = trk;
		distance[index] = dis;
		isGoal[index] = gol;
	}
	inline int getRank(int index) {
		return rank[index];
	}
	inline int getMHandleLoad(int index) {
		return load[index]->getMHandle();
	}
	//アイテム用
	inline VECTOR getDashPos(int index) {
		return dashPos[index];
	}
	inline VECTOR getBomPos(int index) {
		return bomPos[index];
	}
	inline void hitBom(int index) {
		bomPos[index].y = -20;
	}
private:
	Mode mode;//モードの関数
	int map;//マップの種類
	//サウンド
	Sound* bgm;
	Sound* se[5];

	//TITLE
	Image* title;
	Image* pin[PLAYER_NUM];//選択画面のカーソル画像
	VECTOR pinPos[PLAYER_NUM];//選択画面のカーソル位置
	Image* Bottun[8];//選択画面のボタン画像
	VECTOR bPos[8];//選択画面のボタン位置
	int buttonNum[PLAYER_NUM];//選択画面のボタンの番号
	int up[PLAYER_NUM];//上下キーを押した瞬間の処理をつけるための変数
	int right[PLAYER_NUM];//左右キーを押した瞬間の処理をつけるための変数
	Image* menu;
	bool isMenu;//メニューを開いている＝true

	//SETTING
	Model* car[COLOR_NUM];//選択画面で表示する車モデル
	VECTOR pos[PLAYER_NUM];//車の表示位置
	VECTOR rot[PLAYER_NUM];//車の回転量
	bool isChange[PLAYER_NUM];//色が被らないように選択したか、してないかをつける
	int color[COLOR_NUM];//プレイヤーの選んだ色
	Image* ok[PLAYER_NUM];//色を選択し終えたら表示されるモデル
	
	DINPUT_JOYSTATE input[PLAYER_NUM];//コントローラー変数

	//PLAY
	float time;
	Image* count[4];//スタートカウントダウンのUI
	Model* corner;//コーナーエリアのモデル
	Image* rankui[COLOR_NUM];//左下に表示する順位UI

	//周回用
	Model* load[2];//自動でカーブを曲がる用の当たり判定モデル
	VECTOR checkPos[9];//チェックポイントラインの座標
	float csize[9];//チェックポイントのサイズ
	int check[COLOR_NUM]; //チェックポイント
	int track[COLOR_NUM]; //何周
	int rank[COLOR_NUM]; //順位
	float distance[COLOR_NUM]; //チェックポイントとの距離(float
	bool isGoal[COLOR_NUM];//ゴールした=true
	int sortedIndices[COLOR_NUM]; // ソートされたインデックスを保持

	//フィールドに置くアイテム
	Model* dash;//触れるとダッシュ出来る
	VECTOR dashPos[6];//ダッシュの座標
	Model* bom;//触れるとスリップする
	VECTOR bomPos[4];//ボムの座標
	int btime[4];//ボムが消えてから復帰するまでのカウント
	VECTOR objRot;//アイテムの回転量

	//画面上に表示するUI
	Image* course;//上に表示する線
	Image* ui[COLOR_NUM];//キャラに合わせて進ませるUI
	VECTOR uiPos[COLOR_NUM];//UIの座標
	Image* rankbord[2];//スコアを表示するボード
	Image* goal;//ゴールした時に表示するテキストUI

	//FIN
	Model* oukan;//優勝者にかぶせる王冠
	VECTOR orot;//勝利したプレイヤーに被せる王冠の回転量	
	int point[COLOR_NUM];//総得点
};