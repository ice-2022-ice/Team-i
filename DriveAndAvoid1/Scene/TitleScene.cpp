#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : background_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0),titlebgm(NULL),selectbgm(NULL),decisionbgm(NULL)
{

}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/title2.bmp");

	menu_image = LoadGraph("Resource/images/menu.bmp");

	cursor_image = LoadGraph("Resource/images/cone.bmp");

	//BGM,SEの読み込み
	titlebgm = LoadSoundMem("Resource/sounds/maou_bgm_neorock54.mp3");
	selectbgm = LoadSoundMem("Resource/sounds/maou_se_system26.mp3");
	decisionbgm = LoadSoundMem("Resource/sounds/maou_se_system27.mp3");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}
	if (titlebgm == -1)
	{
		throw("Resource/sounds/maou_bgm_neorock54.mp3がありません\n");
	}
	if (selectbgm == -1)
	{
		throw("Resource/sounds/maou_se_system26.mp3がありません\n");
	}
	if (decisionbgm == -1)
	{
		throw("Resource/sounds/maou_se_system27.mp3がありません\n");
	}
}

eSceneType TitleScene::Update()
{
	//BGMの再生
	if (CheckSoundMem(titlebgm) != TRUE)
	{
		PlaySoundMem(titlebgm, DX_PLAYTYPE_LOOP, TRUE);
	}
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;

		//BGMが流れてないときに再生
		if (CheckSoundMem(selectbgm) != TRUE)
		{
			PlaySoundMem(selectbgm, DX_PLAYTYPE_BACK, TRUE);
		}
		//一番下に到達したら、一番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}


	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//BGMが流れてないときに再生
		if (CheckSoundMem(selectbgm) != TRUE)
		{
			PlaySoundMem(selectbgm, DX_PLAYTYPE_BACK, TRUE);
		}
		//一番下に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{

		PlaySoundMem(decisionbgm, DX_PLAYTYPE_BACK, TRUE);
		
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_RANKING_DISP;
		case 2:
			return eSceneType::E_HELP;
		default:
			return eSceneType::E_END;
		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	//タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//メニュー画像の描画
	DrawGraph(120, 200, menu_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);


}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
	DeleteSoundMem(titlebgm);
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}