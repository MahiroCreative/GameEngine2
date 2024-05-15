#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneGame.h"

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
	//メモリから解放
	DeleteGraph(TitleBack);
	DeleteGraph(Titlelogo);
	DeleteSoundMem(SoundGame);
}

void SceneTitle::Init()
{
	fedo->Init();

	//背景BGM読み込み
	SoundGame = LoadSoundMem("BGM・SE/Garden_Farm.mp3");

	//背景画像読み込み
	TitleBack = LoadGraph("data/cloudy.png");

	//タイトルロゴを読み込む
	Titlelogo = LoadGraph("data/GravityImpactロゴ.png");
}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
	//フェード開始
	fedo->Update();

	//サウンド再生
	PlaySoundMem(SoundGame, DX_PLAYTYPE_LOOP, FALSE);

	//入力でシーン遷移
	if (fedo->Start >= 255)
	{
		if (CheckHitKeyAll())
		{
			return std::make_shared<SceneGame>();
		}
	}
	

	return shared_from_this();  //自身のポインタを返す
}

void SceneTitle::Draw()
{
	fedo->Draw();

	DrawGraph(0, 0, TitleBack, false);

	//タイトルロゴの初期位置
	int Titlelogox, Titlelogoy;

	Titlelogox = 0;
	Titlelogoy = -100;

	DrawString(205, 300, "Push Any Button", GetColor(255, 255, 255));

	//タイトルロゴを書く
	DrawGraph(Titlelogox, Titlelogoy, Titlelogo, true);
}

void SceneTitle::End()
{
}
