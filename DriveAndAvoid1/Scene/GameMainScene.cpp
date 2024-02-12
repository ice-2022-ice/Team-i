#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>

GameMainScene::GameMainScene() :back_ground(NULL), player(nullptr),
enemy(nullptr) {
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Initialize()
{

	// �摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back.bmp");

	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 30, 30, enemy_image);
	// �G���[�`�F�b�N
	if (back_ground == -1) {
		throw("�摜back.bmp������܂���\n");
	}
	if (result == -1) {
		throw("�摜car.bmp������܂���\n");
	}

	// �I�u�W�F�N�g�̐���
	player = new Player;
	enemy = new Enemy * [10];

	// �I�u�W�F�N�g�̏�����
	player->Initialize();

	for (int i = 0; i < 10; i++) {
		enemy[i] = nullptr;
	}
}

eSceneType GameMainScene::Update()
{
	// �v���C���[�̍X�V
	player->Update();

	// �G��������
	int time = player->GetTime();

	if (time % 25 == 0) {
		for (int i = 0; i < 10; i++) {
			// �l��null�Ȃ�
			if (enemy[i] == nullptr) {
				int type = GetRand(3) % 3;
				enemy[i] = new Enemy(type, enemy_image[type]);
				enemy[i]->Initialize();
				break;
			}
		}
	}

	// �G�̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 10; i++) 
	{
		// �l��null�łȂ��Ȃ�
		if (enemy[i] != nullptr) 
		{
			enemy[i]->Update(5);

			// ��ʊO�ɍs������A�G���������ăX�R�A���Z
			if (enemy[i]->GetLocation().y >= 640.0f) 
			{
				enemy[i]->Finalize();
				delete enemy[i];	// �������J��
				enemy[i] = nullptr;// null�ɂ���
			}

			//�����蔻��̊m�F
			if (IsHitCheck(player, enemy[i]))
			{
				enemy_count[enemy[i]->GetType()]++;
				power += enemy[i]->GetType() + 1;
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

	// �v���C���[�̔R�����̗͂��O�����Ȃ�A���U���g�ɑJ�ڂ���
	if (player->GetTime() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}

void GameMainScene::Draw() const
{
	DrawGraph(0, 0, back_ground, TRUE);

	// �G�̕`��
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	// �v���C���[�̕`��
	player->Draw();

	// UI�̕`��
	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	SetFontSize(16);
	DrawFormatString(510, 20, GetColor(0, 0, 0), "�p���[");
	DrawFormatString(560, 40, GetColor(255, 255, 255), "%d", power);
	DrawFormatString(510, 80, GetColor(0, 0, 0), "��������");

	for (int i = 0; i < 3; i++) 
	{
		DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
		DrawFormatString(510 + (i*50),140,GetColor(255, 255, 255), "%03d",enemy_count[i]);
	}

	// �R���Q�[�W�̕`��
	float fx = 510.0f;
	float fy = 390.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "TIME");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetTime() * 100 / 1800), fy +
		40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
}

void GameMainScene::Finalize()
{
	// ���I�m�ۂ����I�u�W�F�N�g����������
	player->Finalize();
	delete player;

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
	delete[] enemy;
}

// ���݂̃V�[�����擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

// �����蔻�菈���i�v���C���[�ƓG�j
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{

	// �G��񂪂Ȃ���΁A�����蔻��𖳎�����
	if (e == nullptr) {
		return false;
	}

	// �ʒu���̍����擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	// �����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
	// �R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����
	return ((fabs(diff_location.x)<box_ex.x)&&(fabsf(diff_location.y)<box_ex.y));
}
