#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
private:

private:
	int background_image;		//�w�i�摜
	int menu_image;					//���j���[�摜
	int cursor_image;				//�J�[�\���摜
	int menu_cursor;			//���j���[�J�[�\���ԍ�
	int selectbgm_image;        //�J�[�\���ړ�BGM
	int decisionbgm_image;      //����BGM

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

