#pragma once

#include "Object3d.h"
#include "SafeDelete.h"
#include "Input.h"
#include "DebugCamera.h"
#include "WinApp.h"

using namespace DirectX;

class StageTwoPlayer
{
public: // �����o�֐�
	// �R���X�g���N�^
	StageTwoPlayer();

	// �f�X�g���N�^
	~StageTwoPlayer();

	// ������
	void Initialize(Input* input);

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �Q�b�^�[
	void Getter();

	// �Z�b�^�[
	void Setter();

	// �v���C���[�̃A�N�V����
	void PlayerAction();

	// �����蔻��
	void Collision();

	// �ʏ�u���b�N�̒��n
	void Land();

	// ���W�̎擾
	XMFLOAT3 GetPosition() { return objPlayerRight->GetPosition(); }

	// �����_���W�̎擾
	XMFLOAT3 GetTarget() { return camera->GetTarget(); }

private: // �����o�ϐ�
	bool direction = 0;
	float speed = 0.1f;
	float jumpPower = 0;
	unsigned int jumpCount = 0;
	unsigned int attackFlag = 0;

	XMFLOAT3 CameraPosition = { 21, 8.3f, -20 };
	XMFLOAT3 PlayerPosition = { 0,0,0 };
	XMFLOAT3 PlayerRotation = { 0,0,0 };
	XMFLOAT3 PlayerScale = { 1,1,1 };

	Input* input = nullptr;
	DebugCamera* camera = nullptr;

	Model* modelPlayerRight = nullptr;
	Model* modelPlayerLeft = nullptr;
	Model* modelAttack1 = nullptr;
	Model* modelAttack2 = nullptr;

	Object3d* objPlayerRight = nullptr;
	Object3d* objPlayerLeft = nullptr;
	Object3d* objAttack1 = nullptr;
	Object3d* objAttack2 = nullptr;
};