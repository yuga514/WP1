#include "TutorialMap.h"

// �R���X�g���N�^
TutorialMap::TutorialMap()
{
}

// �f�X�g���N�^
TutorialMap::~TutorialMap()
{
	safe_delete(modelBlock);
	safe_delete(modelDoor);
	safe_delete(modelBrownBlock);
	safe_delete(modelGrayBlock);
	safe_delete(modelSign);

	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BLOCK)
			{
				safe_delete(objBlock[y][x]);
			}
			if (map[y][x] == DOOR)
			{
				safe_delete(objDoor[y][x]);
			}
			if (map[y][x] == BROWN)
			{
				safe_delete(objBrownBlock[y][x]);
			}
			if (map[y][x] == GRAY)
			{
				safe_delete(objGrayBlock[y][x]);
			}
			if (map[y][x] == SIGN)
			{
				safe_delete(objSign[y][x]);
			}
		}
	}
}

// ������
void TutorialMap::Initialize()
{
	// ���f���ǂݍ���
	modelBlock = Model::CreateFromOBJ("block");
	modelDoor = Model::CreateFromOBJ("door");
	modelBrownBlock = Model::CreateFromOBJ("brownBlock");
	modelGrayBlock = Model::CreateFromOBJ("grayBlock");
	modelSign = Model::CreateFromOBJ("sign");

	// 3D�I�u�W�F�N�g����
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BLOCK)
			{
				objBlock[y][x] = Object3d::Create(modelBlock);
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x] = Object3d::Create(modelDoor);
			}
			if (map[y][x] == BROWN)
			{
				objBrownBlock[y][x] = Object3d::Create(modelBrownBlock);
			}
			if (map[y][x] == GRAY)
			{
				objGrayBlock[y][x] = Object3d::Create(modelGrayBlock);
			}
			if (map[y][x] == SIGN)
			{
				objSign[y][x] = Object3d::Create(modelSign);
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
void TutorialMap::Update()
{
	// �Q�b�g�|�W�V����
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BLOCK)
			{
				objBlock[y][x]->GetPosition();
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->GetPosition();
			}
			if (map[y][x] == BROWN)
			{
				objBrownBlock[y][x]->GetPosition();
			}
			if (map[y][x] == GRAY)
			{
				objGrayBlock[y][x]->GetPosition();
			}
			if (map[y][x] == SIGN)
			{
				objSign[y][x]->GetPosition();
			}
		}
	}

	// �Z�b�g�|�W�V����
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BLOCK)
			{
				objBlock[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == BROWN)
			{
				objBrownBlock[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == GRAY)
			{
				objGrayBlock[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == SIGN)
			{
				objSign[y][x]->SetPosition(MapPosition[y][x]);
			}
		}
	}

	// �A�b�v�f�[�g
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BLOCK)
			{
				objBlock[y][x]->Update();
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->Update();
			}
			if (map[y][x] == BROWN)
			{
				objBrownBlock[y][x]->Update();
			}
			if (map[y][x] == GRAY)
			{
				objGrayBlock[y][x]->Update();
			}
			if (map[y][x] == SIGN)
			{
				objSign[y][x]->Update();
			}
		}
	}
}

// �`��
void TutorialMap::Draw()
{
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			if (map[y][x] == BLOCK)
			{
				objBlock[y][x]->Draw();
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->Draw();
			}
			if (map[y][x] == BROWN && blockFlag[0] == 0)
			{
				objBrownBlock[y][x]->Draw();
			}
			if (map[y][x] == GRAY)
			{
				if (blockFlag[1] == 0) { objGrayBlock[4][24]->Draw(); }
				if (blockFlag[2] == 0) { objGrayBlock[5][24]->Draw(); }
				if (blockFlag[3] == 0) { objGrayBlock[6][24]->Draw(); }
				if (blockFlag[4] == 0) { objGrayBlock[7][24]->Draw(); }
			}
			if (map[y][x] == SIGN)
			{
				objSign[y][x]->Draw();
			}
		}
	}
}