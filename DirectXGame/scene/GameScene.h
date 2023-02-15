#pragma once

#include <DirectXMath.h>

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Audio.h"
#include "DebugCamera.h"
#include "TutorialPlayer.h"
#include "TutorialMap.h"
#include "StageOnePlayer.h"
#include "StageOneMap.h"
#include "StageTwoPlayer.h"
#include "StageTwoMap.h"
#include "StageThreePlayer.h"
#include "StageThreeMap.h"

// ゲームシーン
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数
	// コンストクラタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	// 毎フレーム処理
	void Update();

	// 描画
	void Draw();

	// シーン切り替え
	void SceneChange();

	// カメラ移動
	void CameraMove();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugCamera* camera = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	// ゲームシーン用
	char str[100] = { 0 };
	unsigned int scene = 0;
	unsigned int bossEnemyFlag = 0;

	Sprite* title = nullptr;
	Sprite* background1 = nullptr;
	Sprite* background2 = nullptr;
	Sprite* background3 = nullptr;
	Sprite* background4 = nullptr;
	Sprite* gameclear = nullptr;

	TutorialPlayer* tutorialPlayer = nullptr;
	TutorialMap* tutorialMap = nullptr;
	StageOnePlayer* stageOnePlayer = nullptr;
	StageOneMap* stageOneMap = nullptr;
	StageTwoPlayer* stageTwoPlayer = nullptr;
	StageTwoMap* stageTwoMap = nullptr;
	StageThreePlayer* stageThreePlayer = nullptr;
	StageThreeMap* stageThreeMap = nullptr;
};