﻿#pragma once
#include"SceneBase.h"
#include "../Object/Eventobj.h" /*../Object/Player.h*/

class NewGameScene : public SceneBase
{
private:
	float Power;	//渡されたパワー
	float Nowpower;	//現在パワー

	int Record;		//記録距離
	int Flying;		//飛行距離

	int Altitude;	//飛行高度
	float Accel;		//加速度

	int Rand_time;	//ランダムイベントの発生時間

	int String_image[2];			//文字画像
	int Back_image[4];				//背景画像

	int Explosion_image[16];		//爆発画像

	int anim_time;	//アニメーション時間
	int phase;		//アニメーション段階(1:爆発 2:飛行 3:着地)
				
	Eventobj* eventobj;			// イベントオブジェクト

	int boomSE;  //爆発SE
	int bakuSE;  //チャージ前SE
	int resultBGM;//最終結果BGM
	int chageSE;  //チャージ中SE
	int landingSE;//着地SE
	void NGS_Data();

public:
	NewGameScene();
	virtual ~NewGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	
};

