#include "Player.h"
#include<math.h>
//重力加速度
#define GravitationalAcceleration 9.80665 / 2

#define D2R(deg) ((deg)*DX_PI_F/180.0f)

Player::Player():
	PlayerGravity(0.0f),
	Playerweight(0.0f),
	PlayerRespawn(0.0f)
{
}

Player::~Player()
{
	MV1DeleteModel(PlayerGraph);
}

void Player::Init()
{
	//Playerの初期座標
	PlayerX = 0.0f;
	PlayerY = 30.0f;
	PlayerZ = 0.0f;

	//Playerの重さ
	Playerweight = 1.0f;

	//Playerの重力
	PlayerGravity = Playerweight * static_cast<float>(GravitationalAcceleration);

	//Playerの初期位置
	Playerpos = VGet(PlayerX, PlayerY, PlayerZ);

	//Playerの回転状態初期化
	PlayerAngle = VGet(-1.55f, D2R(0.0f), 0.0f);

	//3Dモデルを読み込む
	PlayerGraph = MV1LoadModel("data/Sword.mv1");

	//Playerの大きさを変える
	MV1SetScale(PlayerGraph, VGet(0.05f, 0.05f, 0.05f));

	//Playerのスピード設定
	PlayerSpeed = 1.0f;

	//Playerがリスポーンできる地点
	PlayerRespawn = -7500.0f;

	//Playerが動けるように初期化
	PlayerMoveFlag = true;
}

void Player::Update()
{
	//Playerが動くフラグがTrueなら
	if (PlayerMoveFlag == true)
	{
		//前に進む
		if (CheckHitKey(KEY_INPUT_W))
		{
			Playerpos.z += PlayerSpeed;

		}
		//後ろに進む
		if (CheckHitKey(KEY_INPUT_S))
		{
			Playerpos.z -= PlayerSpeed;

		}
		//右に進む
		if (CheckHitKey(KEY_INPUT_D))
		{
			Playerpos.x += PlayerSpeed;
		}
		//左に進む
		if (CheckHitKey(KEY_INPUT_A))
		{
			Playerpos.x -= PlayerSpeed;
		}
	}

	//Playerに重力を与え続ける
	Playerpos.y -= PlayerGravity;

	//Playerが落ち続けたら初期位置に戻す
	if (Playerpos.y <= PlayerRespawn)
	{
		Playerpos.x = 0.0f;
		Playerpos.y = 30.0f;
		Playerpos.z = 0.0f;
	}

	m_colrect.SetCenter(Playerpos.x - static_cast<float>(5), Playerpos.y, Playerpos.z + static_cast<float>(5), 10.0f, 1.0f, -60.0f);
}

void Player::Draw()
{
	//3Dモデルのポジション設定
	MV1SetPosition(PlayerGraph, Playerpos);

	//3Dモデルの回転地をセットする
	MV1SetRotationXYZ(PlayerGraph, PlayerAngle);

	//3Dモデルを描画する
	MV1DrawModel(PlayerGraph);
}

void Player::End()
{
}
