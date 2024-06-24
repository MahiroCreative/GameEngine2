#pragma once
#include<cmath>
//3次元のベクトルを便利に使うためのクラス
class Vec3
{
public:
	float x, y, z;

	Vec3():
		x(0.0f),
		y(0.0f),
		z(0.0f)
	{}

	Vec3(float posX, float posY, float posZ):
		x(posX),
		y(posY),
		z(posZ)
	{}

	//単項演算子+ Vec3 = +Vec3
	Vec3 operator+() const
	{
		return *this;
	}

	//単項演算子- Vec3 = -Vec3
	Vec3 operator-() const
	{
		return Vec3{-x,-y,-z};
	}

	//足し算
	Vec3 operator+(Vec3 vec) const
	{
		return Vec3{ x + vec.x,y + vec.y,z + vec.z };
	}

	//Vec3 += Vec3
	Vec3 operator+=(Vec3 vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	//引き算
	Vec3 operator-(Vec3 vec) const
	{
		return Vec3{ x - vec.x, y - vec.y, z - vec.z };
	}

	//Vec3 -= Vec3
	Vec3 operator-=(Vec3 vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	//掛け算
	Vec3 operator*(Vec3 vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	//Vec3 *= float
	Vec3 operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}

	//割り算
	Vec3 operator/(float scale) const
	{
		return Vec3{ x / scale,y / scale,z / scale };
	}

	//Vec3 /= float
	Vec3 operator/=(float scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;
		return *this;
	}

	//ベクトルの長さの2乗を求める
	float sqLength() const
	{
		return x * x + y * y + z * z;
	}

	//ベクトルの長さを求める
	float length() const
	{
		return sqrtf(sqLength());
	}

	//自信の正規化を行う
	void normalize()
	{
		float len = length();
		if (len > 0.0f)
		{
			x /= len;
			y /= len;
			z /= len;
		}
		//長さ0の場合は何もしない
	}

	//自信を正規化したベクトルを取得する
	Vec3 getNormalize() const
	{
		float len = length();
		if (len > 0.0f)
		{
			return Vec3{ x / len, y / len, z / len };
			//長さ0の場合
			return Vec3{ 0.0f,0.0f,0.0f };
		}
	}
};

