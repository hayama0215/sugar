#include"model.h"
Model::Model() {
	pos = VGet(0, 0, 0);
	rot = VGet(0, 0, 0);
}
Model::~Model() {
	MV1DeleteModel(mhModel);
}

bool Model::loadModel(const char* fileName) {
	mhModel = MV1LoadModel(fileName);
	if (mhModel == -1) {
		ErrMsg("モデルの読込み失敗", fileName);
		return false;
	}
	return true;
}
void Model::showModel(VECTOR mhPos) {
	MV1SetPosition(mhModel, mhPos);
	MV1DrawModel(mhModel);
}
void Model::setScale(float Scale) {
	MV1SetScale(mhModel, VGet(Scale, Scale, Scale));
}
void Model::Rotation(VECTOR rot) {
	MV1SetRotationXYZ(mhModel, rot);
}
//コリジョン(当たり判定)情報を設定する
void Model::setupCollInfo(){
	MV1SetupCollInfo(mhModel, -1, 8, 8, 8);
}

Image::Image() {
	pos = VGet(0, 0, 0);
	alpha = 255;	//完全不透明

}
bool Image::loadImage(const char* fileName) {
	gHandle = LoadGraph(fileName);
	if (gHandle == -1)
	{
		ErrMsg("画像ファイルの読み込み失敗", fileName);
		return false;
	}
	return true;
}

void Image::showImage() {
	DrawGraph(pos.x, pos.y, gHandle, TRUE);
}
void Image::showImage(VECTOR pos) {
	DrawGraph(pos.x, pos.y, gHandle, TRUE);
}

//画像(ｽﾌﾟﾗｲﾄ)のビルボード表示(1枚画像用)
void Image::drawBillboard(
	VECTOR pos, float size, float angle)
{
	DrawBillboard3D(
		pos,		//表示位置
		0.5f, 0.5f,	//画像の中心位置
		size,		//表示する画像ｻｲｽﾞ
		angle,		//表示する角度
		gHandle,	//画像ﾊﾝﾄﾞﾙ
		TRUE);		//透明度(TRUE:有効)
}