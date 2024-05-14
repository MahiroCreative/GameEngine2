#include "SceneFedo.h"

SceneFedo::SceneFedo():
	Start(0),
	Fedo(false)
{
}

SceneFedo::~SceneFedo()
{
}

void SceneFedo::Init()
{
	Start = 0;
	Fedo = false;
}

void SceneFedo::Update()
{
	//フェードアウトさせる
	if (Fedo == true)
	{
		if (Start >= 0) Start--;
	}
	//フェードインさせる
	else if (Fedo == false)
	{
		if (Start >= 0 && 256) Start++;
	}
	
}

void SceneFedo::Draw()
{
	SetDrawBright(Start, Start, Start);
}

void SceneFedo::End()
{
}
