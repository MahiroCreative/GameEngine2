#include "DxLib.h"
#include <cmath>


VECTOR Closs(VECTOR pos, VECTOR target)
{
	return VGet(pos.y * target.z - pos.z * target.y,
		pos.z * target.x - pos.x * target.z,
		pos.x * target.y - pos.y * target.x);
}

float Lange(VECTOR normal, VECTOR temp)
{
	float size = VSize(normal);

	return (normal.x * temp.x + normal.y * temp.y + normal.z * temp.z) / size;
}


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 裏画面に描画を行う
	SetDrawScreen(DX_SCREEN_BACK);

	SetCameraNearFar(100.0f, 1.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(0, 8, -20), VGet(0, 0, 0));


	int lightHandle = CreatePointLightHandle(VGet(0, 8, -20), 10000, 0.0f, 0.002f, 0.0f);
	SetLightPositionHandle(lightHandle, VGet(0, 8, -20));


	float lange = 0;

	// 移動しない標準カプセル座標と線分ベクトル
	VECTOR targetPos_End = VGet(3, 1, 10);
	VECTOR targetPos_Start = VGet(-3,-1, 10);
	VECTOR targetVec = VSub(targetPos_End, targetPos_Start);

	// 球の座標
	VECTOR movePos = VGet(12, 0,10);

	float r = 3.0f;

	bool isMove = false;

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// フレーム開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアにする
		ClearDrawScreen();

		// ゲームの処理

		// 移動
		if (!isMove)
		{
			movePos.x -= 0.3f;
		}
		else
		{
			movePos.x += 0.3f;
		}

		if (movePos.x > 15.0f)
		{
			isMove = false;
		}
		if (movePos.x < -15.0f)
		{
			isMove = true;
		}


		// 当たり判定計算
		VECTOR Cap1ToSph = VSub(movePos, targetPos_Start);
		VECTOR Cap1ToCap2 = VSub(targetPos_End, targetPos_Start);
		VECTOR normal = VNorm(Cap1ToCap2);
		float s = VDot(Cap1ToSph, normal);
		// 球からカプセルへの線上最近点
		VECTOR point = VGet(targetPos_Start.x + (normal.x * s), targetPos_Start.y + (normal.y * s), targetPos_Start.z + (normal.z * s));

		float temp = VSize(VSub(point, targetPos_Start)) / VSize(VSub(targetPos_End, targetPos_Start));

		float distance;


		if (temp < 0) // 球からカプセル線分に垂線をおろせず、targetPos_Startに近い場所
		{
			distance = VSize(VSub(point, targetPos_Start));
		}
		else if (temp > 1) // 球からカプセル線分に垂線をおろせず、targetPos_Endに近い場所
		{
			distance = VSize(VSub(point, targetPos_End));
		}
		else // 球からカプセル線分に垂線をおろせる
		{
			distance = VSize(VSub(point, movePos));
		}



		// 描画
		// カプセル描画
		DrawCapsule3D(targetPos_Start, targetPos_End, r, 32, 0xffffff,0xffffff,true);
		// 球描画
		if (distance < r * 2) // 当たっているとき
		{
			DrawSphere3D(movePos, r, 32, 0xff0000, 0xff0000, true);
		}
		else // 当たっていないとき
		{
			DrawSphere3D(movePos, r, 32, 0xffffff, 0xff0000, true);
		}


		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
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


