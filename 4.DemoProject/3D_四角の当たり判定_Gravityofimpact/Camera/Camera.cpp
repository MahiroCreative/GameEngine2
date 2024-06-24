#include "Camera.h"
//度をラジアンに変換
#define D2R(deg) ((deg)*DX_PI_F/180.0f)


Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	//基準となるカメラの座標
	cameraPos = VGet(0.0f, 50.0f, -100.0f);

	//カメラのターゲット座標初期化
	cameraTarget = VGet(0.0f, 5.0f, 0.0f);

	//カメラのアングル初期設定
	cameraAngle = VGet(D2R(-20.0f), 0.0f, 0.0f);

	SetCameraNearFar(1.0f, 850.0f);
}

void Camera::Update(Player& player)
{

	//左キー
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	{
		cameraAngle.y += D2R(1.0f);
	}
	//右キー
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	{
		cameraAngle.y -= D2R(1.0f);
	}
	//上キー
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
	{
		//カメラがプレイヤーを超えないくらいまで
		if (cameraAngle.x <= 0.7f)
		{
			cameraAngle.x += D2R(1.0f);
		}
		
	}
	//下キー
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
	{
		//カメラがブロックにめりこまないように
		if (cameraPos.y >= 15.2f + player.Playerpos.y)
		{
			cameraAngle.x -= D2R(1.0f);
		}
		
	}

	//基準のベクトル
	VECTOR Direction = VGet(0.0f, 100.0f, -100.0f);

	//X軸回転行列
	MATRIX matrixX = MGetRotX(cameraAngle.x);
	//Y軸回転行列
	MATRIX matrixY = MGetRotY(cameraAngle.y);

	//行列の合成
	MATRIX matrix = MMult(matrixX, matrixY); 

	//基準ベクトルを行列で変換
	Direction = VTransform(Direction, matrix);

	//カメラ座標はプレイヤー座標から少しはなれたところ
	cameraPos = VAdd(player.Playerpos, Direction);

	//注視点の座標はプレイヤー座標の少し上
	cameraTarget = VAdd(player.Playerpos, VGet(0.0f, 2.0f, 0.0f));

	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
}

void Camera::Draw()
{
	
}

void Camera::End()
{
}
