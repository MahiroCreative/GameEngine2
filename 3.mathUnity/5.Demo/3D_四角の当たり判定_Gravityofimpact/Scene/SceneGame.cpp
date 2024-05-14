#include "SceneGame.h"
#include "SceneGoal.h"
#include "DxLib.h"

SceneGame::SceneGame()
{
}

SceneGame::~SceneGame()
{
	//ƒƒ‚ƒŠ‰ğ•ú
	DeleteSoundMem(SoundGame);
}

void SceneGame::Init()
{
	player->Init();

	camera->Init();

	map->Init();

	//”wŒi‚Ì‰æ‘œ“Ç‚İ‚İ
	GameBack = LoadGraph("data/cloudy.png");

	//”wŒiBGM“Ç‚İ‚İ
	SoundGame = LoadSoundMem("BGMESE/Garden_Farm.mp3");
}

std::shared_ptr<SceneBase> SceneGame::Update()
{
	player->Update();

	camera->Update(*player);

	map->Update(*player);

	//ƒTƒEƒ“ƒhÄ¶
	PlaySoundMem(SoundGame, DX_PLAYTYPE_LOOP, FALSE);

	//ƒS[ƒ‹ƒV[ƒ“‚É‘JˆÚ‚·‚é
	if (map->Goal == true)
	{
		return std::make_shared<SceneGoal>();
	}

	return shared_from_this();
}

void SceneGame::Draw()
{
	//”wŒi‚ğ•`‰æ
	DrawGraph(0, 0, GameBack, false);

	map->Draw(*player);

	player->Draw();

	camera->Draw();
}

void SceneGame::End()
{
	//“Ç‚İ‚ñ‚¾‰æ‘œƒf[ƒ^‰ğ•ú
	DeleteGraph(GameBack);

	map->End();

	player->End();

	camera->End();
}
