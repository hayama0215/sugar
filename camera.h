#pragma once
#include"model.h"
class Camera :public Model {
public:
	Camera();//ｺﾝｽﾄﾗｸﾀ
	~Camera() {};//ﾃﾞｽﾄﾗｸﾀ
	void setCamera(VECTOR cPos,VECTOR lPos);	//ｶﾒﾗ位置の更新
	void ctrl(VECTOR pos, VECTOR rot,int index);//操作処理
	void draw(int index);//表示処理
private:

	VECTOR cameraPos[2], lookPos[2];	//ｶﾒﾗ位置、注視位置
	int LightHandle;//2個目のライトのハンドル
};