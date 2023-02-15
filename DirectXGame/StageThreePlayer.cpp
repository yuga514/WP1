#include "StageThreePlayer.h"

// �R���X�g���N�^
StageThreePlayer::StageThreePlayer()
{
}

// �f�X�g���N�^
StageThreePlayer::~StageThreePlayer()
{
	safe_delete(modelPlayerRight);
	safe_delete(modelPlayerLeft);
	safe_delete(modelAttack1);
	safe_delete(modelAttack2);
	safe_delete(modelBossBrownEnemy);
	safe_delete(objPlayerRight);
	safe_delete(objPlayerLeft);
	safe_delete(objAttack1);
	safe_delete(objAttack2);
	safe_delete(objBossBrownEnemy);
}

// ������
void StageThreePlayer::Initialize(Input* input)
{
	this->input = input;

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	// �J���������_���Z�b�g
	camera->SetDistance(3.0f);

	// ���f���ǂݍ���
	modelPlayerRight = Model::CreateFromOBJ("playerRight");
	modelPlayerLeft = Model::CreateFromOBJ("playerLeft");
	modelAttack1 = Model::CreateFromOBJ("attack1");
	modelAttack2 = Model::CreateFromOBJ("attack2");
	modelBossBrownEnemy = Model::CreateFromOBJ("bossBrownEnemy");

	// 3D�I�u�W�F�N�g����
	objPlayerRight = Object3d::Create(modelPlayerRight);
	objPlayerLeft = Object3d::Create(modelPlayerLeft);
	objAttack1 = Object3d::Create(modelAttack1);
	objAttack2 = Object3d::Create(modelAttack2);
	objBossBrownEnemy = Object3d::Create(modelBossBrownEnemy);
}

// �X�V
void StageThreePlayer::Update()
{
	// �Q�b�^�[
	Getter();

	// �v���C���[�̃A�N�V����
	PlayerAction();

	// �G�l�~�[�̃A�N�V����
	EnemyAction();

	// �����蔻��
	Collision();

	// �Z�b�^�[
	Setter();

	// �A�b�v�f�[�g
	camera->Update();

	objPlayerRight->Update();
	objPlayerLeft->Update();
	objAttack1->Update();
	objAttack2->Update();
	objBossBrownEnemy->Update();
}

// �`��
void StageThreePlayer::Draw()
{
	if (direction == 0) {
		objPlayerRight->Draw();
	}
	if (direction == 1) {
		objPlayerLeft->Draw();
	}
	if (attackFlag == 1) {
		objAttack1->Draw();
	}
	if (attackFlag == 2) {
		objAttack2->Draw();
	}
	objBossBrownEnemy->Draw();
}

// �Q�b�^�[
void StageThreePlayer::Getter()
{
	// �Q�b�g�^�[�Q�b�g
	camera->GetTarget();

	// �Q�b�g�|�W�V����
	objPlayerRight->GetPosition();
	objPlayerLeft->GetPosition();
	objAttack1->GetPosition();
	objAttack2->GetPosition();
	objBossBrownEnemy->GetPosition();

	// �Q�b�g���[�e�[�V����
	objPlayerRight->GetRotation();
	objPlayerLeft->GetRotation();
	objBossBrownEnemy->GetRotation();

	// �Q�b�g�X�P�[��
	objPlayerRight->GetScale();
	objPlayerLeft->GetScale();
}

// �Z�b�^�[
void StageThreePlayer::Setter()
{
	// �Z�b�g�^�[�Q�b�g
	camera->SetTarget(CameraPosition);

	// �Z�b�g�|�W�V����
	objPlayerRight->SetPosition(PlayerPosition);
	objPlayerLeft->SetPosition(PlayerPosition);
	objAttack1->SetPosition(PlayerPosition);
	objAttack2->SetPosition(PlayerPosition);
	objBossBrownEnemy->SetPosition(BossBrownEnemyPosition);

	// �Z�b�g���[�e�[�V����
	objPlayerRight->SetRotation(PlayerRotation);
	objPlayerLeft->SetRotation(PlayerRotation);
	objBossBrownEnemy->SetRotation(BossEnemyRotation);

	// �Z�b�g�X�P�[��
	objPlayerRight->SetScale(PlayerScale);
	objPlayerLeft->SetScale(PlayerScale);
}

