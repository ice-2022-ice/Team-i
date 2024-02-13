﻿#pragma once
#include"SceneBase.h"
class NewGameScene : public SceneBase
{
private:
	float Power;	//渡されたパワー
	float Nowpower;	//現在パワー

	int Record;		//記録距離
	int Flying;		//飛行距離

	int String_image[2];			//文字画像
	int Back_image;					//背景画像

	int Explosion_image[16];		//爆発画像

	int anim_time;	//アニメーション時間
	int phase;		//アニメーション段階(1:爆発 2:飛行 3:着地)
			// ���݂̃p���[
				
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

