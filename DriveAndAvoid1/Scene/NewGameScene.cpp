#include "NewGameScene.h"
#include"DxLib.h"
#include <math.h>

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
