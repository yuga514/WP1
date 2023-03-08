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
	if (scene == 1) {
		// 再生
		audio->SoundPlayWave("bgm.wav", true);

		tutorialPlayer->Update();
		tutorialMap->Update();
	}
	if (scene == 2) {
		stageOnePlayer->Update();
		stageOneMap->Update();
	}
	if (scene == 3) {
		stageTwoPlayer->Update();
		stageTwoMap->Update();
	}
	if (scene == 4) {
		stageThreePlayer->Update();
		stageThreeMap->Update();
		if (input->PushKey(DIK_SPACE)) {
			bossHP = 0;
		}
	}
	if (scene == 5) {
		audio->SoundStop("bgm.wav");
	}
	// 当たり判定
	Collision();
	// シーンチェンジ
	SceneChange();
	// カメラのセット
	SetCameraTarget();
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

	if (scene == 0) { title->Draw(); }
	if (scene == 1) { background1->Draw(); }
	if (scene == 2) { background2->Draw(); }
	if (scene == 3) { background3->Draw(); }
	if (scene == 4) { background4->Draw(); }
	if (scene == 5) { gameclear->Draw(); }
	if (scene == 6) { gameover->Draw(); }

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D描画
	// 3Dオブジェクトの描画
	Object3d::PreDraw(cmdList);

	if (scene == 1) {
		tutorialMap->Draw();
		tutorialPlayer->Draw();
	}
	if (scene == 2) {
		stageOneMap->Draw();
		stageOnePlayer->Draw();
	}
	if (scene == 3) {
		stageTwoMap->Draw();
		stageTwoPlayer->Draw();
	}
	if (scene == 4) {
		stageThreeMap->Draw();
		stageThreePlayer->Draw();
	}

	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	if (0 < scene && scene < 5) {
		if (HP == 5) { HP5->Draw(); }
		if (HP == 4) { HP4->Draw(); }
		if (HP == 3) { HP3->Draw(); }
		if (HP == 2) { HP2->Draw(); }
		if (HP == 1) { HP1->Draw(); }
		if (HP == 0) { HP0->Draw(); }
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
		XMFLOAT3 PlayerPosition = stageOnePlayer->GetPlayerPosition();
		XMFLOAT3 EnemyPosition[3] = { stageOnePlayer->GetEnemyPosition1(),
			stageOnePlayer->GetEnemyPosition2(),stageOnePlayer->GetEnemyPosition3() };
		// 初期値を設定
		if (EnemyPosition[0].x == 0) {
			EnemyPosition[0] = { 27, 0, 0 };
			EnemyPosition[1] = { 45, 12, 0 };
			EnemyPosition[2] = { 63, 0, 0 };
		}

		// エネミーの当たり判定
		if (EnemyPosition[0].x - 2 < PlayerPosition.x && PlayerPosition.x < EnemyPosition[0].x + 2 &&
			PlayerPosition.y < 3 && stageOnePlayer->GetEnemyFlag1() == 0 &&
			stageOnePlayer->GetAttackFlag() == 0 && damageCount == 0) {
			damageCount = 120;
		}
		if (EnemyPosition[1].x - 2 < PlayerPosition.x && PlayerPosition.x < EnemyPosition[1].x + 2 &&
			PlayerPosition.y < 15 && stageOnePlayer->GetEnemyFlag2() == 0 &&
			stageOnePlayer->GetAttackFlag() == 0 && damageCount == 0) {
			damageCount = 120;
		}
		if (EnemyPosition[2].x - 2 < PlayerPosition.x && PlayerPosition.x < EnemyPosition[2].x + 2 &&
			PlayerPosition.y < 3 && stageOnePlayer->GetEnemyFlag3() == 0 &&
			stageOnePlayer->GetAttackFlag() == 0 && damageCount == 0) {
			damageCount = 120;
		}

		// HPを減らす
		if (damageCount == 120) {
			HP--;
		}
		// ダメージカウントを減らす
		if (0 < damageCount) {
			damageCount--;
		}
	}

	if (scene == 4) {
		XMFLOAT3 PlayerPosition = stageThreePlayer->GetPlayerPosition();
		XMFLOAT3 EnemyPosition = stageThreePlayer->GetBossPosition();
		// エネミーの当たり判定
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
		if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(0)) {
			scene = 1;
		}
	}
	if (scene == 1) {
		XMFLOAT3 PlayerPosition = tutorialPlayer->GetPlayerPosition();
		Input::StickMove stickMove = input->GetStickMove();
		if (input->TriggerKey(DIK_UP) && 88 < PlayerPosition.x && PlayerPosition.x < 92 && PlayerPosition.y < 4 ||
			stickMove.lY == 0 && 88 < PlayerPosition.x && PlayerPosition.x < 92 && PlayerPosition.y < 4) {
			scene = 2;
		}
	}
	if (scene == 2) {
		XMFLOAT3 PlayerPosition = stageOnePlayer->GetPlayerPosition();
		Input::StickMove stickMove = input->GetStickMove();
		if (input->TriggerKey(DIK_UP) && 88 < PlayerPosition.x && PlayerPosition.x < 92 && PlayerPosition.y < 4 ||
			stickMove.lY == 0 && 88 < PlayerPosition.x && PlayerPosition.x < 92 && PlayerPosition.y < 4) {
			scene = 3;
		}
	}
	if (scene == 3) {
		XMFLOAT3 PlayerPosition = stageTwoPlayer->GetPlayerPosition();
		Input::StickMove stickMove = input->GetStickMove();
		if (input->TriggerKey(DIK_UP) && 37 < PlayerPosition.x && PlayerPosition.x < 41 && PlayerPosition.y < 4 ||
			stickMove.lY == 0 && 37 < PlayerPosition.x && PlayerPosition.x < 41 && PlayerPosition.y < 4) {
			scene = 4;
		}
	}
	if (scene == 4) {
		if (bossHP == 0) {
			scene = 5;
		}
	}
	// 死んだら
	if (HP == 0) {
		if (scene == 2) { stageOnePlayer->SetDeathFlag(); }
		audio->SoundStop("bgm.wav");
	}
	if (stageOnePlayer->GetDeathFlag() == 1 && damageCount == 0) {
		scene = 6;
	}
}

// カメラのセット
void GameScene::SetCameraTarget()
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