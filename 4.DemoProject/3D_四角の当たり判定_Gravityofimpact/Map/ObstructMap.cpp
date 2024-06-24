#include "ObstructMap.h"

ObstructMap::ObstructMap()
{
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel("data/MapCube.mv1");
	if (modelHandle < 0)
	{
		printfDx("ObstructMapデータ読み込み失敗");
	}

	//Mapの大きさ設定
	float MapScale = 12.0f;

	//Mapの大きさを変える
	MV1SetScale(modelHandle, VGet(MapScale, MapScale, MapScale));

	pos = VGet(0, 0, 0);
}

ObstructMap::~ObstructMap()
{
	//モデルのアンロード
	MV1DeleteModel(modelHandle);
}

void ObstructMap::Update()
{
	//3Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);
}

void ObstructMap::Draw()
{
	//3Dモデルの描画
	MV1DrawModel(modelHandle);
}
