#include "TutorialPlayer.h"

// コンストラクタ
TutorialPlayer::TutorialPlayer()
{
}

// デストラクタ
TutorialPlayer::~TutorialPlayer()
{
	safe_delete(modelPlayerRight);
	safe_delete(modelPlayerLeft);
	safe_delete(modelAttack1);
	safe_delete(modelAttack2);
	safe_delete(objPlayerRight);
	safe_delete(objPlayerLeft);
	safe_delete(objAttack1);
	safe_delete(objAttack2);
	safe_delete(tutorialMap);
}

// 初期化
void TutorialPlayer::Initialize(Input* input)
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

	// 3Dオブジェクト生成
	objPlayerRight = Object3d::Create(modelPlayerRight);
	objPlayerLeft = Object3d::Create(modelPlayerLeft);
	objAttack1 = Object3d::Create(modelAttack1);
	objAttack2 = Object3d::Create(modelAttack2);

	// チュートリアルマップ生成
	tutorialMap = new TutorialMap();
	tutorialMap->Initialize();
}

// 更新
void TutorialPlayer::Update()
{
	// ゲッター
	Getter();

	// プレイヤーのアクション
	PlayerAction();

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
	tutorialMap->Update();
}

// 描画
void TutorialPlayer::Draw()
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
	tutorialMap->Draw();
}

// ゲッター
void TutorialPlayer::Getter()
{
	// ゲットターゲット
	camera->GetTarget();

	// ゲットポジション
	objPlayerRight->GetPosition();
	objPlayerLeft->GetPosition();
	objAttack1->GetPosition();
	objAttack2->GetPosition();

	// ゲットローテーション
	objPlayerRight->GetRotation();
	objPlayerLeft->GetRotation();

	// ゲットスケール
	objPlayerRight->GetScale();
	objPlayerLeft->GetScale();
}

// セッター
void TutorialPlayer::Setter()
{
	// セットターゲット
	camera->SetTarget(CameraPosition);

	// セットポジション
	objPlayerRight->SetPosition(PlayerPosition);
	objPlayerLeft->SetPosition(PlayerPosition);
	objAttack1->SetPosition(PlayerPosition);
	objAttack2->SetPosition(PlayerPosition);

	// セットローテーション
	objPlayerRight->SetRotation(PlayerRotation);
	objPlayerLeft->SetRotation(PlayerRotation);

	// セットスケール
	objPlayerRight->SetScale(PlayerScale);
	objPlayerLeft->SetScale(PlayerScale);
}

