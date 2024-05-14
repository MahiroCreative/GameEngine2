#pragma once
#include "PlayerBase.h"
#include "Rect.h"

class Player : public PlayerBase
{
public:
	Player();
	virtual ~Player();

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void End();

	//Playerの重さ
	float Playerweight;

	//Playerの重力
	float PlayerGravity;

	//Plyaerのリスポーン値
	float PlayerRespawn;

	//Playerのポジション
	VECTOR Playerpos = VGet(0.0f, 10.0f, 0.0f);

	//Playerのアングル
	VECTOR PlayerAngle = VGet(0.0f, 0.0f, 0.0f);

	//当たり判定
	Rect m_colrect;
};

