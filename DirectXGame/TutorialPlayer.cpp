#include "TutorialPlayer.h"

// �R���X�g���N�^
TutorialPlayer::TutorialPlayer()
{
}

// �f�X�g���N�^
TutorialPlayer::~TutorialPlayer()
{
	safe_delete(modelPlayerRight);
	safe_delete(modelPlayerLeft);
	safe_delete(modelAttack1);
	safe_delete(modelAttack2);
	safe_delete(modelBrownBrock);
	safe_delete(modelGrayBrock);
	safe_delete(objPlayerRight);
	safe_delete(objPlayerLeft);
	safe_delete(objAttack1);
	safe_delete(objAttack2);
	safe_delete(objBrownBrock);
	for (int i = 0; i < 4; i++) {
		safe_delete(objGrayBrock[i]);
	}
}

// ������
void TutorialPlayer::Initialize(Input* input)
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
	modelBrownBrock = Model::CreateFromOBJ("brownBrock");
	modelGrayBrock = Model::CreateFromOBJ("grayBrock");

	// 3D�I�u�W�F�N�g����
	objPlayerRight = Object3d::Create(modelPlayerRight);
	objPlayerLeft = Object3d::Create(modelPlayerLeft);
	objAttack1 = Object3d::Create(modelAttack1);
	objAttack2 = Object3d::Create(modelAttack2);
	objBrownBrock = Object3d::Create(modelBrownBrock);
	for (int i = 0; i < 4; i++) {
		objGrayBrock[i] = Object3d::Create(modelGrayBrock);
	}
}

// �X�V
void TutorialPlayer::Update()
{
	// �Q�b�^�[
	Getter();

	// �v���C���[�̃A�N�V����
	PlayerAction();

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
	objBrownBrock->Update();
	for (int i = 0; i < 4; i++) {
		objGrayBrock[i]->Update();
	}
}

// �`��
void TutorialPlayer::Draw()
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
	if (brownBrockFlag == 0) {
		objBrownBrock->Draw();
	}
	for (int i = 0; i < 4; i++) {
		if (grayBrockFlag[i] == 0) {
			objGrayBrock[i]->Draw();
		}
	}
}

// �Q�b�^�[
void TutorialPlayer::Getter()
{
	// �Q�b�g�^�[�Q�b�g
	camera->GetTarget();

	// �Q�b�g�|�W�V����
	objPlayerRight->GetPosition();
	objPlayerLeft->GetPosition();
	objAttack1->GetPosition();
	objAttack2->GetPosition();
	objBrownBrock->GetPosition();
	for (int i = 0; i < 4; i++) {
		objGrayBrock[i]->GetPosition();
	}

	// �Q�b�g���[�e�[�V����
	objPlayerRight->GetRotation();
	objPlayerLeft->GetRotation();

	// �Q�b�g�X�P�[��
	objPlayerRight->GetScale();
	objPlayerLeft->GetScale();
}

// �Z�b�^�[
void TutorialPlayer::Setter()
{
	// �Z�b�g�^�[�Q�b�g
	camera->SetTarget(CameraPosition);

	// �Z�b�g�|�W�V����
	objPlayerRight->SetPosition(PlayerPosition);
	objPlayerLeft->SetPosition(PlayerPosition);
	objAttack1->SetPosition(PlayerPosition);
	objAttack2->SetPosition(PlayerPosition);
	objBrownBrock->SetPosition(BrownBrockPosition);
	for (int i = 0; i < 4; i++) {
		objGrayBrock[i]->SetPosition(GrayBrockPosition[i]);
	}

	// �Z�b�g���[�e�[�V����
	objPlayerRight->SetRotation(PlayerRotation);
	objPlayerLeft->SetRotation(PlayerRotation);

	// �Z�b�g�X�P�[��
	objPlayerRight->SetScale(PlayerScale);
	objPlayerLeft->SetScale(PlayerScale);
}

