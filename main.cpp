#include"game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	ChangeWindowMode(TRUE);			//ｳｨﾝﾄﾞｳﾓｰﾄﾞで起動
	SetGraphMode(WND_W, WND_H, 32);	//画面ｻｲｽﾞ1280×720
	srand((unsigned int)time(NULL));
	if (DxLib_Init() == -1) return -1;	//Dxﾗｲﾌﾞﾗﾘ初期化
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面に表示
	SetUseZBuffer3D(TRUE);			//Z領域を使う
	SetWriteZBuffer3D(TRUE);		//Z領域に書込みを許可
	SetCameraNearFar(1.0f, 2000.0f);	//ｶﾒﾗのZ範囲(1～1000)
	//↑この上は基本触らない
	//画像の読込み
	class Game game;
	//ゲームループ
	while (true)
	{
		ClearDrawScreen();	//画面のｸﾘｱ
		game.ctrl();
		game.draw();
		
		//ここから↓は基本触らない
		ScreenFlip();		//裏画面を表示
		WaitTimer(10);		//時間待ち
		if (ProcessMessage() == -1)break;	//×ﾎﾞﾀﾝで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;	//ESCで終了
	}
	InitGraph();	//全ての画像を削除
	InitSoundMem();	//全ての音を削除

	DxLib_End();	//Dxﾗｲﾌﾞﾗﾘの終了
	return 0;
}