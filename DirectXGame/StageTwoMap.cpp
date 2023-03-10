#include "StageTwoMap.h"

// �R���X�g���N�^
StageTwoMap::StageTwoMap()
{
}

// �f�X�g���N�^
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

// ������
void StageTwoMap::Initialize()
{
	// ���f���ǂݍ���
	modelBrock = Model::CreateFromOBJ("brock");
	modelDoor = Model::CreateFromOBJ("door");
	modelHeart = Model::CreateFromOBJ("heart");

	// 3D�I�u�W�F�N�g����
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

	// �}�b�v�`�b�v�z�u
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			MapPosition[y][x].x = 3.0f * x - 3.0f;
			MapPosition[y][x].y = -3.0f * y + 19.8f;
		}
	}
}

// �X�V
void StageTwoMap::Update()
{
	// �Q�b�g�|�W�V����
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

	// �Q�b�g���[�e�[�V����
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == HEART)
			{
				objHeart[y][x]->GetRotation();
			}
		}
	}

	// �Z�b�g�|�W�V����
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

	// �Z�b�g���[�e�[�V����
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == HEART)
			{
				objHeart[y][x]->SetRotation(HeartRotation);
			}
		}
	}

	// �Z�b�g�X�P�[��
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == HEART)
			{
				objHeart[y][x]->SetScale({ 0.5f,0.5f,0.5f });
			}
		}
	}

	// �n�[�g�̉�]
	HeartRotation.y += 2.0f;
	if (HeartRotation.y == 360) { HeartRotation.y = 0.0f; }

	// �A�b�v�f�[�g
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

// �`��
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