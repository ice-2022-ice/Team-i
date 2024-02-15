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

//初期化処理
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 430.0f);
	box_size = Vector2D(20.0f, 20.0f);
	angle = 0.0f;
	time = 1800;

	//画像の読み込み
	image = LoadGraph("Resource/images/bakuha.png");//car1pol.bmp

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/bakuha.bmpがありません。\n");
	}
}

//更新処理
void Player::Update()
{

	//燃料の消費
	time--;

	//移動処理
	Movement();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}
}

//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
}

//終了処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//当たり判定の大きさの取得処理
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//燃料取得処理
float Player::GetTime() const
{
	return this->time;
}
//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//十字移動処理
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

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}