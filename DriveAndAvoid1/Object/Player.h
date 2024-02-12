#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

class Player
{
public:
	Player();
	~Player();

	void Initialize(); //初期化処理
	void Update(); //更新処理
	void Draw();//描画処理
	void Finalize();//終了処理

public:
	void SetActive(bool flg);//有効フラグ
	Vector2D GetLocation() const;//位置座標の取得
	Vector2D GetBoxSize() const;//当たり判定の大きさの取得
	float GetTime() const;//時間取得処理

private:
	bool is_active; //有効常態か？
	int image;		//画像データ
	Vector2D location;//位置座標
	Vector2D box_size;//当たり判定の大きさ
	float angle;//角度
	float time;//時間

private:
	void Movement();//移動処理
};