#include "SceneGoal.h"
#include "SceneTitle.h"
#include "DxLib.h"

SceneGoal::SceneGoal():
	ClearGraph(0),
	Map(0),
	Player(0),
	MapX(0.0f),
	MapY(0.0f),
	MapZ(0.0f),
	PlayerX(0.0f),
	PlayerY(0.0f),
	PlayerZ(0.0f),
	SceneChange(false)
{
}

SceneGoal::~SceneGoal()
{
	//メモリ解放
	DeleteGraph(GoalBack);
	DeleteGraph(ClearGraph);
	DeleteSoundMem(SoundGoal);

}

void SceneGoal::Init()
{
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	//座標の初期化
	MapX = 0.0f;
	MapY = 50.0f;
	MapZ = 0.0f;
	PlayerX = 0.0f;
	PlayerY = 300.0f;
	PlayerZ = 5.0f;

	//フェードの初期化
	fedo->Init();

	//背景BGM読み込み
	SoundGoal = LoadSoundMem("BGM・SE/栄光のゴール.mp3");

	//Clearの画像読み込み
	ClearGraph = LoadGraph("data/Clear.png");

	//背景画像読み込み
	GoalBack = LoadGraph("data/cloudy.png");

	//3Dモデルの読み込み
	Map = MV1LoadModel("data/MapCube.mv1");
	Player = MV1LoadModel("data/Sword.mv1");

	//Playerの大きさを変える
	MV1SetScale(Player, VGet(0.05f, 0.05f, 0.05f));

	//Playerの初期位置
	PlayerPos = VGet(PlayerX, PlayerY, PlayerZ);

	//ポジション設定
	MapPos = VGet(0.0f, 50.0f, 0.0f);

	//基準となるカメラの座標
	cameraPos = VGet(0.0f, 100.0f, -30.0f);

	//カメラのターゲット座標初期化
	cameraTarget = VGet(0.0f, 5.0f, 0.0f);
}

std::shared_ptr<SceneBase> SceneGoal::Update()
{
	//フェードを行う
	fedo->Update();

	//サウンド再生
	PlaySoundMem(SoundGoal, DX_PLAYTYPE_LOOP, TRUE);

	//入力でシーン遷移
	if (CheckHitKeyAll())
	{
		//フェードアウトを行う
		fedo->Fedo = true;

		SceneChange = true;
	}

	//3Dモデルのポジション設定
	MV1SetPosition(Map, MapPos);
	MV1SetPosition(Player, PlayerPos);

	if (PlayerPos.y >= 70.0f)
	{
		PlayerPos.y -= 5.0f;
	}

	//注視点の座標はターゲットの少し上
	cameraTarget = VAdd(MapPos, VGet(0.0f, 50.0f, 0.0f));

	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);

	//シーン遷移
	if (fedo->Start <= 0 && SceneChange == true)
	{
		return std::make_shared<SceneTitle>();
	}

	return shared_from_this();  //自身のポインタを返す
}

void SceneGoal::Draw()
{
	//背景画像描画
	DrawGraph(0, 0, GoalBack, false);

	DrawGraph(0, 0, ClearGraph, true);

	//3Dモデル描画
	MV1DrawModel(Map);
	MV1DrawModel(Player);

	//フェード
	fedo->Draw();
}

void SceneGoal::End()
{
	//メモリ解放
	DeleteGraph(GoalBack);
	DeleteGraph(ClearGraph);
}
