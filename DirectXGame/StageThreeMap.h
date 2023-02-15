#pragma once

#include "Object3d.h"
#include "SafeDelete.h"

using namespace DirectX;

class StageThreeMap
{
public: // �����o�֐�
	// �R���X�g���N�^
	StageThreeMap();

	// �f�X�g���N�^
	~StageThreeMap();

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Draw();

private: // �����o�ϐ�
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