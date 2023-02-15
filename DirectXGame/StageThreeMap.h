#pragma once

#include "Object3d.h"
#include "SafeDelete.h"

using namespace DirectX;

class StageThreeMap
{
public: // メンバ関数
	// コンストラクタ
	StageThreeMap();

	// デストラクタ
	~StageThreeMap();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private: // メンバ変数
	const int mapX = 17;
	const int mapY = 9;

	XMFLOAT3 MapPosition[9][17] = {};

	int map[9][17] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	enum mapinfo
	{
		NONE,
		BROCK
	};

	Model* modelBrock = nullptr;

	Object3d* objBrock[9][17] = {};
};