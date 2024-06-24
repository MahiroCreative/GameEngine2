#pragma once
#include "DxLib.h"
class SceneFedo
{
public:
	SceneFedo();
	virtual ~SceneFedo();

	void Init();
	void Update();
	void Draw();
	void End();

	//フェードイン,フェードアウトさせるための変数
	int Start;

	//フェードイン、フェードアウト開始させるための変数
	bool Fedo;
};

