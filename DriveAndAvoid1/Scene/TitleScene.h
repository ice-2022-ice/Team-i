#pragma once

#include "SceneBase.h"
#include "NewGameScene.h"

class TitleScene : public SceneBase
{
private:

private:
	int background_image;		//背景画像
	int menu_image;					//メニュー画像
	int cursor_image;				//カーソル画像
	int menu_cursor;			//メニューカーソル番号

	int rotate;					//回転させる
	int animation;				//アニメーションの時間

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

