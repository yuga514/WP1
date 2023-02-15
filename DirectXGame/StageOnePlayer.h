#pragma once

#include "Object3d.h"
#include "SafeDelete.h"
#include "Input.h"
#include "DebugCamera.h"
#include "WinApp.h"

using namespace DirectX;

class StageOnePlayer
{
public: // メンバ関数
	// コンストラクタ
	StageOnePlayer();

	// デストラクタ
	~StageOnePlayer();

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

	// エネミーのアクション
	void EnemyAction();

	// 当たり判定
	void Collision();

	// 通常ブロックの着地
	void Land();

	// 壊れるブロックの着地
	void CrushBrockLand();

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
	bool brownBrockFlag[2] = {};
	bool grayBrockFlag[4] = {};
	bool brownEnemyFlag[2] = {};
	bool grayEnemyFlag = 0;
	bool brownEnemyMoveFlag[2] = {};
	bool grayEnemyMoveFlag = 0;

	XMFLOAT3 CameraPosition = { 21, 8.3f, -20 };
	XMFLOAT3 PlayerPosition = { 0,0,0 };
	XMFLOAT3 PlayerRotation = { 0,0,0 };
	XMFLOAT3 PlayerScale = { 1,1,1 };
	XMFLOAT3 BrownBrockPosition[2] = { { 15, -1.2f, 0 }, { 72, -1.2f, 0 } };
	XMFLOAT3 GrayBrockPosition[4] = { { 81, 7.8f, 0 }, { 81, 4.8f, 0 }, { 81, 1.8f, 0 }, { 81, -1.2f, 0 } };
	XMFLOAT3 BrownEnemyPosition[2] = { { 27, 0, 0 },{ 45, 12, 0 } };
	XMFLOAT3 GrayEnemyPosition = { 63, 0, 0 };
	XMFLOAT3 EnemyRotation = { 0,0,0 };

	Input* input = nullptr;
	DebugCamera* camera = nullptr;

	Model* modelPlayerRight = nullptr;
	Model* modelPlayerLeft = nullptr;
	Model* modelAttack1 = nullptr;
	Model* modelAttack2 = nullptr;
	Model* modelBrownBrock = nullptr;
	Model* modelGrayBrock = nullptr;
	Model* modelBrownEnemy = nullptr;
	Model* modelGrayEnemy = nullptr;

	Object3d* objPlayerRight = nullptr;
	Object3d* objPlayerLeft = nullptr;
	Object3d* objAttack1 = nullptr;
	Object3d* objAttack2 = nullptr;
	Object3d* objBrownBrock[2] = {};
	Object3d* objGrayBrock[4] = {};
	Object3d* objBrownEnemy[2] = {};
	Object3d* objGrayEnemy = nullptr;
};