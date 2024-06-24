#pragma once
#include "DxLib.h"
#include<memory>

class PlayerBase
{
public:
	PlayerBase():
		PlayerSpeed(0.0f),
		PlayerGraph(0),
		PlayerMoveFlag(true),
		PlayerX(0.0f),
		PlayerY(0.0f),
		PlayerZ(0.0f)
	{}
	virtual ~PlayerBase(){}

	//virtualで継承先を呼び出す

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;

	//Playerのスピード
	float PlayerSpeed;
	//Playerの3Dモデルハンドル
	int PlayerGraph;

	//Playerが動けるフラグ
	bool PlayerMoveFlag;

	//PlayerのX,Y,Z座標
	float PlayerX, PlayerY, PlayerZ;
};

