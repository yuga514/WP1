#include "StageTwoMap.h"

// コンストラクタ
StageTwoMap::StageTwoMap()
{
}

// デストラクタ
StageTwoMap::~StageTwoMap()
{
	safe_delete(modelBrock);
	safe_delete(modelDoor);
	safe_delete(modelHeart);

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
			if (map[y][x] == HEART)
			{
				safe_delete(objHeart[y][x]);
			}
		}
	}
}

// 初期化
void StageTwoMap::Initialize()
{
	// モデル読み込み
	modelBrock = Model::CreateFromOBJ("brock");
	modelDoor = Model::CreateFromOBJ("door");
	modelHeart = Model::CreateFromOBJ("heart");

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
			if (map[y][x] == HEART)
			{
				objHeart[y][x] = Object3d::Create(modelHeart);
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
void StageTwoMap::Update()
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
			if (map[y][x] == HEART)
			{
				objHeart[y][x]->GetPosition();
			}
		}
	}

	// ゲットローテーション
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == HEART)
			{
				objHeart[y][x]->GetRotation();
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
			if (map[y][x] == HEART)
			{
				objHeart[y][x]->SetPosition(MapPosition[y][x]);
			}
		}
	}

	// セットローテーション
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == HEART)
			{
				objHeart[y][x]->SetRotation(HeartRotation);
			}
		}
	}

	// セットスケール
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == HEART)
			{
				objHeart[y][x]->SetScale({ 0.5f,0.5f,0.5f });
			}
		}
	}

	// ハートの回転
	HeartRotation.y += 2.0f;
	if (HeartRotation.y == 360) { HeartRotation.y = 0.0f; }

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
			if (map[y][x] == HEART)
			{
				objHeart[y][x]->Update();
			}
		}
	}
}

// 描画
void StageTwoMap::Draw()
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
			if (map[y][x] == HEART && heartFlag == 0)
			{
				objHeart[y][x]->Draw();
			}
		}
	}
}