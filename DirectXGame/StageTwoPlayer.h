#pragma once

#include "Object3d.h"
#include "SafeDelete.h"
#include "Input.h"
#include "DebugCamera.h"
#include "WinApp.h"

using namespace DirectX;

class StageTwoPlayer
{
public: // メンバ関数
	// コンストラクタ
	StageTwoPlayer();

	// デストラクタ
	~StageTwoPlayer();

	// 初期化
	void Initialize(Input* input);

	// 更新
	void Update();

	// 描画
	void Draw();

	// ゲッター
	void Getter();

	// セッター
	void Setter();

	// プレイヤーのアクション
	void PlayerAction();

	// 当たり判定
	void Collision();

	// 通常ブロックの着地
	void Land();

	// 座標の取得
	XMFLOAT3 GetPosition() { return objPlayerRight->GetPosition(); }

	// 注視点座標の取得
	XMFLOAT3 GetTarget() { return camera->GetTarget(); }

private: // メンバ変数
	bool direction = 0;
	float speed = 0.1f;
	float jumpPower = 0;
	unsigned int jumpCount = 0;
	unsigned int attackFlag = 0;

	XMFLOAT3 CameraPosition = { 21, 8.3f, -20 };
	XMFLOAT3 PlayerPosition = { 0,0,0 };
	XMFLOAT3 PlayerRotation = { 0,0,0 };
	XMFLOAT3 PlayerScale = { 1,1,1 };

	Input* input = nullptr;
	DebugCamera* camera = nullptr;

	Model* modelPlayerRight = nullptr;
	Model* modelPlayerLeft = nullptr;
	Model* modelAttack1 = nullptr;
	Model* modelAttack2 = nullptr;

	Object3d* objPlayerRight = nullptr;
	Object3d* objPlayerLeft = nullptr;
	Object3d* objAttack1 = nullptr;
	Object3d* objAttack2 = nullptr;
};