#include "StageThreePlayer.h"

// コンストラクタ
StageThreePlayer::StageThreePlayer()
{
}

// デストラクタ
StageThreePlayer::~StageThreePlayer()
{
	safe_delete(modelPlayerRight);
	safe_delete(modelPlayerLeft);
	safe_delete(modelAttack1);
	safe_delete(modelAttack2);
	safe_delete(modelBossBrownEnemy);
	safe_delete(objPlayerRight);
	safe_delete(objPlayerLeft);
	safe_delete(objAttack1);
	safe_delete(objAttack2);
	safe_delete(objBossBrownEnemy);
}

// 初期化
void StageThreePlayer::Initialize(Input* input)
{
	this->input = input;

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// カメラ注視点をセット
	camera->SetDistance(3.0f);

	// モデル読み込み
	modelPlayerRight = Model::CreateFromOBJ("playerRight");
	modelPlayerLeft = Model::CreateFromOBJ("playerLeft");
	modelAttack1 = Model::CreateFromOBJ("attack1");
	modelAttack2 = Model::CreateFromOBJ("attack2");
	modelBossBrownEnemy = Model::CreateFromOBJ("bossBrownEnemy");

	// 3Dオブジェクト生成
	objPlayerRight = Object3d::Create(modelPlayerRight);
	objPlayerLeft = Object3d::Create(modelPlayerLeft);
	objAttack1 = Object3d::Create(modelAttack1);
	objAttack2 = Object3d::Create(modelAttack2);
	objBossBrownEnemy = Object3d::Create(modelBossBrownEnemy);
}

// 更新
void StageThreePlayer::Update()
{
	// ゲッター
	Getter();

	// プレイヤーのアクション
	PlayerAction();

	// エネミーのアクション
	EnemyAction();

	// 当たり判定
	Collision();

	// セッター
	Setter();

	// アップデート
	camera->Update();

	objPlayerRight->Update();
	objPlayerLeft->Update();
	objAttack1->Update();
	objAttack2->Update();
	objBossBrownEnemy->Update();
}

// 描画
void StageThreePlayer::Draw()
{
	if (direction == 0) {
		objPlayerRight->Draw();
	}
	if (direction == 1) {
		objPlayerLeft->Draw();
	}
	if (attackFlag == 1) {
		objAttack1->Draw();
	}
	if (attackFlag == 2) {
		objAttack2->Draw();
	}
	objBossBrownEnemy->Draw();
}

// ゲッター
void StageThreePlayer::Getter()
{
	// ゲットターゲット
	camera->GetTarget();

	// ゲットポジション
	objPlayerRight->GetPosition();
	objPlayerLeft->GetPosition();
	objAttack1->GetPosition();
	objAttack2->GetPosition();
	objBossBrownEnemy->GetPosition();

	// ゲットローテーション
	objPlayerRight->GetRotation();
	objPlayerLeft->GetRotation();
	objBossBrownEnemy->GetRotation();

	// ゲットスケール
	objPlayerRight->GetScale();
	objPlayerLeft->GetScale();
}

// セッター
void StageThreePlayer::Setter()
{
	// セットターゲット
	camera->SetTarget(CameraPosition);

	// セットポジション
	objPlayerRight->SetPosition(PlayerPosition);
	objPlayerLeft->SetPosition(PlayerPosition);
	objAttack1->SetPosition(PlayerPosition);
	objAttack2->SetPosition(PlayerPosition);
	objBossBrownEnemy->SetPosition(BossBrownEnemyPosition);

	// セットローテーション
	objPlayerRight->SetRotation(PlayerRotation);
	objPlayerLeft->SetRotation(PlayerRotation);
	objBossBrownEnemy->SetRotation(BossEnemyRotation);

	// セットスケール
	objPlayerRight->SetScale(PlayerScale);
	objPlayerLeft->SetScale(PlayerScale);
}

