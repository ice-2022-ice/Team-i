#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : background_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0),titlebgm(NULL),selectbgm(NULL),decisionbgm(NULL)
{

}

TitleScene::~TitleScene()
{

}

//����������
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/title2.bmp");

	menu_image = LoadGraph("Resource/images/menu.bmp");

	cursor_image = LoadGraph("Resource/images/cone.bmp");

	//BGM,SE�̓ǂݍ���
	titlebgm = LoadSoundMem("Resource/sounds/maou_bgm_neorock54.mp3");
	selectbgm = LoadSoundMem("Resource/sounds/maou_se_system26.mp3");
	decisionbgm = LoadSoundMem("Resource/sounds/maou_se_system27.mp3");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmp������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp������܂���\n");
	}
	if (titlebgm == -1)
	{
		throw("Resource/sounds/maou_bgm_neorock54.mp3������܂���\n");
	}
	if (selectbgm == -1)
	{
		throw("Resource/sounds/maou_se_system26.mp3������܂���\n");
	}
	if (decisionbgm == -1)
	{
		throw("Resource/sounds/maou_se_system27.mp3������܂���\n");
	}
}

eSceneType TitleScene::Update()
{
	//BGM�̍Đ�
	if (CheckSoundMem(titlebgm) != TRUE)
	{
		PlaySoundMem(titlebgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;

		//BGM������ĂȂ��Ƃ��ɍĐ�
		if (CheckSoundMem(selectbgm) != TRUE)
		{
			PlaySoundMem(selectbgm, DX_PLAYTYPE_BACK, TRUE);
		}
		//��ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}


	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//BGM������ĂȂ��Ƃ��ɍĐ�
		if (CheckSoundMem(selectbgm) != TRUE)
		{
			PlaySoundMem(selectbgm, DX_PLAYTYPE_BACK, TRUE);
		}
		//��ԉ��ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	//�J�[�\������i���肵����ʂɑJ�ڂ���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{

		PlaySoundMem(decisionbgm, DX_PLAYTYPE_BACK, TRUE);
		
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_RANKING_DISP;
		case 2:
			return eSceneType::E_HELP;
		default:
			return eSceneType::E_END;
		}
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//���j���[�摜�̕`��
	DrawGraph(120, 200, menu_image, TRUE);

	//�J�[�\���摜�̕`��
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);


}

//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
	DeleteSoundMem(titlebgm);
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}