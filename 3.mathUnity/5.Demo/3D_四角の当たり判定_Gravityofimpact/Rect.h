#pragma once
#include "Vec3.h"
#include "DxLib.h"

class Rect
{
public:
	Rect();
	virtual ~Rect();

	//中心座標と幅高さと奥行を指定
	void SetCenter(float x, float y, float z, float width, float height, float depth);

	//矩形同士の当たり判定
	bool IsCollision(const Rect& rect);

	// 描画
	void Draw(unsigned int color, bool isFill);

	//左上の座標
	VECTOR pos1;
	//左下の座標
	VECTOR pos2;
	//右上の座標
	VECTOR pos3;
	//右下の座標
	VECTOR pos4;
	//後ろの左上
	VECTOR pos5;
	//後ろの左下
	VECTOR pos6;
	//後ろの右上
	VECTOR pos7;
	//後ろの右下
	VECTOR pos8;

private:

	//代入するための変数
	float X;
	float Y;
	float Z;
	float Xwidth;
	float Yheight;
	float Zdepth;
};

