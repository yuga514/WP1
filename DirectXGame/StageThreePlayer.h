#pragma once

#include "Object3d.h"
#include "SafeDelete.h"
#include "Input.h"
#include "DebugCamera.h"
#include "WinApp.h"
#include "StageTwoPlayer.h"

using namespace DirectX;

class StageThreePlayer
{
public: // �����o�֐�
	// �R���X�g���N�^
	StageThreePlayer();

	// �f�X�g���N�^
	~StageThreePlayer();

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

	// �G�l�~�[�̃A�N�V����
	void EnemyAction();

	// �����蔻��
	void Collision();

	// �ʏ�u���b�N�̒��n
	void Land();

	// �v���C���[�̍��W�̎擾
	XMFLOAT3 GetPlayerPosition() { return objPlayerRight->GetPosition(); }

	// �{�X�̍��W�̎擾
	XMFLOAT3 GetBossPosition() { return objBoss->GetPosition(); }

	// �J�����̒����_���W�̎擾
	XMFLOAT3 GetCameraTarget() { return camera->GetTarget(); }

private: // �����o�ϐ�
	bool direction = 0;
	float speed = 0.1f;
	float jumpPower = 0;
	unsigned int jumpCount = 0;
	unsigned int attackFlag = 0;
	bool bossMoveFlag = 0;

	XMFLOAT3 CameraPosition = { 21, 8.3f, -20 };
	XMFLOAT3 PlayerPosition = { 0,0,0 };
	XMFLOAT3 PlayerRotation = { 0,0,0 };
	XMFLOAT3 PlayerScale = { 1,1,1 };
	XMFLOAT3 BossPosition = { 30,1,0 };
	XMFLOAT3 BossRotation = { 0,0,0 };

	Input* input = nullptr;
	DebugCamera* camera = nullptr;

	Model* modelPlayerRight = nullptr;
	Model* modelPlayerLeft = nullptr;
	Model* modelAttack1 = nullptr;
	Model* modelAttack2 = nullptr;
	Model* modelBoss = nullptr;

	Object3d* objPlayerRight = nullptr;
	Object3d* objPlayerLeft = nullptr;
	Object3d* objAttack1 = nullptr;
	Object3d* objAttack2 = nullptr;
	Object3d* objBoss = nullptr;

	StageTwoPlayer* stageTwoPlayer = nullptr;
};