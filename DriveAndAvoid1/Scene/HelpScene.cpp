#include "HelpScene.h"
#include "../utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//初期化処理
void HelpScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/help.bmp");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/help.bmpがありません\n");
	}
}
//更新処理
eSceneType HelpScene::Update()
{
	//Bボタンが押されたらタイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//描画処理
void HelpScene::Draw() const
{
	//背景の描画処理
	DrawGraph(0, 0, background_image, FALSE);
	
	//ゲームの説明
	SetFontSize(20);
	DrawString(20, 160, "制限時間内にアイテムを", 0x000000, 0);
	DrawString(20, 180, "取り続けるゲームです", 0x000000, 0);
	DrawString(20, 200, "パワーの源となるアイテムを", 0x000000, 0);
	DrawString(20, 220, "集めてスコアを叩き出して下さい", 0x000000, 0);
	DrawString(20, 240, "検討をお祈りします", 0x000000, 0);

	DrawString(150, 450, "---Bボタンを押してタイトルへ戻る---", 0x000000, 0);
}

//終了処理
void HelpScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報取得
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}