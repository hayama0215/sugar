#pragma once
#include"global.h"

#define DIFFUSE_COLOR GetColor(255,0,0)  //ﾃﾞｨﾌｭｰｽﾞ色(拡散反射色)
#define SPECULAR_COLOR GetColor(255,0,0) //ｽﾍﾟｷｭﾗｰ色(鏡面反射色)

class Collision {
public:
	//当たり判定(球:計算版)
	bool hitCheck_Sphere(VECTOR center1, float r1,VECTOR center2, float r2);
	void drawSphere(VECTOR pos, float r);

	//当たり判定(カプセル)
	bool collCheck_Capsule(int MHandle, VECTOR pos1, VECTOR pos2, float r);
	void drawCapsule(VECTOR pos1, VECTOR pos2, float r);	//ｶﾌﾟｾﾙ


	bool hitCheckLineX(VECTOR pos1, VECTOR pos2,float size);//線との当たり判定
	bool hitCheckLineZ(VECTOR pos1, VECTOR pos2,float size);//線との当たり判定
};