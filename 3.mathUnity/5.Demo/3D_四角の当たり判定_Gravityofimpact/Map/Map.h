#pragma once
#include "DxLib.h"
#include "ObstructMap.h"
#include "Rect.h"
#include "Player/Player.h"

class Map
{
public:
	Map();
	virtual ~Map();

	virtual void Init();
	virtual void Update(Player& player);
	virtual void Draw(Player& player);
	virtual void End();

	//マップオブジェクト生成
	ObstructMap* obustructmap1 = new ObstructMap();
	ObstructMap* obustructmap2 = new ObstructMap();
	ObstructMap* obustructmap3 = new ObstructMap();
	ObstructMap* obustructmap4 = new ObstructMap();
	ObstructMap* obustructmap5 = new ObstructMap();
	ObstructMap* obustructmap6 = new ObstructMap();
	ObstructMap* obustructmap7 = new ObstructMap();
	ObstructMap* obustructmap8 = new ObstructMap();
	ObstructMap* obustructmap9 = new ObstructMap();
	ObstructMap* obustructmap10 = new ObstructMap();

	//Playerが動けなくなるまでの時間
	int NotMoveTime;

	//SE再生用トリガー
	bool PlaySe;

	//SE用格納用変数
	int SE;

	//他のマップとの距離
	float MapdistanceX, MapdistanceY, MapdistanceZ;

	//マップの初期位置
	float MapX, MapY, MapZ;

	//マップの当たり判定幅
	float MapWidth, MapHeight, MapDepth;

	//シーン遷移させるためのトリガー
	bool Goal;
	
	//当たり判定
	Rect m_colrect;
	Rect m_colrect2;
	Rect m_colrect3;
	Rect m_colrect4;
	Rect m_colrect5;
	Rect m_colrect6;
	Rect m_colrect7;
	Rect m_colrect8;
	Rect m_colrect9;
	Rect m_colrect10;
};

