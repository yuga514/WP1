#include "StageThreeMap.h"

// �R���X�g���N�^
StageThreeMap::StageThreeMap()
{
}

// �f�X�g���N�^
StageThreeMap::~StageThreeMap()
{
	safe_delete(modelBrock);

	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				safe_delete(objBrock[y][x]);
			}
		}
	}
}

// ������
void StageThreeMap::Initialize()
{
	// ���f���ǂݍ���
	modelBrock = Model::CreateFromOBJ("block");

	// 3D�I�u�W�F�N�g����
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				objBrock[y][x] = Object3d::Create(modelBrock);
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
void StageThreeMap::Update()
{
	// �Q�b�g�|�W�V����
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				objBrock[y][x]->GetPosition();
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
		}
	}

	// �A�b�v�f�[�g
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				objBrock[y][x]->Update();
			}
		}
	}
}

// �`��
void StageThreeMap::Draw()
{
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BROCK)
			{
				objBrock[y][x]->Draw();
			}
		}
	}
}