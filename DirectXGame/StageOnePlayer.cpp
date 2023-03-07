#include "StageOnePlayer.h"

// �R���X�g���N�^
StageOnePlayer::StageOnePlayer()
{
}

// �f�X�g���N�^
StageOnePlayer::~StageOnePlayer()
{
	safe_delete(modelPlayerRight);
	safe_delete(modelPlayerLeft);
	safe_delete(modelAttack1);
	safe_delete(modelAttack2);
	safe_delete(modelBrownBrock);
	safe_delete(modelGrayBrock);
	safe_delete(modelBrownEnemy);
	safe_delete(modelGrayEnemy);
	safe_delete(objPlayerRight);
	safe_delete(objPlayerLeft);
	safe_delete(objAttack1);
	safe_delete(objAttack2);
	for (int i = 0; i < 2; i++) {
		safe_delete(objBrownBrock[i]);
	}
	for (int i = 0; i < 4; i++) {
		safe_delete(objGrayBrock[i]);
	}
	for (int i = 0; i < 2; i++) {
		safe_delete(objBrownEnemy[i]);
	}
	safe_delete(objGrayEnemy);
}

// ������
void StageOnePlayer::Initialize(Input* input)
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
	modelBrownEnemy = Model::CreateFromOBJ("brownEnemy");
	modelGrayEnemy = Model::CreateFromOBJ("grayEnemy");

	// 3D�I�u�W�F�N�g����
	objPlayerRight = Object3d::Create(modelPlayerRight);
	objPlayerLeft = Object3d::Create(modelPlayerLeft);
	objAttack1 = Object3d::Create(modelAttack1);
	objAttack2 = Object3d::Create(modelAttack2);
	for (int i = 0; i < 2; i++) {
		objBrownBrock[i] = Object3d::Create(modelBrownBrock);
	}
	for (int i = 0; i < 4; i++) {
		objGrayBrock[i] = Object3d::Create(modelGrayBrock);
	}
	for (int i = 0; i < 2; i++) {
		objBrownEnemy[i] = Object3d::Create(modelBrownEnemy);
	}
	objGrayEnemy = Object3d::Create(modelGrayEnemy);
}

// �X�V
void StageOnePlayer::Update()
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
	for (int i = 0; i < 2; i++) {
		objBrownBrock[i]->Update();
	}
	for (int i = 0; i < 4; i++) {
		objGrayBrock[i]->Update();
	}
	for (int i = 0; i < 2; i++) {
		objBrownEnemy[i]->Update();
	}
	objGrayEnemy->Update();
}

// �`��
void StageOnePlayer::Draw()
{
	if (damageCount % 2 == 0) {
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
	}
	for (int i = 0; i < 2; i++) {
		if (brownBrockFlag[i] == 0) {
			objBrownBrock[i]->Draw();
		}
	}
	for (int i = 0; i < 4; i++) {
		if (grayBrockFlag[i] == 0) {
			objGrayBrock[i]->Draw();
		}
	}
	for (int i = 0; i < 2; i++) {
		if (brownEnemyFlag[i] == 0) {
			objBrownEnemy[i]->Draw();
		}
	}
	if (grayEnemyFlag == 0) {
		objGrayEnemy->Draw();
	}
}

// �Q�b�^�[
void StageOnePlayer::Getter()
{
	// �Q�b�g�^�[�Q�b�g
	camera->GetTarget();

	// �Q�b�g�|�W�V����
	objPlayerRight->GetPosition();
	objPlayerLeft->GetPosition();
	objAttack1->GetPosition();
	objAttack2->GetPosition();
	for (int i = 0; i < 2; i++) {
		objBrownBrock[i]->GetPosition();
	}
	for (int i = 0; i < 4; i++) {
		objGrayBrock[i]->GetPosition();
	}
	for (int i = 0; i < 2; i++) {
		objBrownEnemy[i]->GetPosition();
	}
	objGrayEnemy->GetPosition();

	// �Q�b�g���[�e�[�V����
	objPlayerRight->GetRotation();
	objPlayerLeft->GetRotation();
	for (int i = 0; i < 2; i++) {
		objBrownEnemy[i]->GetRotation();
	}
	objGrayEnemy->GetRotation();

	// �Q�b�g�X�P�[��
	objPlayerRight->GetScale();
	objPlayerLeft->GetScale();
}

