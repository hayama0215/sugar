#include "particle.h"

//初期化処理
void Particle::init(int index)
{
	ptcl[index].blendMode = DX_BLENDMODE_ADD;	//加算合成
	ptcl[index].pos = VGet((float)GetRand(2), 0, 0);	//位置
	ptcl[index].lifeTime = GetRand(500);		//生存期間
	ptcl[index].size = 5.0f;					//ﾊﾟｰﾃｨｸﾙのｻｲｽﾞ
	ptcl[index].alpha = GetRand(64) + 192 - 1;	//透明度
	ptcl[index].radian = 0;			//角度(ﾗｼﾞｱﾝ)
	ptcl[index].isActive = true;	//表示中ﾌﾗｸﾞ
}

//操作処理
void Particle::ctrl()
{
	for (int i = 0; i < particleMax; i++)
	{
		float wide = (float)GetRand(10) * 0.01f;
		ptcl[i].pos.x += cos(ptcl[i].radian) * wide;
		ptcl[i].radian += (float)GetRand(10) * 0.01f;
		ptcl[i].pos.y += 0.05f;
		ptcl[i].alpha -= (float)GetRand(5) * 0.1f;
		ptcl[i].lifeTime--;
		if (ptcl[i].lifeTime <= 0) {
			init(i);
		}
	}
}
//表示処理
void Particle::draw()
{
	for (int i = 0; i < particleMax; i++)
	{
		alpha = ptcl[i].alpha;
		alphaOn();		//透明度を有効にする
		drawBillboard(ptcl[i].pos,
			ptcl[i].size, ptcl[i].radian);
	}
	alphaOff();	//透明度を無効にする
}
