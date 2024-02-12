#include "Enemy.h"
#include"DxLib.h"

Enemy::Enemy(int type, int handle):type(type),image(handle),speed(0.0f),location(0.0f),box_size(0.0f)
{

}

Enemy::~Enemy() 
{

}

// 処理化処理
void Enemy::Initialize() 
{
	// 出題させるX座標パターン取得
	float random_x = (float)(GetRand(420) + 40);
	// 生成位置の設定
	location = Vector2D(random_x, -50.0f);
	// あたり判定の設定
	box_size = Vector2D(20.0f, 20.0f);
	// 速さの設定
	speed = (float)(this->type) + (1.f + (float)GetRand(20) / 10.f);
}

void Enemy::Update(float speed) 
{
	// 位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed - 4);
}

void Enemy::Draw()const
{
	// 敵画像描画
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