// �Z�b�^�[
void StageOnePlayer::Setter()
{
	// �Z�b�g�^�[�Q�b�g
	camera->SetTarget(CameraPosition);

	// �Z�b�g�|�W�V����
	objPlayerRight->SetPosition(PlayerPosition);
	objPlayerLeft->SetPosition(PlayerPosition);
	objAttack1->SetPosition(PlayerPosition);
	objAttack2->SetPosition(PlayerPosition);
	for (int i = 0; i < 2; i++) {
		objBrownBrock[i]->SetPosition(BrownBrockPosition[i]);
	}
	for (int i = 0; i < 4; i++) {
		objGrayBrock[i]->SetPosition(GrayBrockPosition[i]);
	}
	for (int i = 0; i < 2; i++) {
		objBrownEnemy[i]->SetPosition(BrownEnemyPosition[i]);
	}
	objGrayEnemy->SetPosition(GrayEnemyPosition);

	// �Z�b�g���[�e�[�V����
	objPlayerRight->SetRotation(PlayerRotation);
	objPlayerLeft->SetRotation(PlayerRotation);
	for (int i = 0; i < 2; i++) {
		objBrownEnemy[i]->SetRotation(EnemyRotation);
	}
	objGrayEnemy->SetRotation(EnemyRotation);

	// �Z�b�g�X�P�[��
	objPlayerRight->SetScale(PlayerScale);
	objPlayerLeft->SetScale(PlayerScale);
}

