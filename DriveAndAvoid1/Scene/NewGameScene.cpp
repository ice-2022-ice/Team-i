#include "NewGameScene.h"
#include"DxLib.h"
#include <math.h>

NewGameScene::NewGameScene()
{
	Initialize();
}

NewGameScene::~NewGameScene()
{

}

//初期化処理
void NewGameScene::Initialize()
{
	//パワー決定
	Power = 70.0f;
	Nowpower = 0;

	phase = 1;
	anim_time = 0;

	//画像の読み込み
	int resultStr = LoadDivGraph("Resource/images/Stringimage.png", 2, 2, 1, 100, 100, String_image);
	int resultExp = LoadDivGraph("Resource/images/explosion.png", 16, 4, 4, 32, 32, Explosion_image);
	Back_image = LoadGraph("Resource/images/blowback.png");

	//エラーチェック
	if (resultStr == -1)
	{
		throw("Resource/images/Stringimage.pngがありません\n");
	}

}
//更新処理
eSceneType NewGameScene::Update()
{
	if (phase == 1) 
	{
		if (120 < anim_time) 
		{
			if (0 < Power) 
			{
				Power -= 0.3;
				Nowpower += 0.3;
				if (Power < 0)
				{
					Power = 0;
					anim_time = 0;
				}
			}
			else
			{

			}
		}
	}

	anim_time++;
	return GetNowScene();
}

//描画処理
void NewGameScene::Draw() const
{
	if (phase == 1)
	{
		//背景画像
		DrawGraph(0, 0, Back_image, TRUE);

		//文字画像
		float size = Nowpower * 0.05 + 1;
		int num = anim_time / 4;
		//爆発するまで「爆」の文字を表示
		if (0 < Power || num < 4) DrawRotaGraph(640 / 2 - (50 * size), 480 / 2, size, 0, String_image[0], true);

		//「笑」の文字を表示・移動
		if (0 < Power || anim_time < 12)DrawRotaGraph(640 / 2 + 50, 480 / 2, 1.f, 0, String_image[1], true);
		else DrawRotaGraph(640 / 2 + 50 + (anim_time - 12) * 60, 480 / 2 - (anim_time - 12) * 50, 1.f, (anim_time - 12), String_image[1], true);

		//爆発
		size = Nowpower * 0.05 + 1;
		if (Power <= 0 && num < 16)
		{
			DrawRotaGraph(640 / 2 - (50 * size), 480 / 2, size + 25, 0, Explosion_image[num], true);
		}

		SetFontSize(64);
		DrawFormatString(50, 50, 0xffffff, "%.1f", Power);
	}
}

//終了処理
void NewGameScene::Finalize()
{
	//読み込んだ画像の削除
	/*DeleteGraph();*/
}

//現在のシーン情報取得
eSceneType NewGameScene::GetNowScene() const
{
	return eSceneType::E_NGS;
}

