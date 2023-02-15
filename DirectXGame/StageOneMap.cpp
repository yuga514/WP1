#include "StageOneMap.h"

// コンストラクタ
StageOneMap::StageOneMap()
{
}

// デストラクタ
StageOneMap::~StageOneMap()
{
	safe_delete(modelBrock);
	safe_delete(modelDoor);

	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				safe_delete(objBrock[y][x]);
			}
			if (map[y][x] == DOOR)
			{
				safe_delete(objDoor[y][x]);
			}
		}
	}
}

// 初期化
void StageOneMap::Initialize()
{
	// モデル読み込み
	modelBrock = Model::CreateFromOBJ("brock");
	modelDoor = Model::CreateFromOBJ("door");

	// 3Dオブジェクト生成
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				objBrock[y][x] = Object3d::Create(modelBrock);
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x] = Object3d::Create(modelDoor);
			}
		}
	}

	// マップチップ配置
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			MapPosition[y][x].x = 3.0f * x - 3.0f;
			MapPosition[y][x].y = -3.0f * y + 19.8f;
		}
	}
}

// 更新
void StageOneMap::Update()
{
	// ゲットポジション
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				objBrock[y][x]->GetPosition();
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->GetPosition();
			}
		}
	}

	// セットポジション
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				objBrock[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->SetPosition(MapPosition[y][x]);
			}
		}
	}

	// アップデート
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				objBrock[y][x]->Update();
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->Update();
			}
		}
	}
}

// 描画
void StageOneMap::Draw()
{
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				objBrock[y][x]->Draw();
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->Draw();
			}
		}
	}
}