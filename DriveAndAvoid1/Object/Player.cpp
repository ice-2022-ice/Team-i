#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), time(0.0f)
{

}

Player::~Player()
{

}

//����������
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 430.0f);
	box_size = Vector2D(20.0f, 20.0f);
	angle = 0.0f;
	time = 1800;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/bakuha.png");//car1pol.bmp

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/bakuha.bmp������܂���B\n");
	}
}

//�X�V����
void Player::Update()
{

	//�R���̏���
	time--;

	//�ړ�����
	Movement();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}
}

//�`�揈��
void Player::Draw()
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
}

//�I������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�����蔻��̑傫���̎擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//�R���擾����
float Player::GetTime() const
{
	return this->time;
}
//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//�\���ړ�����
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		move += Vector2D(-4.5f, 0.0f);
		angle = -DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(4.5f, 0.0f);
		angle = DX_PI_F / 18;
	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}