#include "DxLib.h"
#include"Camera.h"
#include <cmath>
#include<iostream>

#include"Pad.h"

using namespace std;

namespace
{
	constexpr float kCameraDist = 96;
	constexpr float kCameraHeight = 32;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	std::shared_ptr<Camera> camera;
	camera = std::make_shared<Camera>();

	float posX = 5;
	float moveSpeed = 0.2f;

	int sphere1R = 2;
	int sphere2R = 5;

	float colFlag = 0;

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();
		posX-= moveSpeed;
		if (posX < -5)
		{
			moveSpeed = -0.2f;
		}
		if (posX > 5)
		{
			moveSpeed = 0.2f;
		}
	
		

		VECTOR sphere1Pos = VGet(posX, 0, 0);
		VECTOR sphere2Pos = VGet(-posX, 0, 0);
		
		colFlag = false;
		camera->Update();
		//距離を求める
		int Distance = sqrt((sphere2Pos.x - sphere1Pos.x) * (sphere2Pos.x - sphere1Pos.x) + (sphere2Pos.y - sphere1Pos.y) * (sphere2Pos.y - sphere1Pos.y) + (sphere2Pos.z - sphere1Pos.z) * (sphere2Pos.z - sphere1Pos.z));
		if (Distance < sphere1R + sphere2R)//半径の合計より距離が短かったら
		{
			colFlag = true;
		}
		DrawSphere3D(sphere1Pos, sphere1R, 0, 0xff0000, 0xff0000, colFlag);
		DrawSphere3D(sphere2Pos, sphere2R, 0, 0x0000ff, 0x0000ff, colFlag);

		

		for (int x = -50; x <= 50; x += 10)
		{
			DrawLine3D(VGet(static_cast<float>(x), 0, -50), VGet(static_cast<float>(x), 0, 50), 0xffff00);
		}
		for (int z = -50; z <= 50; z += 10)
		{
			DrawLine3D(VGet(-50, 0, static_cast<float>(z)), VGet(50, 0, static_cast<float>(z)), 0xff0000);
		}

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}