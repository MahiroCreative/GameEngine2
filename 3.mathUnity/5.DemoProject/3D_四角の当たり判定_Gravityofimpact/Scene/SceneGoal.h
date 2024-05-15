#pragma once
#include "SceneBase.h"

class SceneGoal : public SceneBase
{
public:
	SceneGoal();
	virtual ~SceneGoal();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	//Clearの画像格納変数
	int ClearGraph;

	//3Dのオブジェクト
	int Map, Player;

	//3Dの座標
	float MapX, MapY, MapZ;
	float PlayerX, PlayerY, PlayerZ;

	//シーン遷移させるためのフラグ
	bool SceneChange;

	//カメラのポジション
	VECTOR cameraPos = VGet(0.0f, 0.0f, 0.0f);

	//カメラのターゲット
	VECTOR cameraTarget = VGet(0.0f, 0.0f, 0.0f);

	//モデルのポジション
	VECTOR MapPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR PlayerPos = VGet(0.0f, 0.0f, 0.0f);
};

