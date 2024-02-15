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

//初期化処理
void Eventobj::Initialize(float power, bool active, int rank)
{
	//有効判定をセット
	this->active = active;

	//初期位置設定
	location = Vector2D(960.0f, 480.f / 2 - 500.f);

	//得点倍率設定
	this->rank = rank + 1;
	score = 0;

	if (power <= 0)
	{
		location.y = 480.f / 2 + 500.f;
	}

	//アニメーションリセット
	anim_time = 0;
}

//更新処理
void Eventobj::Update(float Accel)
{
	//移動処理
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

//描画処理
void Eventobj::Draw()
{
	int num = anim_time / 1;

	//画像の描画
	if (num < 5)DrawRotaGraphF(location.x, location.y, 2, 0, image[rank - 1], TRUE);

	//爆発画像
	if (!active && num < 16)DrawRotaGraph(location.x, location.y, 10, 0, Explosion_image[num], true);

	//得点テキスト
	if (!active && anim_time < 45) 
	{
		SetFontSize(30);
		switch (rank)
		{
		case 1:
			DrawString(50, 110, "鳩 + 1500", 0xffffff);
			break;
		case 2:
			DrawString(50, 110, "カモメ + 3000", 0xffffff);
			break;
		case 3:
			DrawString(50, 110, "忍者 + 4500", 0xffffff);
			break;
		case 4:
			DrawString(50, 110, "ドラゴン + 6000", 0xffffff);
			break;
		case 5:
			DrawString(50, 110, "UFO + 7500", 0xffffff);
			break;
		default:
			break;
		}
	}
}

//終了処理
void Eventobj::Finalize()
{
	//読み込んだ画像を削除
	delete image;
}

//移動処理
void Eventobj::Movement(float Accel)
{
	Vector2D move = Vector2D(-abs(Accel) * 2 * 1.3, Accel * 2);

	location += move;
}

//スコア獲得
int Eventobj::GetScore()
{
	int score = this->score;

	//セットしたスコアをリセットする
	this->score = 0;

	//獲得スコアを返す
	return score;
}