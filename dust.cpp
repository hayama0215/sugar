#include "dust.h"
Dust::Dust()
{
	loadImage("image/smoke.png");	//ﾊﾟｰﾃｨｸﾙ画像の読込み

	//パーティクル数分の配列を確保
	particleMax = 20;
	ptcl = (Ptcl*)malloc(sizeof(Ptcl) * particleMax);

	//初期化
	for (int i = 0; i < particleMax; i++) {
		init(i);
	}
}

void Dust::init(int index)
{
	ptcl[index].blendMode = DX_BLENDMODE_ADD;	//加算合成
	ptcl[index].pos = VGet((float)GetRand(2)+10, 0, 0);	//位置
	ptcl[index].lifeTime = GetRand(50);		//生存期間
	ptcl[index].size = 10.0f;					//ﾊﾟｰﾃｨｸﾙのｻｲｽﾞ
	ptcl[index].alpha = GetRand(64) + 192 - 1;	//透明度
	ptcl[index].radian = 0;			//角度(ﾗｼﾞｱﾝ)
	ptcl[index].isActive = false;	//表示中ﾌﾗｸﾞ
}

void Dust::ctrl()
{
	for (int i = 0; i < particleMax; i++) 
	{
		if (ptcl[i].isActive) continue;	//動作中は飛ばす

		ptcl[i].isActive = true;	//動作中にする
		ptcl[i].pos = pos;			//ﾌﾟﾚｲﾔｰの位置(足元)
		ptcl[i].pos.y = -3.0f;		//地面から
		break;	//1つ動かしたらbreak;
	}

	for (int i = 0; i < particleMax; i++)
	{
		if (!ptcl[i].isActive) continue;	//未動作は飛ばす

		ptcl[i].pos.y += 0.08f;	//上昇させる
		ptcl[i].alpha -= (float)GetRand(10) * 0.1f;
		ptcl[i].lifeTime--;		//ｶｳﾝﾄﾀﾞｳﾝ
		if (ptcl[i].lifeTime <= 0) {
			init(i);
		}
	}
}
