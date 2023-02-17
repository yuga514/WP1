#include <cassert>

#include "GameScene.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(title);
	safe_delete(background1);
	safe_delete(background2);
	safe_delete(background3);
	safe_delete(background4);
	safe_delete(gameclear);
	safe_delete(tutorialPlayer);
	safe_delete(tutorialMap);
	safe_delete(stageOnePlayer);
	safe_delete(stageOneMap);
	safe_delete(stageTwoPlayer);
	safe_delete(stageTwoMap);
	safe_delete(stageThreePlayer);
	safe_delete(stageThreeMap);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	Sprite::LoadTexture(1, L"Resources/title.png");
	Sprite::LoadTexture(2, L"Resources/background1.png");
	Sprite::LoadTexture(3, L"Resources/background2.png");
	Sprite::LoadTexture(4, L"Resources/background3.png");
	Sprite::LoadTexture(5, L"Resources/background4.png");
	Sprite::LoadTexture(6, L"Resources/gameclear.png");

	// スプライト生成
	debugText.Initialize(debugTextTexNumber);
	title = Sprite::Create(1, { 0.0f,0.0f }, { 2,2,2,1 });
	background1 = Sprite::Create(2, { 0.0f,0.0f });
	background2 = Sprite::Create(3, { 0.0f,0.0f });
	background3 = Sprite::Create(4, { 0.0f,0.0f });
	background4 = Sprite::Create(5, { 0.0f,0.0f });
	gameclear = Sprite::Create(6, { 0.0f,0.0f }, { 2,2,2,1 });

	// サウンド読み込み
	audio->SoundLoadWave("bgm.wav");

	// チュートリアルプレイヤー生成
	tutorialPlayer = new TutorialPlayer();
	tutorialPlayer->Initialize(input);
	// チュートリアルマップ生成
	tutorialMap = new TutorialMap();
	tutorialMap->Initialize();
	// ステージ1プレイヤー生成
	stageOnePlayer = new StageOnePlayer();
	stageOnePlayer->Initialize(input);
	// ステージ1マップ生成
	stageOneMap = new StageOneMap();
	stageOneMap->Initialize();
	// ステージ2プレイヤー生成
	stageTwoPlayer = new StageTwoPlayer();
	stageTwoPlayer->Initialize(input);
	// ステージ2マップ生成
	stageTwoMap = new StageTwoMap();
	stageTwoMap->Initialize();
	// ステージ3プレイヤー生成
	stageThreePlayer = new StageThreePlayer();
	stageThreePlayer->Initialize(input);
	// ステージ3マップ生成
	stageThreeMap = new StageThreeMap();
	stageThreeMap->Initialize();

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	// カメラ注視点をセット
	camera->SetDistance(3.0f);
}

void GameScene::Update()
{
	switch (scene)
	{
	case 0:
		break;
	case 1:
		// 再生
		audio->SoundPlayWave("bgm.wav", true);
		// アップデート
		tutorialPlayer->Update();
		tutorialMap->Update();
		break;
	case 2:
		// アップデート
		stageOnePlayer->Update();
		stageOneMap->Update();
		break;
	case 3:
		// アップデート
		stageTwoPlayer->Update();
		stageTwoMap->Update();
		break;
	case 4:
		// アップデート
		stageThreePlayer->Update();
		stageThreeMap->Update();
		break;
	case 5:
		audio->SoundStop("bgm.wav");
		break;
	case 6:
		break;
	}
	// カメラ移動
	CameraMove();
	// シーンチェンジ
	SceneChange();
	// アップデート
	camera->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	switch (scene)
	{
	case 0:
		title->Draw();
		break;
	case 1:
		background1->Draw();
		break;
	case 2:
		background2->Draw();
		break;
	case 3:
		background3->Draw();
		break;
	case 4:
		background4->Draw();
		break;
	case 5:
		gameclear->Draw();
		break;
	case 6:
		break;
	}
	//background1->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D描画
	// 3Dオブジェクトの描画
	Object3d::PreDraw(cmdList);

	switch (scene)
	{
	case 0:
		break;
	case 1:
		tutorialPlayer->Draw();
		tutorialMap->Draw();
		break;
	case 2:
		stageOnePlayer->Draw();
		stageOneMap->Draw();
		break;
	case 3:
		stageTwoPlayer->Draw();
		stageTwoMap->Draw();
		break;
	case 4:
		stageThreePlayer->Draw();
		stageThreeMap->Draw();
		break;
	case 5:
		break;
	case 6:
		break;
	}

	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	switch (scene)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	}

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

// シーンチェンジ
void GameScene::SceneChange()
{
	if (scene == 0) {
		if (input->TriggerKey(DIK_SPACE)) {
			scene = 1;
		}
	}
	if (scene == 1) {
		XMFLOAT3 PlayerPosition = tutorialPlayer->GetPosition();
		if (input->TriggerKey(DIK_UP) && 88 < PlayerPosition.x && PlayerPosition.x < 92 && PlayerPosition.y < 4) {
			scene = 2;
		}
	}
	if (scene == 2) {
		XMFLOAT3 PlayerPosition = stageOnePlayer->GetPosition();
		if (input->TriggerKey(DIK_UP) && 88 < PlayerPosition.x && PlayerPosition.x < 92 && PlayerPosition.y < 4) {
			scene = 3;
		}
	}
	if (scene == 3) {
		XMFLOAT3 PlayerPosition = stageTwoPlayer->GetPosition();
		if (input->TriggerKey(DIK_UP) && 37 < PlayerPosition.x && PlayerPosition.x < 41 && PlayerPosition.y < 4) {
			scene = 4;
		}
	}
	if (scene == 4) {
		// エネミーの当たり判定
		XMFLOAT3 PlayerPosition = stageThreePlayer->GetPosition();
		XMFLOAT3 EnemyPosition = stageThreePlayer->GetPosition2();
		if (EnemyPosition.x - 3 < PlayerPosition.x && PlayerPosition.x <
			EnemyPosition.x + 3 && PlayerPosition.y < 4 && input->TriggerKey(DIK_X)) {
			bossFlag++;
		}
		if (bossFlag == 15) {
			scene = 5;
		}
	}
}

// チュートリアルのカメラをセット
void GameScene::CameraMove()
{
	if (scene == 1) {
		XMFLOAT3 CameraPosition = tutorialPlayer->GetTarget();
		camera->SetTarget(CameraPosition);
	}
	if (scene == 2) {
		XMFLOAT3 CameraPosition = stageOnePlayer->GetTarget();
		camera->SetTarget(CameraPosition);
	}
	if (scene == 3) {
		XMFLOAT3 CameraPosition = stageTwoPlayer->GetTarget();
		camera->SetTarget(CameraPosition);
	}
	if (scene == 4) {
		XMFLOAT3 CameraPosition = stageThreePlayer->GetTarget();
		camera->SetTarget(CameraPosition);
	}
}