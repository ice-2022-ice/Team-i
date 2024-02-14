﻿#include "Rouding.h"
#include <DxLib.h>

Rouding::Rouding() : Rouding_image(NULL)
{
	timer = 0;
}


Rouding::~Rouding()
{

}

//初期化処理
void Rouding::Initialize()
{
	Rouding_image = LoadGraph("Resource/images/title2.bmp");
	if (Rouding_image == -1)
	{
		throw ("Resource/images/title2.bmpがない\n");
	}

}

//更新処理
eSceneType Rouding::Update()
{
	if (timer >= 300)
	{
		return eSceneType::E_NGS;
	}
	timer++;
	return GetNowScene();
}

//描画処理
void Rouding::Draw() const
{
	DrawGraph(0, 0, Rouding_image, FALSE);
	SetFontSize(27);
	DrawString(450, 450, "Now Loading...", 0xffffff, 0);
}

//終了処理
void Rouding::Finalize()
{

}

//現在のシーン情報取得
eSceneType Rouding::GetNowScene() const
{
	return eSceneType::E_RUD;
}