// �v���C���[�̃A�N�V����
void StageOnePlayer::PlayerAction()
{
	// �X�e�B�b�N�̓��͂��擾
	Input::StickMove stickMove = input->GetStickMove();

	// ��������
	PlayerPosition.y -= jumpPower;

	// ���������x��������
	jumpPower += 0.01f;

	// �E�ړ�
	if (input->PushKey(DIK_RIGHT) || 42767 < stickMove.lX && input->GetDevJoyStick()) {
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
	if (input->PushKey(DIK_LEFT) || stickMove.lX < 22767 && input->GetDevJoyStick()) {
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
	if (input->PushKey(DIK_LSHIFT) && jumpCount == 0 ||
		input->PushKey(DIK_LSHIFT) && jumpCount == 3 ||
		input->PushButton(4) && jumpCount == 0 && input->GetDevJoyStick() ||
		input->PushButton(4) && jumpCount == 3 && input->GetDevJoyStick()) {
		speed = 0.2f;
	}
	else if (input->PushKey(DIK_LSHIFT) == 0 && jumpCount == 0 ||
		input->PushKey(DIK_LSHIFT) == 0 && jumpCount == 3 ||
		input->PushButton(4) == 0 && jumpCount == 0 && input->GetDevJoyStick() ||
		input->PushButton(4) == 0 && jumpCount == 3 && input->GetDevJoyStick()) {
		speed = 0.1f;
	}

	// 0�i�ڂ̒n�ʂɂ��Ă�����~�܂�
	if (PlayerPosition.y < 0) {
		PlayerPosition.y = 0.0f;
		Land();
	}
	// 1�ڂ�4�i�ڂ̒n�ʂɂ��Ă�����~�܂�
	if (34 < PlayerPosition.x && PlayerPosition.x < 53 && 10.5f < PlayerPosition.y && PlayerPosition.y < 12) {
		PlayerPosition.y = 12.0f;
		Land();
	}
	// 2�ڂ�4�i�ڂ̒n�ʂɂ��Ă�����~�܂�
	if (76 < PlayerPosition.x && PlayerPosition.x < 80 && 10.5f < PlayerPosition.y && PlayerPosition.y < 12) {
		PlayerPosition.y = 12.0f;
		Land();
	}
	// 2�ڂ�4�i�ڂ̒n�ʂɂ��Ă�����~�܂�i�D�F�u���b�N�̏�j
	if (80 < PlayerPosition.x && PlayerPosition.x < 86 && PlayerPosition.y < 12 && grayBrockFlag[0] == 0) {
		PlayerPosition.y = 12.0f;
		CrushBrockLand();
	}

	// �W�����v
	if (input->TriggerKey(DIK_Z) && jumpCount < 2 && speed == 0.2f ||
		input->TriggerButton(0) && jumpCount < 2 && speed == 0.2f && input->GetDevJoyStick()) {
		jumpCount += 1;
		jumpPower = -0.35f;
	}
	else if (input->TriggerKey(DIK_Z) && jumpCount < 2 && speed == 0.1f ||
		input->TriggerButton(0) && jumpCount < 2 && speed == 0.1f && input->GetDevJoyStick()) {
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
	if (input->TriggerKey(DIK_X) && input->PushKey(DIK_DOWN) && jumpCount == 2 && attackFlag == 0 ||
		input->TriggerButton(1) && 42767 < stickMove.lY &&
		jumpCount == 2 && attackFlag == 0 && input->GetDevJoyStick()) {
		attackFlag = 2;
	}
	else if (input->TriggerKey(DIK_X) && attackFlag == 0 || input->TriggerButton(1) && attackFlag == 0) {
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

// �G�l�~�[�̃A�N�V����
void StageOnePlayer::EnemyAction()
{
	// ���ړ�
	if (brownEnemyMoveFlag[0] == 0) {
		BrownEnemyPosition[0].x -= 0.1f;
	}
	if (brownEnemyMoveFlag[1] == 0) {
		BrownEnemyPosition[1].x -= 0.1f;
	}
	if (grayEnemyMoveFlag == 0) {
		GrayEnemyPosition.x -= 0.1f;
	}

	// �E�ړ�
	if (brownEnemyMoveFlag[0] == 1) {
		BrownEnemyPosition[0].x += 0.1f;
	}
	if (brownEnemyMoveFlag[1] == 1) {
		BrownEnemyPosition[1].x += 0.1f;
	}
	if (grayEnemyMoveFlag == 1) {
		GrayEnemyPosition.x += 0.1f;
	}

	// �����]��
	if (BrownEnemyPosition[0].x < 18) {
		brownEnemyMoveFlag[0] = 1;
	}
	if (BrownEnemyPosition[1].x < 36) {
		brownEnemyMoveFlag[1] = 1;
	}
	if (GrayEnemyPosition.x < 54) {
		grayEnemyMoveFlag = 1;
	}
	if (33 < BrownEnemyPosition[0].x) {
		brownEnemyMoveFlag[0] = 0;
	}
	if (51 < BrownEnemyPosition[1].x) {
		brownEnemyMoveFlag[1] = 0;
	}
	if (69 < GrayEnemyPosition.x) {
		grayEnemyMoveFlag = 0;
	}

	// ��]
	EnemyRotation.y += 3.6f;
	if (EnemyRotation.y == 360) {
		EnemyRotation.y = 0.0f;
	}
}

// �����蔻��
void StageOnePlayer::Collision()
{
	// ��ʊO�ɏo�Ȃ��悤�ɂ���
	if (PlayerPosition.x < 0) {
		PlayerPosition.x = 0.0f;
	}
	if (93 < PlayerPosition.x) {
		PlayerPosition.x = 93.0f;
	}

	// ���F�u���b�N[0]�̓����蔻��i�E�j
	if (12 < PlayerPosition.x && PlayerPosition.x < 13 && brownBrockFlag[0] == 0 ||
		// 4�ڂ̃u���b�N�̓����蔻��i�E�j
		75 < PlayerPosition.x && PlayerPosition.x < 76 && PlayerPosition.y < 12 ||
		// 5�ڂ̃u���b�N�̓����蔻��i�E�j
		81 < PlayerPosition.x && PlayerPosition.x < 82 && 0 < PlayerPosition.y) {
		PlayerPosition.x -= speed;
	}
	// 2�ڂ̃u���b�N�̓����蔻��i�E�j
	if (33 < PlayerPosition.x && PlayerPosition.x < 34 && PlayerPosition.y < 12 ||
		// ���F�u���b�N[1]�̓����蔻��i�E�j
		69 < PlayerPosition.x && PlayerPosition.x < 70 && PlayerPosition.y == 0 && brownBrockFlag[1] == 0 ||
		// 3�ڂ̃u���b�N�̓����蔻��i�E�j
		69 < PlayerPosition.x && PlayerPosition.x < 70 && 0 < PlayerPosition.y) {
		CameraPosition.x -= speed;
		PlayerPosition.x -= speed;
	}

	// 1�ڂ̃u���b�N�̓����蔻��i���j
	if (17 < PlayerPosition.x && PlayerPosition.x < 18 && 0 < PlayerPosition.y ||
		// 3�ڂ̃u���b�N�̓����蔻��i���j
		74 < PlayerPosition.x && PlayerPosition.x < 75 && 0 < PlayerPosition.y ||
		// 4�ڂ̃u���b�N�̓����蔻��i���j
		80 < PlayerPosition.x && PlayerPosition.x < 81 && PlayerPosition.y < 12 ||
		// 5�ڂ̃u���b�N�̓����蔻��i���j
		86 < PlayerPosition.x && PlayerPosition.x < 87 && 0 < PlayerPosition.y) {
		PlayerPosition.x += speed;
	}
	// 2�ڂ̃u���b�N�̓����蔻��i���j
	if (53 < PlayerPosition.x && PlayerPosition.x < 54 && PlayerPosition.y < 12) {
		CameraPosition.x += speed;
		PlayerPosition.x += speed;
	}

	// 1�ڂ�4�i�ڂ̒n�ʂ��痎���Ă��܂����ꍇ�i���j
	if (33.5f < PlayerPosition.x && PlayerPosition.x < 34 && 10.5f < PlayerPosition.y && PlayerPosition.y < 12 ||
		// 1�ڂ�4�i�ڂ̒n�ʂ��痎���Ă��܂����ꍇ�i�E�j
		53 < PlayerPosition.x && PlayerPosition.x < 53.5f && 10.5f < PlayerPosition.y && PlayerPosition.y < 12 ||
		// 2�ڂ�4�i�ڂ̒n�ʂ��痎���Ă��܂����ꍇ�i���j
		75.5f < PlayerPosition.x && PlayerPosition.x < 76 && 10.5f < PlayerPosition.y && PlayerPosition.y < 12 || 
		// 2�ڂ�4�i�ڂ̒n�ʂ��痎���Ă��܂����ꍇ�i�E�j
		80 < PlayerPosition.x && PlayerPosition.x < 80.5f && 10.5f < PlayerPosition.y && PlayerPosition.y < 12) {
		jumpCount = 3;
	}

	// 1�ڂ̃W�����v�s�n�тɂ���ꍇ
	if (PlayerPosition.x < 17 && 0 < PlayerPosition.y) {
		PlayerPosition.y = 0.0f;
		jumpPower = 0.0f;
	}
	// 2�ڂ̃W�����v�s�n�тɂ���ꍇ
	if (70 < PlayerPosition.x && PlayerPosition.x < 74 && 0 < PlayerPosition.y) {
		PlayerPosition.y = 0.0f;
		jumpPower = 0.0f;
	}
	// 3�ڂ̃W�����v�s�n�тɂ���ꍇ
	if (82 < PlayerPosition.x && PlayerPosition.x < 86 && 0 < PlayerPosition.y) {
		PlayerPosition.y = 0.0f;
		jumpPower = 0.0f;
	}

	// ���F�u���b�N[0]�̓����蔻��
	if (11.8f < PlayerPosition.x && attackFlag == 1) {
		brownBrockFlag[0] = 1;
	}
	// ���F�u���b�N[1]�̓����蔻��
	if (68.8f < PlayerPosition.x && PlayerPosition.y < 1 && attackFlag == 1) {
		brownBrockFlag[1] = 1;
	}

	// �D�F�u���b�N�̓����蔻��
	for (int i = 0; i < 4; i++) {
		if (80 < PlayerPosition.x && PlayerPosition.x < 86 && PlayerPosition.y < GrayBrockPosition[i].y + 4.1f &&
			attackFlag == 2) {
			grayBrockFlag[i] = 1;
		}
	}

	// �G�l�~�[�̓����蔻��
	/*if (BrownEnemyPosition[0].x - 2 < PlayerPosition.x && PlayerPosition.x <
		BrownEnemyPosition[0].x + 2 && PlayerPosition.y < 3 && brownEnemyFlag[0] == 0) {
		if (attackFlag == 0 && damageCount == 0) {
			damageCount = 60;
		}
		if (0 < attackFlag) {
			brownEnemyFlag[0] = 1;
		}
	}
	if (BrownEnemyPosition[1].x - 2 < PlayerPosition.x && PlayerPosition.x <
		BrownEnemyPosition[1].x + 2 && PlayerPosition.y < 15 && brownEnemyFlag[1] == 0) {
		if (attackFlag == 0 && damageCount == 0) {
			damageCount = 60;
		}
		if (0 < attackFlag) {
			brownEnemyFlag[1] = 1;
		}
	}
	if (GrayEnemyPosition.x - 2 < PlayerPosition.x && PlayerPosition.x <
		GrayEnemyPosition.x + 2 && PlayerPosition.y < 3 && grayEnemyFlag == 0) {
		if (attackFlag == 0 && damageCount == 0) {
			damageCount = 60;
		}
		if (attackFlag == 2) {
			grayEnemyFlag = 1;
		}
	}*/

	// �_���[�W�֌W
	if (0 < damageCount) {
		damageCount--;
	}
}

// �ʏ�u���b�N�̒��n
void StageOnePlayer::Land()
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
void StageOnePlayer::CrushBrockLand()
{
	if (jumpCount == 2) {
		PlayerRotation.z = 0.0f;
	}
	jumpPower = 0.0f;
	jumpCount = 0;
}