// �v���C���[�̃A�N�V����
void StageThreePlayer::PlayerAction()
{
	// ��������
	PlayerPosition.y -= jumpPower;

	// ���������x��������
	jumpPower += 0.01f;

	// �E�ړ�
	if (input->PushKey(DIK_RIGHT)) {
		PlayerPosition.x += speed;
		PlayerRotation.z -= 3.6f;
		direction = 0;
	}

	// ���ړ�
	if (input->PushKey(DIK_LEFT)) {
		PlayerPosition.x -= speed;
		PlayerRotation.z += 3.6f;
		direction = 1;
	}

	// �_�b�V��
	if (input->PushKey(DIK_X) && jumpCount == 0 || input->PushKey(DIK_X) && jumpCount == 3) {
		speed = 0.2f;
	}
	if (input->PushKey(DIK_X) == 0 && jumpCount == 0 || input->PushKey(DIK_X) == 0 && jumpCount == 3) {
		speed = 0.1f;
	}

	// 0�i�ڂ̒n�ʂɂ��Ă�����~�܂�
	if (PlayerPosition.y < 0) {
		PlayerPosition.y = 0.0f;
		Land();
	}

	// �W�����v
	if (input->TriggerKey(DIK_Z) && jumpCount < 2 && speed == 0.2f) {
		jumpCount += 1;
		jumpPower = -0.35f;
	}
	else if (input->TriggerKey(DIK_Z) && jumpCount < 2 && speed == 0.1f) {
		jumpCount += 1;
		jumpPower = -0.3f;
	}
	if (jumpCount == 2) {
		if (direction == 0) {
			PlayerRotation.z -= 36.0f;
		}
		if (direction == 1) {
			PlayerRotation.z += 36.0f;
		}
	}

	// �U��
	if (input->TriggerKey(DIK_X) && input->PushKey(DIK_DOWN) && jumpCount == 2 && attackFlag == 0) {
		attackFlag = 2;
	}
	else if (input->TriggerKey(DIK_X) && attackFlag == 0) {
		attackFlag = 1;
	}
	if (attackFlag == 1) {
		PlayerRotation.y += 36.0f;
		PlayerRotation.z = 0.0f;
		if (PlayerRotation.y == 360) {
			PlayerRotation.y = 0.0f;
			attackFlag = 0;
		}
	}
	if (attackFlag == 2) {
		PlayerRotation.y += 36.0f;
		PlayerPosition.y -= 1.0f;
		PlayerRotation.z = 0.0f;
	}

	// �v���C���[������ł�����
	if (PlayerScale.y < 1) {
		PlayerScale.x -= 0.1f;
		PlayerScale.y += 0.1f;
		PlayerScale.z -= 0.1f;
	}
}

// �G�l�~�[�̃A�N�V����
void StageThreePlayer::EnemyAction()
{
	// ���ړ�
	if (bossBrownEnemyMoveFlag == 0) {
		BossBrownEnemyPosition.x -= 0.2f;
	}
	// �E�ړ�
	if (bossBrownEnemyMoveFlag == 1) {
		BossBrownEnemyPosition.x += 0.2f;
	}

	// �����]��
	if (BossBrownEnemyPosition.x < 0) {
		bossBrownEnemyMoveFlag = 1;
	}
	if (42 < BossBrownEnemyPosition.x) {
		bossBrownEnemyMoveFlag = 0;
	}

	// ��]
	BossEnemyRotation.y += 3.6f;
	if (BossEnemyRotation.y == 360) {
		BossEnemyRotation.y = 0.0f;
	}
}

// �����蔻��
void StageThreePlayer::Collision()
{
	// ��ʊO�ɏo�Ȃ��悤�ɂ���
	if (PlayerPosition.x < 0) {
		PlayerPosition.x = 0.0f;
	}
	if (42 < PlayerPosition.x) {
		PlayerPosition.x = 42.0f;
	}
}

// �ʏ�u���b�N�̒��n
void StageThreePlayer::Land()
{
	if (jumpCount == 2) {
		PlayerRotation.z = 0.0f;
	}
	if (attackFlag == 2) {
		PlayerRotation.y = 0.0f;
		PlayerScale = { 1.9f, 0.1f, 1.9f };
		attackFlag = 0;
	}
	jumpPower = 0.0f;
	jumpCount = 0;
}