#pragma once
#include"global.h"

class Model {
public:
	Model();//ｺﾝｽﾄﾗｸﾀ
	~Model();//ﾃﾞｽﾄﾗｸﾀ
	bool loadModel(const char* fileName);//モデル読み込み
	void showModel(VECTOR mhPos);//モデル表示
	void setScale(float Scale);//モデルサイズ設定
	void Rotation(VECTOR rot);//モデル向き設定

	//コリジョン(当たり判定)情報を設定する
	void setupCollInfo();
	//座標を返す
	inline VECTOR getPos() {
		return pos;
	}
	//モデルハンドルの取得
	inline int getMHandle() {
		return mhModel;
	}
	//回転の取得
	inline VECTOR getRotation() {
		return rot;
	}
	
private:
	int mhModel;//モデル用ハンドル
protected://継承先用
	VECTOR oldpos;//衝突時に戻す用の座標

	VECTOR pos;//座標
	VECTOR rot;	//回転
};

class Image {
public:
	Image();//ｺﾝｽﾄﾗｸﾀ
	~Image() {};//ﾃﾞｽﾄﾗｸﾀ
	bool loadImage(const char* fileName);//画像読み込み
	
	void showImage();//モデル表示
	void showImage(VECTOR pos);//モデル表示座標入力込み
	void drawBillboard(VECTOR pos, float size, float angle);//画像(ｽﾌﾟﾗｲﾄ)のﾋﾞﾙﾎﾞｰﾄﾞ表示(1枚画像用)

	//半透明を有効にする
	inline void alphaOn() {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}
	//半透明を無効にする
	inline void alphaOff() {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
private:
	int gHandle;//画像用ハンドル
	int addAlpha;	//透明度の加減算値
protected://継承先用
	VECTOR pos;		//表示位置
	int alpha;		//透明度
};