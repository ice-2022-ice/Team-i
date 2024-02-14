#include "Rouding.h"
#include"DxLib.h"
#include <math.h>
#include "GameMainScene.h"

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
	//画像の読み込み
	Rouding_image = LoadGraph("Resource/images/title2.bmp");
	
	//エラーチェック
	if (Rouding_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
}

//更新処理
eSceneType Rouding::Update()
{	
	if (timer >=300)
	{
		return eSceneType::E_NGS;
	}
	timer++;
	return GetNowScene();
}

//描画処理
void Rouding::Draw() const
{
	//タイトル画像の描画
	DrawGraph(0, 0, Rouding_image, FALSE);

	//ゲームの説明
	SetFontSize(27);
	DrawString(450, 450, "Now Loading…", 0xffffff, 0);
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



void Rouding::RUD_Data()
{

}