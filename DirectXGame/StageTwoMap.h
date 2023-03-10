#pragma once

#include "Object3d.h"
#include "SafeDelete.h"

using namespace DirectX;

class StageTwoMap
{
public: // �����o�֐�
	// �R���X�g���N�^
	StageTwoMap();

	// �f�X�g���N�^
	~StageTwoMap();

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �n�[�g�t���O�̎擾
	bool GetHeartFlag() { return heartFlag; }

	// �n�[�g�t���O�̐ݒ�
	void SetHeartFlag() { heartFlag = 1; }

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
		{0,0,0,0,3,0,0,0,0,0,0,0,0,0,2,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	enum mapinfo
	{
		NONE,
		BROCK,
		DOOR,
		HEART
	};

	bool heartFlag = 0;

	XMFLOAT3 HeartRotation = { 0,0,0 };

	Model* modelBrock = nullptr;
	Model* modelDoor = nullptr;
	Model* modelHeart = nullptr;

	Object3d* objBrock[9][17] = {};
	Object3d* objDoor[9][17] = {};
	Object3d* objHeart[9][17] = {};
};