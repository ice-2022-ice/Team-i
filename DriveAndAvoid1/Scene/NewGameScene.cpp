#include "NewGameScene.h"
#include"DxLib.h"
#include <math.h>

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
