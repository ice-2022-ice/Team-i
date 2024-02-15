#include "Eventobj.h"
#include "../Utility/InputControl.h"
#include <cmath>
#include "DxLib.h"

Eventobj::Eventobj() : location(0.0f)
{
	int resultExp = LoadDivGraph("Resource/images/explosion.png", 16, 4, 4, 32, 32, Explosion_image);
	int resultImg = LoadDivGraph("Resource/images/flyobj.png", 5, 5, 1, 100, 100, image);
}

Eventobj::~Eventobj()
{

}

//����������
void Eventobj::Initialize(float power, bool active, int rank)
{
	//�L��������Z�b�g
	this->active = active;

	//�����ʒu�ݒ�
	location = Vector2D(960.0f, 480.f / 2 - 500.f);

	//���_�{���ݒ�
	this->rank = rank + 1;
	score = 0;

	if (power <= 0)
	{
		location.y = 480.f / 2 + 500.f;
	}

	//�A�j���[�V�������Z�b�g
	anim_time = 0;
}

//�X�V����
void Eventobj::Update(float Accel)
{
	//�ړ�����
	Movement(Accel);

	if (active)
	{
		int disX = 640 / 2 - location.x;
		int disY = 480 / 2 - location.y;

		if (abs(disX) < 30 && abs(disY) < 30) 
		{
			active = false;
			score = rank * 1500;
		}
	}
	else
	{
		anim_time++;
	}
}

//�`�揈��
void Eventobj::Draw()
{
	int num = anim_time / 1;

	//�摜�̕`��
	if (num < 5)DrawRotaGraphF(location.x, location.y, 2, 0, image[rank - 1], TRUE);

	//�����摜
	if (!active && num < 16)DrawRotaGraph(location.x, location.y, 10, 0, Explosion_image[num], true);

	//���_�e�L�X�g
	if (!active && anim_time < 45) 
	{
		SetFontSize(30);
		switch (rank)
		{
		case 1:
			DrawString(50, 110, "�� + 1500", 0xffffff);
			break;
		case 2:
			DrawString(50, 110, "�J���� + 3000", 0xffffff);
			break;
		case 3:
			DrawString(50, 110, "�E�� + 4500", 0xffffff);
			break;
		case 4:
			DrawString(50, 110, "�h���S�� + 6000", 0xffffff);
			break;
		case 5:
			DrawString(50, 110, "UFO + 7500", 0xffffff);
			break;
		default:
			break;
		}
	}
}

//�I������
void Eventobj::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	delete image;
}

//�ړ�����
void Eventobj::Movement(float Accel)
{
	Vector2D move = Vector2D(-abs(Accel) * 2 * 1.3, Accel * 2);

	location += move;
}

//�X�R�A�l��
int Eventobj::GetScore()
{
	int score = this->score;

	//�Z�b�g�����X�R�A�����Z�b�g����
	this->score = 0;

	//�l���X�R�A��Ԃ�
	return score;
}