#include "DxLib.h"
#include "Quaternion.h"

// スクリーンサイズ
#define SCREEN_W 1280
#define SCREEN_H 720


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(SCREEN_W, SCREEN_H, 32);		// 解像度をSCREEN_W*SCREEN_H、colorを16bitに設定.

	// ウインドウモード
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 裏画面に描画を行う
	SetDrawScreen(DX_SCREEN_BACK);

	// Scene開始

	//奥行0.1～10000までをカメラの描画範囲とする
	SetCameraNearFar(1.0f, 10000.0f);

	VECTOR pos = VGet(0,0,0);
	VECTOR cPos = VGet(0, 0, -30);
	VECTOR cUp = VGet(cPos.x, cPos.y + 1, cPos.z);
	VECTOR cRight = VGet(cPos.x + 1, cPos.y, cPos.z);
	Quaternion cQ;

	float angle = - 2 * DX_PI_F * 0.002f;//0.72度;
	float Range = 2000.0f;
	float Atten0 = 1.0f;
	float Atten1 = 0.0006f;
	float Atten2 = 0.0f;
	int handle = CreatePointLightHandle(cPos, Range, Atten0, Atten1, Atten2);
	int pHandle = MV1LoadModel("Player.mv1");
	MV1SetPosition(pHandle, pos);
	MV1SetScale(pHandle, VGet(0.02f, 0.02f, 0.02f));

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// フレーム開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアにする
		ClearDrawScreen();

		// ゲームの処理
		VECTOR axis = VGet(0,0,0);
		VECTOR vec = VGet(0, 0, 0);
		VECTOR up = VSub(cUp, cPos);
		VECTOR right = VSub(cRight, cPos);
		VECTOR center = VSub(pos, cPos);

		// 縦周り回転
		if (CheckHitKey(KEY_INPUT_UP))
		{
			axis = VAdd(axis, VSub(VGet(0, 0, 0), right));
			axis = VNorm(axis);
		}
		else if (CheckHitKey(KEY_INPUT_DOWN))
		{
			axis = VAdd(axis,right);
			axis = VNorm(axis);
		}

		// 横周り回転
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			axis = VAdd(axis, up);
			axis = VNorm(axis);
		}
		else if (CheckHitKey(KEY_INPUT_LEFT))
		{
			axis = VAdd(axis, VSub(VGet(0, 0, 0), up));
			axis = VNorm(axis);
		}

		// 旋回回転
		if (CheckHitKey(KEY_INPUT_Z))
		{
			axis = VAdd(axis, center);
			axis = VNorm(axis);
		}
		else if (CheckHitKey(KEY_INPUT_C))
		{
			axis = VAdd(axis, VSub(VGet(0, 0, 0), center));
			axis = VNorm(axis);
		}

		// 移動
		if (CheckHitKey(KEY_INPUT_D))
		{
			vec = VAdd(vec,right);
			vec = VScale(VNorm(vec), 0.3f);
		}
		else if (CheckHitKey(KEY_INPUT_A))
		{
			vec = VAdd(vec, VSub(VGet(0, 0, 0), right));
			vec = VScale(VNorm(vec), 0.3f);
		}
		
		// 旋回回転
		if (CheckHitKey(KEY_INPUT_W))
		{
			vec = VAdd(vec, center);
			vec = VScale(VNorm(vec), 0.3f);
		}
		else if (CheckHitKey(KEY_INPUT_S))
		{
			vec = VAdd(vec, VSub(VGet(0, 0, 0), center));
			vec = VScale(VNorm(vec), 0.3f);
		}

		cQ.SetMove(angle, axis);
		cPos = cQ.Move(cPos,vec);
		cUp = cQ.Move(cUp,vec);
		cRight = cQ.Move(cRight, vec);

		SetLightPositionHandle(handle, cPos);
		SetCameraPositionAndTargetAndUpVec(cPos, pos, up);


		for (int x = -10; x < 10; x++)
		{
			DrawLine3D(VGet(x * 3, 0, -30), VGet(x * 3, 0, 30), 0x00f000);
		}
		for (int z = -10; z < 10; z++)
		{
			DrawLine3D(VGet(-30, 0, z * 3), VGet(30, 0, z * 3), 0xf00000);
		}

		DrawLine3D(VGet(0, 0, 0), VScale(axis, 30), 0x0000f0);

		MV1DrawModel(pHandle);
		// DrawCone3D(VGet(pos.x + 20, pos.y + 20, pos.z), VGet(pos.x - 20, pos.y - 20, pos.z), 10, 32, 0xffffff, 0xffffff, true);

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// end処理
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}


		// FPSを60に固定
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16,66ミリ秒(16667マイクロ秒)経過まで待つ
		}
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}