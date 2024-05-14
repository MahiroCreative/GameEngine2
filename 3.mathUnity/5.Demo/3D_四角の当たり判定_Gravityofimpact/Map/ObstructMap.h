#pragma once
#define _OBSTRUCT_MAP_H_

#include "DxLib.h"

class ObstructMap
{
public:
	ObstructMap();   //コンストラクタ
	virtual ~ObstructMap();   //デストラクタ

	void Update();    //更新
	void Draw();      //描画

	//モデルハンドルの取得
	int GetModelHandle() { return modelHandle; }

	//ポジションのgetter/setter
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

private:
	int modelHandle;  //モデルハンドル
	VECTOR pos;       //ポジション
};
