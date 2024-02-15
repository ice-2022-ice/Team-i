#pragma once
#include "SceneBase.h"
#include "../Object/Player.h" /*../Object/Player.h*/
#include "../Object/Enemy.h"  /*../Object/Enemy.h*/
#include "DxLib.h"

class GameMainScene:public SceneBase
{
private:
	int power;				// 現在のパワー
	int back_ground;		// 背景画像
	int enemy_kusa;			//草のアイテム画像
	int enemy_hayashi;		//林のアイテム画像
	int enemy_mori;			//森のアイテム画像
	int enemy_image[3];		// 敵画像
	int enemy_count[3];		// 通り過ぎた敵のカウント

	int touchSE[3];  //ぶつかった時のSE
	int mainBGM;     //メイン画面BGM

	Player* player;			// プレイヤー
	Enemy** enemy;			// 敵
public:
	GameMainScene();
	~GameMainScene();



	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	// あたり判定
	bool IsHitCheck(Player* p, Enemy* e);
};