// �v���C���[�̃A�N�V����
void TutorialPlayer::PlayerAction()
{
	// ��������
	PlayerPosition.y -= jumpPower;

	// ���������x��������
	jumpPower += 0.01f;

	// �E�ړ�
	if (input->PushKey(DIK_RIGHT)) {
		if (72 < PlayerPosition.x) {
			CameraPosition.x = 72.0f;
		}
		if (21 < PlayerPosition.x && PlayerPosition.x < 72) {
			CameraPosition.x += speed;
		}
		PlayerPosition.x += speed;
		PlayerRotation.z -= 3.6f;
		direction = 0;
	}

	// ���ړ�
	if (input->PushKey(DIK_LEFT)) {
		if (PlayerPosition.x < 21) {
			CameraPosition.x = 21.0f;
		}
		if (21 < PlayerPosition.x && PlayerPosition.x < 72) {
			CameraPosition.x -= speed;
		}
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
	// 1�i�ڂ̒n�ʂɂ��Ă�����~�܂�
	if (31 < PlayerPosition.x && PlayerPosition.x < 35 && 1.5f < PlayerPosition.y && PlayerPosition.y < 3) {
		PlayerPosition.y = 3.0f;
		Land();
	}
	// 4�i�ڂ̒n�ʂɂ��Ă�����~�܂�
	if (40 < PlayerPosition.x && PlayerPosition.x < 68 && 10.5f < PlayerPosition.y && PlayerPosition.y < 12) {
		PlayerPosition.y = 12.0f;
		Land();
	}
	// 4�i�ڂ̒n�ʂɂ��Ă�����~�܂�i�D�F�u���b�N�̏�j
	if (68 < PlayerPosition.x && PlayerPosition.x < 74 && PlayerPosition.y < 12 && grayBrockFlag[0] == 0) {
		PlayerPosition.y = 12.0f;
		CrushBrockLand();
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
		if (PlayerRotation.y == 720) {
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

// �����蔻��
void TutorialPlayer::Collision()
{
	// ��ʊO�ɏo�Ȃ��悤�ɂ���
	if (PlayerPosition.x < 0) {
		PlayerPosition.x = 0.0f;
	}
	if (93 < PlayerPosition.x) {
		PlayerPosition.x = 93.0f;
	}

	// 1�ڂ̃u���b�N�̓����蔻��i�E�j
	if (30 < PlayerPosition.x && PlayerPosition.x < 31 && PlayerPosition.y < 3 ||
		// 2�ڂ̃u���b�N�̓����蔻��i�E�j
		39 < PlayerPosition.x && PlayerPosition.x < 40 && PlayerPosition.y < 12 ||
		// 3�ڂ̃u���b�N�̓����蔻��i�E�j
		48 < PlayerPosition.x && PlayerPosition.x < 49 && 12 < PlayerPosition.y ||
		// ���F�u���b�N�̓����蔻��i�E�j
		48 < PlayerPosition.x && PlayerPosition.x < 49 && PlayerPosition.y == 12 && brownBrockFlag == 0 ||
		// 4�ڂ̃u���b�N�̓����蔻��i�E�j
		69 < PlayerPosition.x && PlayerPosition.x < 70 && 0 < PlayerPosition.y) {
		CameraPosition.x -= speed;
		PlayerPosition.x -= speed;
	}

	// 1�ڂ̃u���b�N�̓����蔻��i���j
	if (35 < PlayerPosition.x && PlayerPosition.x < 36 && PlayerPosition.y < 3 ||
		// 2�ڂ̃u���b�N�̓����蔻��i���j
		68 < PlayerPosition.x && PlayerPosition.x < 69 && PlayerPosition.y < 12 ||
		// 3�ڂ̃u���b�N�̓����蔻��i���j
		53 < PlayerPosition.x && PlayerPosition.x < 54 && 12 < PlayerPosition.y) {
		CameraPosition.x += speed;
		PlayerPosition.x += speed;
	}
	// 4�ڂ̃u���b�N�̓����蔻��i���j
	if (74 < PlayerPosition.x && PlayerPosition.x < 75 && 0 < PlayerPosition.y) {
		PlayerPosition.x += speed;
	}

	// 1�i�ڂ̒n�ʂ��痎���Ă��܂����ꍇ�i���j
	if (30.5f < PlayerPosition.x && PlayerPosition.x < 31 && PlayerPosition.y < 3 ||
		// 1�i�ڂ̒n�ʂ��痎���Ă��܂����ꍇ�i�E�j
		35 < PlayerPosition.x && PlayerPosition.x < 35.5f && PlayerPosition.y < 3 ||
		// 4�i�ڂ̒n�ʂ��痎���Ă��܂����ꍇ�i���j
		39.5f < PlayerPosition.x && PlayerPosition.x < 40 && 10.5f < PlayerPosition.y && PlayerPosition.y < 12 ||
		// 4�i�ڂ̒n�ʂ��痎���Ă��܂����ꍇ�i�E�j
		68 < PlayerPosition.x && PlayerPosition.x < 68.5f && 10.5f < PlayerPosition.y && PlayerPosition.y < 12) {
		jumpCount = 3;
	}

	// 1�ڂ̃W�����v�s�n�тɂ���ꍇ
	if (49 < PlayerPosition.x && PlayerPosition.x < 53 && 12 < PlayerPosition.y) {
		PlayerPosition.y = 12.0f;
		jumpPower = 0.0f;
	}
	// 2�ڂ̃W�����v�s�n�тɂ���ꍇ
	if (70 < PlayerPosition.x && PlayerPosition.x < 74 && 0 < PlayerPosition.y) {
		PlayerPosition.y = 0.0f;
		jumpPower = 0.0f;
	}

	// ���F�u���b�N�̓����蔻��
	if (47.8f < PlayerPosition.x && PlayerPosition.y < 13 && attackFlag == 1) {
		brownBrockFlag = 1;
	}
	// �D�F�u���b�N�̓����蔻��
	for (int i = 0; i < 4; i++) {
		if (68 < PlayerPosition.x && PlayerPosition.x < 74 && PlayerPosition.y < GrayBrockPosition[i].y + 4.1f &&
			attackFlag == 2) {
			grayBrockFlag[i] = 1;
		}
	}
}

// �ʏ�u���b�N�̒��n
void TutorialPlayer::Land()
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

// ����u���b�N�̒��n
void TutorialPlayer::CrushBrockLand()
{
	if (jumpCount == 2) {
		PlayerRotation.z = 0.0f;
	}
	jumpPower = 0.0f;
	jumpCount = 0;
}