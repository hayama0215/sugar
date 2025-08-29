#include "collision.h"

//当たり判定(球)
bool Collision::hitCheck_Sphere(
	VECTOR center1, float r1, VECTOR center2, float r2)
{
	//中心線の長さを求める
	//a^2 + b^2 + c^2
	float centerLength =
		(center1.x - center2.x) * (center1.x - center2.x)		//a^2
		+ (center1.y - center2.y) * (center1.y - center2.y)		//b^2
		+ (center1.z - center2.z) * (center1.z - center2.z);	//b^2

	//半径の足し算を2乗したものと中心線の長さを比べる
	//a^2+b^2+c^2 < (r1+r2)^2
	if (centerLength < (r1 + r2) * (r1 + r2)) {
		return true;	//当たっている
	}
	return false;	//外れている
}

//Sphere(球)の表示
void Collision::drawSphere(VECTOR pos, float r)
{
	DrawSphere3D(
		pos,			//表示位置
		r,				//半径
		8,				//分割数
		DIFFUSE_COLOR,	//ﾃﾞｨﾌｭｰｽﾞ色(物体の色)
		SPECULAR_COLOR,	//ｽﾍﾟｷｭﾗｰ色(反射した色)
		FALSE);			//TRUE:塗りつぶし　FALSE:ﾌﾚｰﾑ表示
}

//当たり判定(カプセル)
bool Collision::collCheck_Capsule(int MHandle, VECTOR pos1, VECTOR pos2, float r)
{
	MV1_COLL_RESULT_POLY_DIM hitPolyDim;	//判定結果構造体

	hitPolyDim = MV1CollCheck_Capsule(
		MHandle,	//予めsetupCollInfoしたﾓﾃﾞﾙﾊﾝﾄﾞﾙ
		-1,			//判定するﾌﾚｰﾑ番号(全体なら-1)
		pos1,		//ぶつかってくるｵﾌﾞｼﾞｪｸﾄの上の中心座標
		pos2,		//ぶつかってくるｵﾌﾞｼﾞｪｸﾄの下の中心座標
		r);			//ぶつかってくるｵﾌﾞｼﾞｪｸﾄの半径
	if (hitPolyDim.HitNum >= 1) {
		//1ﾎﾟﾘｺﾞﾝ以上当たっている時
		return true;	//衝突
	}
	return false;	//外れ
}
//カプセルの表示
void Collision::drawCapsule(VECTOR pos1, VECTOR pos2, float r)
{
	DrawCapsule3D(
		pos1,			//ｶﾌﾟｾﾙの上の位置
		pos2,			//ｶﾌﾟｾﾙの下の位置
		r,				//半径
		8,				//分割数
		DIFFUSE_COLOR,	//ﾃﾞｨﾌｭｰｽﾞ色(物体の色)
		SPECULAR_COLOR,	//ｽﾍﾟｷｭﾗｰ色(反射した色)
		FALSE);			//TRUE:塗りつぶし　FALSE:ﾌﾚｰﾑ表示
}

bool Collision::hitCheckLineX(VECTOR pos1, VECTOR pos2, float size) {//線とモデルの当たり判定X
	if (pos2.x - size < pos1.x && pos2.x + size > pos1.x && pos1.z >= pos2.z-5 && pos1.z <= pos2.z + 5) {
		return true;
	}
	return false;
}
bool Collision::hitCheckLineZ(VECTOR pos1, VECTOR pos2, float size) {//線とモデルの当たり判定Z
	if (pos2.z - size < pos1.z && pos2.z + size > pos1.z && pos1.x >= pos2.x-5 && pos1.x <= pos2.x + 5) {
		return true;
	}
	return false;
}