#pragma once

#include "model.h"

//パーティクルクラス
class Particle : public Image
{
public:
	Particle() {};	//ｺﾝｽﾄﾗｸﾀ
	~Particle() {};	//ﾃﾞｽﾄﾗｸﾀ

	//仮想関数
	virtual void init(int index);
	virtual void ctrl();
	virtual void draw();

protected:
	int particleMax;	//ﾊﾟｰﾃｨｸﾙ数

	struct Ptcl
	{
		int		blendMode;	//ﾌﾞﾚﾝﾄﾞﾓｰﾄﾞ
		VECTOR	pos;		//位置
		VECTOR	add;		//増分値
		int		lifeTime;	//生存期間
		float	size;		//ﾊﾟｰﾃｨｸﾙのｻｲｽﾞ
		float	alpha;		//透明度
		float	radian;		//角度(ﾗｼﾞｱﾝ)
		bool	isActive;	//表示中ﾌﾗｸﾞ
		//構造体のｺﾝｽﾄﾗｸﾀ
		Ptcl() {
			pos = VGet(0, 0, 0);
			lifeTime = 500;
			size = 5.0f;
			alpha = 255;	//完全不透明
			radian = 0;
			isActive = false;
		}
	}*ptcl;
};