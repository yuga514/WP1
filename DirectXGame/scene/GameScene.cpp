#include <cassert>

#include "GameScene.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(title);
	safe_delete(HP5);
	safe_delete(HP4);
	safe_delete(HP3);
	safe_delete(HP2);
	safe_delete(HP1);
	safe_delete(HP0);
	safe_delete(background1);
	safe_delete(background2);
	safe_delete(background3);
	safe_delete(background4);
	safe_delete(gameclear);
	safe_delete(gameover);
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
	Sprite::LoadTexture(2, L"Resources/HP5.png");
	Sprite::LoadTexture(3, L"Resources/HP4.png");
	Sprite::LoadTexture(4, L"Resources/HP3.png");
	Sprite::LoadTexture(5, L"Resources/HP2.png");
	Sprite::LoadTexture(6, L"Resources/HP1.png");
	Sprite::LoadTexture(7, L"Resources/HP0.png");
	Sprite::LoadTexture(8, L"Resources/background1.png");
	Sprite::LoadTexture(9, L"Resources/background2.png");
	Sprite::LoadTexture(10, L"Resources/background3.png");
	Sprite::LoadTexture(11, L"Resources/background4.png");
	Sprite::LoadTexture(12, L"Resources/gameclear.png");
	Sprite::LoadTexture(13, L"Resources/gameover.png");

	// スプライト生成
	debugText.Initialize(debugTextTexNumber);
	title = Sprite::Create(1, { 0.0f,0.0f }, { 2,2,2,1 });
	HP5 = Sprite::Create(2, { 0.0f,0.0f }, { 2,2,2,1 });
	HP4 = Sprite::Create(3, { 0.0f,0.0f }, { 2,2,2,1 });
	HP3 = Sprite::Create(4, { 0.0f,0.0f }, { 2,2,2,1 });
	HP2 = Sprite::Create(5, { 0.0f,0.0f }, { 2,2,2,1 });
	HP1 = Sprite::Create(6, { 0.0f,0.0f }, { 2,2,2,1 });
	HP0 = Sprite::Create(7, { 0.0f,0.0f }, { 2,2,2,1 });
	background1 = Sprite::Create(8, { 0.0f,0.0f });
	background2 = Sprite::Create(9, { 0.0f,0.0f });
	background3 = Sprite::Create(10, { 0.0f,0.0f });
	background4 = Sprite::Create(11, { 0.0f,0.0f });
	gameclear = Sprite::Create(12, { 0.0f,0.0f }, { 2,2,2,1 });
	gameover = Sprite::Create(13, { 0.0f,0.0f }, { 2,2,2,1 });

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
		gameover->Draw();
		break;
	}

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
		HP5->Draw();
		break;
	case 2:
		if (HP == 5) { HP5->Draw(); }
		if (HP == 4) { HP4->Draw(); }
		if (HP == 3) { HP3->Draw(); }
		if (HP == 2) { HP2->Draw(); }
		if (HP == 1) { HP1->Draw(); }
		if (HP == 0) { HP0->Draw(); }
		break;
	case 3:
		if (HP == 5) { HP5->Draw(); }
		if (HP == 4) { HP4->Draw(); }
		if (HP == 3) { HP3->Draw(); }
		if (HP == 2) { HP2->Draw(); }
		if (HP == 1) { HP1->Draw(); }
		if (HP == 0) { HP0->Draw(); }
		break;
	case 4:
		if (HP == 5) { HP5->Draw(); }
		if (HP == 4) { HP4->Draw(); }
		if (HP == 3) { HP3->Draw(); }
		if (HP == 2) { HP2->Draw(); }
		if (HP == 1) { HP1->Draw(); }
		if (HP == 0) { HP0->Draw(); }
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

// 当たり判定
void GameScene::Collision()
{
	if (scene == 2) {
		// エネミーの当たり判定
		XMFLOAT3 PlayerPosition = stageOnePlayer->GetPlayerPosition();
		XMFLOAT3 EnemyPosition1 = stageOnePlayer->GetEnemyPosition1();
		unsigned int a = stageOnePlayer->GetDamageCount();

		/*if (EnemyPosition1.x - 2 < PlayerPosition.x && PlayerPosition.x <
			EnemyPosition1.x + 2 && PlayerPosition.y < 3 && brownEnemyFlag[0] == 0) {
			if (stageOnePlayer->GetAttackFlag() == 0 && stageOnePlayer->GetDamageCount() == 0) {
				damageCount = 60;
			}
			if (0 < attackFlag) {
				brownEnemyFlag[0] = 1;
			}
		}*/
		if (a < 60) {
			HP--;
		}
	}
	if (scene == 4) {
		// エネミーの当たり判定
		XMFLOAT3 PlayerPosition = stageThreePlayer->GetPlayerPosition();
		XMFLOAT3 EnemyPosition = stageThreePlayer->GetBossPosition();
		if (EnemyPosition.x - 3 < PlayerPosition.x && PlayerPosition.x <
			EnemyPosition.x + 3 && PlayerPosition.y < 4 && input->TriggerKey(DIK_X)) {
			bossHP--;
		}
	}
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
		XMFLOAT3 PlayerPosition = tutorialPlayer->GetPlayerPosition();
		if (input->TriggerKey(DIK_UP) && 88 < PlayerPosition.x && PlayerPosition.x < 92 && PlayerPosition.y < 4) {
			scene = 2;
		}
	}
	if (scene == 2) {
		XMFLOAT3 PlayerPosition = stageOnePlayer->GetPlayerPosition();
		if (input->TriggerKey(DIK_UP) && 88 < PlayerPosition.x && PlayerPosition.x < 92 && PlayerPosition.y < 4) {
			scene = 3;
		}
	}
	if (scene == 3) {
		XMFLOAT3 PlayerPosition = stageTwoPlayer->GetPlayerPosition();
		if (input->TriggerKey(DIK_UP) && 37 < PlayerPosition.x && PlayerPosition.x < 41 && PlayerPosition.y < 4) {
			scene = 4;
		}
	}
	if (scene == 4) {
		if (bossHP == 0) {
			scene = 5;
		}
	}
}

// チュートリアルのカメラをセット
void GameScene::CameraMove()
{
	if (scene == 1) {
		XMFLOAT3 CameraPosition = tutorialPlayer->GetCameraTarget();
		camera->SetTarget(CameraPosition);
	}
	if (scene == 2) {
		XMFLOAT3 CameraPosition = stageOnePlayer->GetCameraTarget();
		camera->SetTarget(CameraPosition);
	}
	if (scene == 3) {
		XMFLOAT3 CameraPosition = stageTwoPlayer->GetCameraTarget();
		camera->SetTarget(CameraPosition);
	}
	if (scene == 4) {
		XMFLOAT3 CameraPosition = stageThreePlayer->GetCameraTarget();
		camera->SetTarget(CameraPosition);
	}
}