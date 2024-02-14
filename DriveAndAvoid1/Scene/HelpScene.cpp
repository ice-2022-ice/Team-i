#include "HelpScene.h"
#include "../utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//����������
void HelpScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/help.bmp");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/help.bmp������܂���\n");
	}
}
//�X�V����
eSceneType HelpScene::Update()
{
	//B�{�^���������ꂽ��^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//�`�揈��
void HelpScene::Draw() const
{
	//�w�i�̕`�揈��
	DrawGraph(0, 0, background_image, FALSE);
	
	//�Q�[���̐���
	SetFontSize(20);
	DrawString(20, 160, "�������ԓ��ɃA�C�e����", 0x000000, 0);
	DrawString(20, 180, "��葱����Q�[���ł�", 0x000000, 0);
	DrawString(20, 200, "�p���[�̌��ƂȂ�A�C�e����", 0x000000, 0);
	DrawString(20, 220, "�W�߂ăX�R�A��@���o���ĉ�����", 0x000000, 0);
	DrawString(20, 240, "���������F�肵�܂�", 0x000000, 0);

	DrawString(150, 450, "---B�{�^���������ă^�C�g���֖߂�---", 0x000000, 0);
}

//�I������
void HelpScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
}

//���݂̃V�[�����擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}