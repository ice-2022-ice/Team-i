#include "NewGameScene.h"
#include"DxLib.h"
#include <math.h>
#include "GameMainScene.h"
#include "../Utility/InputControl.h"

NewGameScene::NewGameScene()
{

}

NewGameScene::~NewGameScene()
{

}


//����������
void NewGameScene::Initialize()
{
	//�摜�̓ǂݍ���
	
	NGS_Data();
	//�G���[�`�F�b�N
	/*if ( == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}*/
}
//�X�V����
eSceneType NewGameScene::Update()
{
	return GetNowScene();
}

//�`�揈��
void NewGameScene::Draw() const
{
	SetFontSize(16);
	DrawString(20, 120, "�j���[�Q�[�����", 0xffffff, 0);

	DrawFormatString(510, 20, GetColor(255, 255, 255), "�p���[");
	DrawFormatString(560, 22, 0xffffff, "=%6d", power);
}

//�I������
void NewGameScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	/*DeleteGraph();*/
}

//���݂̃V�[�����擾
eSceneType NewGameScene::GetNowScene() const
{
	return eSceneType::E_NGS;
}

void NewGameScene::NGS_Data()
{
	//�t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/power_data.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("resource/dat/power_data.csv���ǂݍ��߂܂���\n");
	}

	//���ʂ�ǂݍ���
	fscanf_s(fp, "%6d,\n", &power);

	//�t�@�C���N���[�Y
	fclose(fp);
}
