#include "sound.h"

//�f�X�g���N�^
Sound::~Sound()
{
	DeleteSoundMem(SHandle);
}

//�T�E���h�Ǎ��݊֐�
bool Sound::loadSound(const char* fileName)
{
	SHandle = LoadSoundMem(fileName);
	if (SHandle == -1) {
		MessageBox(NULL, "�T�E���h�̓Ǎ��ݎ��s",
			fileName, MB_OK);
		return false;
	}
	return true;
}

void Sound::stopBGM() {
	StopSoundMem(SHandle);  //�Đ����~
}

void Sound::playBGM() {
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP, TRUE);
}
//���ʉ��iSE�j�̍Đ��֐�
void Sound::SE_Play()
{
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK, TRUE);
}