// プレイヤーのアクション
void TutorialPlayer::PlayerAction()
{
	// スティックの入力を取得
	Input::StickMove stickMove = input->GetStickMove();

	// 落下処理
	PlayerPosition.y -= jumpPower;

	// 落下加速度を加える
	jumpPower += 0.01f;

	// 右移動
	if (input->PushKey(DIK_RIGHT) || 42767 < stickMove.lX && input->GetDevJoyStick()) {
		if (72 < PlayerPosition.x) {
			CameraPosition.x = 72.0f;
		}
		if (21 < PlayerPosition.x && PlayerPosition.x < 72) {
			CameraPosition.x += speed;
		}
		PlayerPosition.x += speed;
		PlayerRotation.z -= 3.6f;
		direction = 0;
	}

	// 左移動
	if (input->PushKey(DIK_LEFT) || stickMove.lX < 22767 && input->GetDevJoyStick()) {
		if (PlayerPosition.x < 21) {
			CameraPosition.x = 21.0f;
		}
		if (21 < PlayerPosition.x && PlayerPosition.x < 72) {
			CameraPosition.x -= speed;
		}
		PlayerPosition.x -= speed;
		PlayerRotation.z += 3.6f;
		direction = 1;
	}

	// ダッシュ
	if (input->PushKey(DIK_LSHIFT) && jumpCount == 0 ||
		input->PushKey(DIK_LSHIFT) && jumpCount == 3 ||
		input->PushButton(4) && jumpCount == 0 && input->GetDevJoyStick() ||
		input->PushButton(4) && jumpCount == 3 && input->GetDevJoyStick()) {
		speed = 0.2f;
	}
	else if (input->PushKey(DIK_LSHIFT) == 0 && jumpCount == 0 ||
		input->PushKey(DIK_LSHIFT) == 0 && jumpCount == 3 ||
		input->PushButton(4) == 0 && jumpCount == 0 && input->GetDevJoyStick() ||
		input->PushButton(4) == 0 && jumpCount == 3 && input->GetDevJoyStick()) {
		speed = 0.1f;
	}

	// 0段目の地面についていたら止まる
	if (PlayerPosition.y < 0) {
		PlayerPosition.y = 0.0f;
		Land();
	}
	// 1段目の地面についていたら止まる
	if (31 < PlayerPosition.x && PlayerPosition.x < 35 && 1.5f < PlayerPosition.y && PlayerPosition.y < 3) {
		PlayerPosition.y = 3.0f;
		Land();
	}
	// 4段目の地面についていたら止まる
	if (40 < PlayerPosition.x && PlayerPosition.x < 68 && 10.5f < PlayerPosition.y && PlayerPosition.y < 12) {
		PlayerPosition.y = 12.0f;
		Land();
	}
	// 4段目の地面についていたら止まる（灰色ブロックの上）
	if (68 < PlayerPosition.x && PlayerPosition.x < 74 && PlayerPosition.y < 12 && tutorialMap->GetBlockFlag2() == 0) {
		PlayerPosition.y = 12.0f;
		CrushBrockLand();
	}

	// ジャンプ
	if (input->TriggerKey(DIK_Z) && jumpCount < 2 && speed == 0.2f ||
		input->TriggerButton(0) && jumpCount < 2 && speed == 0.2f && input->GetDevJoyStick()) {
		jumpCount += 1;
		jumpPower = -0.35f;
	}
	else if (input->TriggerKey(DIK_Z) && jumpCount < 2 && speed == 0.1f ||
		input->TriggerButton(0) && jumpCount < 2 && speed == 0.1f && input->GetDevJoyStick()) {
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
	if (input->TriggerKey(DIK_X) && input->PushKey(DIK_DOWN) && jumpCount == 2 && attackFlag == 0 ||
		input->TriggerButton(1) && 42767 < stickMove.lY &&
		jumpCount == 2 && attackFlag == 0 && input->GetDevJoyStick()) {
		attackFlag = 2;
	}
	else if (input->TriggerKey(DIK_X) && attackFlag == 0 || input->TriggerButton(1) && attackFlag == 0) {
		attackFlag = 1;
	}
	if (attackFlag == 1) {
		PlayerRotation.y += 36.0f;
		PlayerRotation.z = 0.0f;
		if (PlayerRotation.y == 720) {
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

// 当たり判定
void TutorialPlayer::Collision()
{
	// 画面外に出ないようにする
	if (PlayerPosition.x < 0) {
		PlayerPosition.x = 0.0f;
	}
	if (93 < PlayerPosition.x) {
		PlayerPosition.x = 93.0f;
	}

	// 1個目のブロックの当たり判定（右）
	if (30 < PlayerPosition.x && PlayerPosition.x < 31 && PlayerPosition.y < 3 ||
		// 2個目のブロックの当たり判定（右）
		39 < PlayerPosition.x && PlayerPosition.x < 40 && PlayerPosition.y < 12 ||
		// 3個目のブロックの当たり判定（右）
		48 < PlayerPosition.x && PlayerPosition.x < 49 && 12 < PlayerPosition.y ||
		// 茶色ブロックの当たり判定（右）
		48 < PlayerPosition.x && PlayerPosition.x < 49 && PlayerPosition.y == 12 && tutorialMap->GetBlockFlag1() == 0 ||
		// 4個目のブロックの当たり判定（右）
		69 < PlayerPosition.x && PlayerPosition.x < 70 && 0 < PlayerPosition.y) {
		CameraPosition.x -= speed;
		PlayerPosition.x -= speed;
	}

	// 1個目のブロックの当たり判定（左）
	if (35 < PlayerPosition.x && PlayerPosition.x < 36 && PlayerPosition.y < 3 ||
		// 2個目のブロックの当たり判定（左）
		68 < PlayerPosition.x && PlayerPosition.x < 69 && PlayerPosition.y < 12 ||
		// 3個目のブロックの当たり判定（左）
		53 < PlayerPosition.x && PlayerPosition.x < 54 && 12 < PlayerPosition.y) {
		CameraPosition.x += speed;
		PlayerPosition.x += speed;
	}
	// 4個目のブロックの当たり判定（左）
	if (74 < PlayerPosition.x && PlayerPosition.x < 75 && 0 < PlayerPosition.y) {
		PlayerPosition.x += speed;
	}

	// 1段目の地面から落ちてしまった場合（左）
	if (30.5f < PlayerPosition.x && PlayerPosition.x < 31 && PlayerPosition.y < 3 ||
		// 1段目の地面から落ちてしまった場合（右）
		35 < PlayerPosition.x && PlayerPosition.x < 35.5f && PlayerPosition.y < 3 ||
		// 4段目の地面から落ちてしまった場合（左）
		39.5f < PlayerPosition.x && PlayerPosition.x < 40 && 10.5f < PlayerPosition.y && PlayerPosition.y < 12 ||
		// 4段目の地面から落ちてしまった場合（右）
		68 < PlayerPosition.x && PlayerPosition.x < 68.5f && 10.5f < PlayerPosition.y && PlayerPosition.y < 12) {
		jumpCount = 3;
	}

	// 1個目のジャンプ不可地帯にいる場合
	if (49 < PlayerPosition.x && PlayerPosition.x < 53 && 12 < PlayerPosition.y) {
		PlayerPosition.y = 12.0f;
		jumpPower = 0.0f;
	}
	// 2個目のジャンプ不可地帯にいる場合
	if (70 < PlayerPosition.x && PlayerPosition.x < 74 && 0 < PlayerPosition.y) {
		PlayerPosition.y = 0.0f;
		jumpPower = 0.0f;
	}

	// 茶色ブロックの当たり判定
	if (47.8f < PlayerPosition.x && PlayerPosition.y < 13 && attackFlag == 1) {
		tutorialMap->SetBlockFlag1();
	}
	// 灰色ブロックの当たり判定
	if (68 < PlayerPosition.x && PlayerPosition.x < 74 && attackFlag == 2) {
		if (PlayerPosition.y < 12) { tutorialMap->SetBlockFlag2(); }
		if (PlayerPosition.y < 9) { tutorialMap->SetBlockFlag3(); }
		if (PlayerPosition.y < 6) { tutorialMap->SetBlockFlag4(); }
		if (PlayerPosition.y < 3) { tutorialMap->SetBlockFlag5(); }
	}
}

// 通常ブロックの着地
void TutorialPlayer::Land()
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

// 壊れるブロックの着地
void TutorialPlayer::CrushBrockLand()
{
	if (jumpCount == 2) {
		PlayerRotation.z = 0.0f;
	}
	jumpPower = 0.0f;
	jumpCount = 0;
}