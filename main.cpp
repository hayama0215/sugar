#include"game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	ChangeWindowMode(TRUE);			//����޳Ӱ�ނŋN��
	SetGraphMode(WND_W, WND_H, 32);	//��ʻ���1280�~720
	srand((unsigned int)time(NULL));
	if (DxLib_Init() == -1) return -1;	//Dxײ���؏�����
	SetDrawScreen(DX_SCREEN_BACK);	//����ʂɕ\��
	SetUseZBuffer3D(TRUE);			//Z�̈���g��
	SetWriteZBuffer3D(TRUE);		//Z�̈�ɏ����݂�����
	SetCameraNearFar(1.0f, 2000.0f);	//��ׂ�Z�͈�(1�`1000)
	//�����̏�͊�{�G��Ȃ�
	//�摜�̓Ǎ���
	class Game game;
	//�Q�[�����[�v
	while (true)
	{
		ClearDrawScreen();	//��ʂ̸ر
		game.ctrl();
		game.draw();
		
		//�������火�͊�{�G��Ȃ�
		ScreenFlip();		//����ʂ�\��
		WaitTimer(10);		//���ԑ҂�
		if (ProcessMessage() == -1)break;	//�~���݂ŏI��
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;	//ESC�ŏI��
	}
	InitGraph();	//�S�Ẳ摜���폜
	InitSoundMem();	//�S�Ẳ����폜

	DxLib_End();	//Dxײ���؂̏I��
	return 0;
}