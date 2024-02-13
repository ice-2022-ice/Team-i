#include "NewGameScene.h"
#include"DxLib.h"
#include <math.h>
#include "GameMainScene.h"
#include "../Utility/InputControl.h"

NewGameScene::NewGameScene()
{

}

NewGameScene::~NewGameScene()
{

}


//初期化処理
void NewGameScene::Initialize()
{
	//画像の読み込み
	
	NGS_Data();
	//エラーチェック
	/*if ( == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}*/
}
//更新処理
eSceneType NewGameScene::Update()
{
	return GetNowScene();
}

//描画処理
void NewGameScene::Draw() const
{
	SetFontSize(16);
	DrawString(20, 120, "ニューゲーム画面", 0xffffff, 0);

	DrawFormatString(510, 20, GetColor(255, 255, 255), "パワー");
	DrawFormatString(560, 22, 0xffffff, "=%6d", power);
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

void NewGameScene::NGS_Data()
{
	//ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/power_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("resource/dat/power_data.csvが読み込めません\n");
	}

	//結果を読み込む
	fscanf_s(fp, "%6d,\n", &power);

	//ファイルクローズ
	fclose(fp);
}
