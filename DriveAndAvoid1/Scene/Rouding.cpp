#include "Rouding.h"
#include"DxLib.h"
#include <math.h>
#include "GameMainScene.h"

Rouding::Rouding() : Rouding_image(NULL)
{
	timer = 0;
}
	

Rouding::~Rouding()
{

}

//����������
void Rouding::Initialize()
{
	//�摜�̓ǂݍ���
	Rouding_image = LoadGraph("Resource/images/title2.bmp");
	
	//�G���[�`�F�b�N
	if (Rouding_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
}

//�X�V����
eSceneType Rouding::Update()
{	
	if (timer >=300)
	{
		return eSceneType::E_NGS;
	}
	timer++;
	return GetNowScene();
}

//�`�揈��
void Rouding::Draw() const
{
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, Rouding_image, FALSE);

	//�Q�[���̐���
	SetFontSize(27);
	DrawString(450, 450, "Now Loading�c", 0xffffff, 0);
}

//�I������
void Rouding::Finalize()
{

}

//���݂̃V�[�����擾
eSceneType Rouding::GetNowScene() const
{
	return eSceneType::E_RUD;
}



void Rouding::RUD_Data()
{

}