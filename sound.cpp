#include "sound.h"

//デストラクタ
Sound::~Sound()
{
	DeleteSoundMem(SHandle);
}

//サウンド読込み関数
bool Sound::loadSound(const char* fileName)
{
	SHandle = LoadSoundMem(fileName);
	if (SHandle == -1) {
		MessageBox(NULL, "サウンドの読込み失敗",
			fileName, MB_OK);
		return false;
	}
	return true;
}

void Sound::stopBGM() {
	StopSoundMem(SHandle);  //再生を停止
}

void Sound::playBGM() {
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP, TRUE);
}
//効果音（SE）の再生関数
void Sound::SE_Play()
{
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK, TRUE);
}
