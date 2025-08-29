#include"camera.h"
Camera::Camera() {
	SetCameraNearFar(1.0f, 1000.0f);	//ｶﾒﾗのZ範囲(1～1000)
	LightHandle = CreateDirLightHandle(VGet(-1.0f, 0.0f, -1.0f));
	for (int i = 0;i < PLAYER_NUM;i++) cameraPos[i] = lookPos[i] = VGet(0, 0, 0);
}
void Camera::setCamera(VECTOR cPos, VECTOR lPos)
{
	SetDrawAreaFull();
	SetCameraScreenCenter(WND_W / 2, WND_H / 2);//表示を左に移動
	cameraPos[0] = cPos;
	lookPos[0] = lPos;
	//カメラ位置と注視位置の設定
	SetCameraPositionAndTarget_UpVecY(cameraPos[0], lookPos[0]);
}

//TPSカメラ
void Camera::ctrl(VECTOR pos, VECTOR rot, int index)
{
	MATRIX mat1;	//各行列

	//位置情報を設定
	cameraPos[index] = lookPos[index] = pos;

	mat1 = MGetRotY(rot.y);				//Y軸回転行列の作成
	VECTOR axisZ = VGet(0, 0, 1.0f);	//軸ﾍﾞｸﾄﾙ
	axisZ = VTransform(axisZ, mat1);	//向きのﾍﾞｸﾄﾙを求める

	//ｶﾒﾗ位置と注視位置を決定
	VECTOR pos1, pos2;
	pos1 = VScale(axisZ, 50.0f);	//ｶﾒﾗ距離
	pos2 = VScale(axisZ, 40.0f);	//注視距離

	cameraPos[index] = VAdd(cameraPos[index], pos1);	//ｶﾒﾗ位置
	lookPos[index] = VSub(lookPos[index], pos2);		//注視位置

	//Y座標を固定する
	cameraPos[index].y += 30.0f;
	lookPos[index].y += 10.0f;
}

void Camera::draw(int index) {
	if (index == 0) {
		SetDrawArea(0, 0, WND_W / 2, WND_H); // 左半分を表示
		SetCameraScreenCenter(WND_W / 4, WND_H / 2);//表示を左に移動
		//カメラ位置と注視位置の設定
		SetCameraPositionAndTarget_UpVecY(cameraPos[index], lookPos[index]);
	}
	if (index == 1) {
		SetDrawArea(WND_W / 2, 0, WND_W, WND_H); // 右半分を表示
		SetCameraScreenCenter(WND_W - WND_W / 4, WND_H / 2);//表示を右に移動
		//カメラ位置と注視位置の設定
		SetCameraPositionAndTarget_UpVecY(cameraPos[index], lookPos[index]);
	}
}