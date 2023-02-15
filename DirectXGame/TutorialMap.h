#pragma once

#include "Object3d.h"
#include "SafeDelete.h"

using namespace DirectX;

class TutorialMap
{
public: // メンバ関数
	// コンストラクタ
	TutorialMap();

	// デストラクタ
	~TutorialMap();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private: // メンバ変数
	const int mapX = 34;
	const int mapY = 9;

	XMFLOAT3 MapPosition[9][34] = {};

	int map[9][34] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,7,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0},
		{0,0,3,0,0,0,4,0,0,0,5,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,8,0,0,2,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	enum mapinfo
	{
		NONE,
		BROCK,
		DOOR,
		SIGN1,
		SIGN2,
		SIGN3,
		SIGN4,
		SIGN5,
		SIGN6
	};

	Model* modelBrock = nullptr;
	Model* modelDoor = nullptr;
	Model* modelSign1 = nullptr;
	Model* modelSign2 = nullptr;
	Model* modelSign3 = nullptr;
	Model* modelSign4 = nullptr;
	Model* modelSign5 = nullptr;
	Model* modelSign6 = nullptr;

	Object3d* objBrock[9][34] = {};
	Object3d* objDoor[9][34] = {};
	Object3d* objSign1[9][34] = {};
	Object3d* objSign2[9][34] = {};
	Object3d* objSign3[9][34] = {};
	Object3d* objSign4[9][34] = {};
	Object3d* objSign5[9][34] = {};
	Object3d* objSign6[9][34] = {};
};