// プレイヤーのアクション
void StageThreePlayer::PlayerAction()
{
	// 落下処理
	PlayerPosition.y -= jumpPower;

	// 落下加速度を加える
	jumpPower += 0.01f;

	// 右移動
	if (input->PushKey(DIK_RIGHT)) {
		PlayerPosition.x += speed;
		PlayerRotation.z -= 3.6f;
		direction = 0;
	}

	// 左移動
	if (input->PushKey(DIK_LEFT)) {
		PlayerPosition.x -= speed;
		PlayerRotation.z += 3.6f;
		direction = 1;
	}

	// ダッシュ
	if (input->PushKey(DIK_X) && jumpCount == 0 || input->PushKey(DIK_X) && jumpCount == 3) {
		speed = 0.2f;
	}
	if (input->PushKey(DIK_X) == 0 && jumpCount == 0 || input->PushKey(DIK_X) == 0 && jumpCount == 3) {
		speed = 0.1f;
	}

	// 0段目の地面についていたら止まる
	if (PlayerPosition.y < 0) {
		PlayerPosition.y = 0.0f;
		Land();
	}

	// ジャンプ
	if (input->TriggerKey(DIK_Z) && jumpCount < 2 && speed == 0.2f) {
		jumpCount += 1;
		jumpPower = -0.35f;
	}
	else if (input->TriggerKey(DIK_Z) && jumpCount < 2 && speed == 0.1f) {
		jumpCount += 1;
		jumpPower = -0.3f;
	}
	if (jumpCount == 2) {
		if (direction == 0) {
			PlayerRotation.z -= 36.0f;
		}
		if (direction == 1) {
			PlayerRotation.z += 36.0f;
		}
	}

	// 攻撃
	if (input->TriggerKey(DIK_X) && input->PushKey(DIK_DOWN) && jumpCount == 2 && attackFlag == 0) {
		attackFlag = 2;
	}
	else if (input->TriggerKey(DIK_X) && attackFlag == 0) {
		attackFlag = 1;
	}
	if (attackFlag == 1) {
		PlayerRotation.y += 36.0f;
		PlayerRotation.z = 0.0f;
		if (PlayerRotation.y == 360) {
			PlayerRotation.y = 0.0f;
			attackFlag = 0;
		}
	}
	if (attackFlag == 2) {
		PlayerRotation.y += 36.0f;
		PlayerPosition.y -= 1.0f;
		PlayerRotation.z = 0.0f;
	}

	// プレイヤーが凹んでいたら
	if (PlayerScale.y < 1) {
		PlayerScale.x -= 0.1f;
		PlayerScale.y += 0.1f;
		PlayerScale.z -= 0.1f;
	}
}

// エネミーのアクション
void StageThreePlayer::EnemyAction()
{
	// 左移動
	if (bossBrownEnemyMoveFlag == 0) {
		BossBrownEnemyPosition.x -= 0.2f;
	}
	// 右移動
	if (bossBrownEnemyMoveFlag == 1) {
		BossBrownEnemyPosition.x += 0.2f;
	}

	// 方向転換
	if (BossBrownEnemyPosition.x < 0) {
		bossBrownEnemyMoveFlag = 1;
	}
	if (42 < BossBrownEnemyPosition.x) {
		bossBrownEnemyMoveFlag = 0;
	}

	// 回転
	BossEnemyRotation.y += 3.6f;
	if (BossEnemyRotation.y == 360) {
		BossEnemyRotation.y = 0.0f;
	}
}

// 当たり判定
void StageThreePlayer::Collision()
{
	// 画面外に出ないようにする
	if (PlayerPosition.x < 0) {
		PlayerPosition.x = 0.0f;
	}
	if (42 < PlayerPosition.x) {
		PlayerPosition.x = 42.0f;
	}
}

// 通常ブロックの着地
void StageThreePlayer::Land()
{
	if (jumpCount == 2) {
		PlayerRotation.z = 0.0f;
	}
	if (attackFlag == 2) {
		PlayerRotation.y = 0.0f;
		PlayerScale = { 1.9f, 0.1f, 1.9f };
		attackFlag = 0;
	}
	jumpPower = 0.0f;
	jumpCount = 0;
}