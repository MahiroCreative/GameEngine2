#include "Rect.h"
#include<cassert>

Rect::Rect():
	X(0.0f),
	Y(0.0f),
	Z(0.0f),
	Xwidth(0.0f),
	Yheight(0.0f),
	Zdepth(0.0f)
{
	//左上
	pos1 = VGet(0.0f, 0.0f, 0.0f);
	//左下
	pos2 = VGet(0.0f, 0.0f, 0.0f);
	//右上
	pos3 = VGet(0.0f, 0.0f, 0.0f);
	//右下
	pos4 = VGet(0.0f, 0.0f, 0.0f);
	//後ろの左上
	pos5 = VGet(0.0f, 0.0f, 0.0f);
	//後ろの左下
	pos6 = VGet(0.0f, 0.0f, 0.0f);
	//後ろの右上
	pos7 = VGet(0.0f, 0.0f, 0.0f);
	//後ろの右下
	pos8 = VGet(0.0f, 0.0f, 0.0f);


}

Rect::~Rect()
{
}

void Rect::SetCenter(float x, float y, float z, float width, float height, float depth)
{
	//代入する
	X = x;
	Y = y;
	Z = z;
	Xwidth = x + width;
	Yheight = y + height;
	Zdepth = z + depth;

	//左上座標
	pos1 = VGet(X, Y, Z);
	//左下座標
	pos2 = VGet(X, Yheight, Z);
	//右上座標
	pos3 = VGet(Xwidth, Y, Z);
	//右下座標
	pos4 = VGet(Xwidth, Yheight, Z);
	//後ろの左上座標
	pos5 = VGet(X, Y, Zdepth);
	//後ろの左下座標
	pos6 = VGet(X, Yheight, Zdepth);
	//後ろの右上座標
	pos7 = VGet(Xwidth, Y, Zdepth);
	//後ろの右下座標
	pos8 = VGet(Xwidth, Yheight, Zdepth);
}

bool Rect::IsCollision(const Rect& rect)
{
	//絶対当たらないパターン以外は当たっている
	if (X > rect.Xwidth ) return false;
	if (Y > rect.Yheight) return false;
	if (Xwidth < rect.X ) return false;
	if (Yheight < rect.Y ) return false;
	if (Z < rect.Zdepth) return false;
	if (Zdepth > rect.Z) return false;

	//当たらないパターン以外は当たっている
	return true;
}



void Rect::Draw(unsigned int color, bool isFill)
{
	//左上から右上
	DrawLine3D(pos1, pos3, color);
	//左上から左下
	DrawLine3D(pos1, pos2, color);
	//左上から後ろの左上
	DrawLine3D(pos1, pos5, color);
	//右上から右した
	DrawLine3D(pos3, pos4, color);
	//右上から後ろの右上
	DrawLine3D(pos3, pos7, color);
	//左下から後ろの左下
	DrawLine3D(pos2, pos6, color);
	//左下から右下
	DrawLine3D(pos2, pos4, color);
	//右下から後ろの右下
	DrawLine3D(pos4, pos8, color);
	//後ろの左上から後ろの右上
	DrawLine3D(pos5, pos7, color);
	//後ろの左上から後ろの左下
	DrawLine3D(pos5, pos6, color);
	//後ろの右下から後ろの右上
	DrawLine3D(pos8, pos7, color);
	//後ろの右下から後ろの左下
	DrawLine3D(pos8, pos6, color);
}
