#pragma once
#include "global.h"

class Sound{
public:
	Sound() {};	//ｺﾝｽﾄﾗｸﾀ
	~Sound();	//ﾃﾞｽﾄﾗｸﾀ

	bool loadSound(const char* fileName);//サウンド読込み
	void stopBGM();//bgmを止める
	void playBGM();//bgmを流す
	void SE_Play();//効果音（SE）の再生関数
private:

	int SHandle;	//ｻｳﾝﾄﾞﾊﾝﾄﾞﾙ
};