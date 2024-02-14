#pragma once

#include "SceneBase.h"
#include "NewGameScene.h"

class TitleScene : public SceneBase
{
private:

private:
	int background_image;		//�w�i�摜
	int menu_image;					//���j���[�摜
	int cursor_image;				//�J�[�\���摜
	int menu_cursor;			//���j���[�J�[�\���ԍ�

	int rotate;					//��]������
	int animation;				//�A�j���[�V�����̎���

	int titlebgm;              //�^�C�g����ʂ�BGM
	int selectbgm;             //�J�[�\���ړ���SE
	int decisionbgm;           //���莞��SE

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

