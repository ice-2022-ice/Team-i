#include "Enemy.h"
#include"DxLib.h"

Enemy::Enemy(int type, int handle):type(type),image(handle),speed(0.0f),location(0.0f),box_size(0.0f)
{

}

Enemy::~Enemy() 
{

}

// ����������
void Enemy::Initialize() 
{
	// �o�肳����X���W�p�^�[���擾
	float random_x = (float)(GetRand(420) + 40);
	// �����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	// �����蔻��̐ݒ�
	box_size = Vector2D(20.0f, 20.0f);
	// �����̐ݒ�
	speed = (float)(this->type) + (1.f + (float)GetRand(20) / 10.f);
}

void Enemy::Update(float speed) 
{
	// �ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 4);
}

void Enemy::Draw()const
{
	// �G�摜�`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);

}

void Enemy::Finalize()
{
}

int Enemy::GetType() const
{
	return type;
}

Vector2D Enemy::GetLocation()
{
	return location;
}

Vector2D Enemy::GetBoxSize()
{
	return box_size;
}
