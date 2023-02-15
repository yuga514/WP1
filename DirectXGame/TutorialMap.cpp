#include "TutorialMap.h"

// �R���X�g���N�^
TutorialMap::TutorialMap()
{
}

// �f�X�g���N�^
TutorialMap::~TutorialMap()
{
	safe_delete(modelBrock);
	safe_delete(modelDoor);
	safe_delete(modelSign1);
	safe_delete(modelSign2);
	safe_delete(modelSign3);
	safe_delete(modelSign4);
	safe_delete(modelSign5);
	safe_delete(modelSign6);

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
			if (map[y][x] == SIGN1)
			{
				safe_delete(objSign1[y][x]);
			}
			if (map[y][x] == SIGN2)
			{
				safe_delete(objSign2[y][x]);
			}
			if (map[y][x] == SIGN3)
			{
				safe_delete(objSign3[y][x]);
			}
			if (map[y][x] == SIGN4)
			{
				safe_delete(objSign4[y][x]);
			}
			if (map[y][x] == SIGN5)
			{
				safe_delete(objSign5[y][x]);
			}
			if (map[y][x] == SIGN6)
			{
				safe_delete(objSign6[y][x]);
			}
		}
	}
}

// ������
void TutorialMap::Initialize()
{
	// ���f���ǂݍ���
	modelBrock = Model::CreateFromOBJ("brock");
	modelDoor = Model::CreateFromOBJ("door");
	modelSign1 = Model::CreateFromOBJ("sign1");
	modelSign2 = Model::CreateFromOBJ("sign2");
	modelSign3 = Model::CreateFromOBJ("sign3");
	modelSign4 = Model::CreateFromOBJ("sign4");
	modelSign5 = Model::CreateFromOBJ("sign5");
	modelSign6 = Model::CreateFromOBJ("sign6");

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
			if (map[y][x] == SIGN1)
			{
				objSign1[y][x] = Object3d::Create(modelSign1);
			}
			if (map[y][x] == SIGN2)
			{
				objSign2[y][x] = Object3d::Create(modelSign2);
			}
			if (map[y][x] == SIGN3)
			{
				objSign3[y][x] = Object3d::Create(modelSign3);
			}
			if (map[y][x] == SIGN4)
			{
				objSign4[y][x] = Object3d::Create(modelSign4);
			}
			if (map[y][x] == SIGN5)
			{
				objSign5[y][x] = Object3d::Create(modelSign5);
			}
			if (map[y][x] == SIGN6)
			{
				objSign6[y][x] = Object3d::Create(modelSign6);
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
			if (map[y][x] == BROCK)
			{
				objBrock[y][x]->GetPosition();
			}
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->GetPosition();
			}
			if (map[y][x] == SIGN1)
			{
				objSign1[y][x]->GetPosition();
			}
			if (map[y][x] == SIGN2)
			{
				objSign2[y][x]->GetPosition();
			}
			if (map[y][x] == SIGN3)
			{
				objSign3[y][x]->GetPosition();
			}
			if (map[y][x] == SIGN4)
			{
				objSign4[y][x]->GetPosition();
			}
			if (map[y][x] == SIGN5)
			{
				objSign5[y][x]->GetPosition();
			}
			if (map[y][x] == SIGN6)
			{
				objSign6[y][x]->GetPosition();
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
			if (map[y][x] == SIGN1)
			{
				objSign1[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == SIGN2)
			{
				objSign2[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == SIGN3)
			{
				objSign3[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == SIGN4)
			{
				objSign4[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == SIGN5)
			{
				objSign5[y][x]->SetPosition(MapPosition[y][x]);
			}
			if (map[y][x] == SIGN6)
			{
				objSign6[y][x]->SetPosition(MapPosition[y][x]);
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
			if (map[y][x] == DOOR)
			{
				objDoor[y][x]->Update();
			}
			if (map[y][x] == SIGN1)
			{
				objSign1[y][x]->Update();
			}
			if (map[y][x] == SIGN2)
			{
				objSign2[y][x]->Update();
			}
			if (map[y][x] == SIGN3)
			{
				objSign3[y][x]->Update();
			}
			if (map[y][x] == SIGN4)
			{
				objSign4[y][x]->Update();
			}
			if (map[y][x] == SIGN5)
			{
				objSign5[y][x]->Update();
			}
			if (map[y][x] == SIGN6)
			{
				objSign6[y][x]->Update();
			}
		}
	}
}

// �`��
void TutorialMap::Draw()
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
			if (map[y][x] == SIGN1)
			{
				objSign1[y][x]->Draw();
			}
			if (map[y][x] == SIGN2)
			{
				objSign2[y][x]->Draw();
			}
			if (map[y][x] == SIGN3)
			{
				objSign3[y][x]->Draw();
			}
			if (map[y][x] == SIGN4)
			{
				objSign4[y][x]->Draw();
			}
			if (map[y][x] == SIGN5)
			{
				objSign5[y][x]->Draw();
			}
			if (map[y][x] == SIGN6)
			{
				objSign6[y][x]->Draw();
			}
		}
	}
}