#pragma once

#include "Object3d.h"
#include "SafeDelete.h"

using namespace DirectX;

class StageTwoMap
{
public: // メンバ関数
	// コンストラクタ
	StageTwoMap();

	// デストラクタ
	~StageTwoMap();

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
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	enum mapinfo
	{
		NONE,
		BROCK,
		DOOR
	};

	Model* modelBrock = nullptr;
	Model* modelDoor = nullptr;

	Object3d* objBrock[9][17] = {};
	Object3d* objDoor[9][17] = {};
};