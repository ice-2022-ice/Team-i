#pragma once

#include "../Utility/Vector2D.h"

class Eventobj
{
public:
	Eventobj();
	~Eventobj();

	void Initialize(float power, bool active, int rank); //初期化処理
	void Update(float Accel); //更新処理
	void Draw();//描画処理
	void Finalize();//終了処理

	int GetScore();	//スコア獲得

public:


private:
	int image[5];		//画像データ
	int Explosion_image[16];		//爆発画像
	int anim_time;					//アニメ時間

	Vector2D location;//位置座標

	bool active;	//有効判定

	int rank;		//オブジェクトのスコア倍率
	int score;		//獲得スコア

private:
	void Movement(float Accel);//移動処理
};