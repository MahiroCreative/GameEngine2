#pragma once
#include "DxLib.h"
#include "Player/Player.h"
#include<cmath>

#define CAMERA_LOOK_AT_DISTANCE 200.0f;

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void Init();
	void Update(Player& player);
	void Draw();
	void End();

	//カメラのポジション
	VECTOR cameraPos = VGet(0.0f, 0.0f, 0.0f);
	//カメラのターゲット
	VECTOR cameraTarget = VGet(0.0f, 0.0f, 0.0f);

	//カメラのアングル
	VECTOR cameraAngle = VGet(0.0f, 0.0f, 0.0f);

};

