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

	// ブロックフラグの取得
	bool GetBlockFlag1() { return blockFlag[0]; }
	bool GetBlockFlag2() { return blockFlag[1]; }
	bool GetBlockFlag3() { return blockFlag[2]; }
	bool GetBlockFlag4() { return blockFlag[3]; }
	bool GetBlockFlag5() { return blockFlag[4]; }

	// ブロックフラグの設定
	void SetBlockFlag1() { blockFlag[0] = 1; }
	void SetBlockFlag2() { blockFlag[1] = 1; }
	void SetBlockFlag3() { blockFlag[2] = 1; }
	void SetBlockFlag4() { blockFlag[3] = 1; }
	void SetBlockFlag5() { blockFlag[4] = 1; }

private: // メンバ変数
	const int mapX = 34;
	const int mapY = 9;

	XMFLOAT3 MapPosition[9][34] = {};

	int map[9][34] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,3,0,0,0,5,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,4,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,4,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,4,1,0,0,0,0,0,0,0,0},
		{0,5,0,5,0,0,0,0,5,0,5,0,1,0,0,1,1,1,1,1,1,1,1,1,4,0,0,0,0,0,0,2,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	enum mapinfo
	{
		NONE,
		BLOCK,
		DOOR,
		BROWN,
		GRAY,
		SIGN
	};

	bool blockFlag[5] = {};

	Model* modelBlock = nullptr;
	Model* modelDoor = nullptr;
	Model* modelBrownBlock = nullptr;
	Model* modelGrayBlock = nullptr;
	Model* modelSign = nullptr;

	Object3d* objBlock[9][34] = {};
	Object3d* objDoor[9][34] = {};
	Object3d* objBrownBlock[9][34] = {};
	Object3d* objGrayBlock[9][34] = {};
	Object3d* objSign[9][34] = {};
};