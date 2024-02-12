#pragma once
#include "SceneBase.h"
#include "../Object/Player.h" /*../Object/Player.h*/
#include "../Object/Enemy.h"  /*../Object/Enemy.h*/

class GameMainScene:public SceneBase
{
private:
	int power;				// ���݂̃p���[
	int back_ground;		// �w�i�摜
	int enemy_image[3];		// �G�摜
	int enemy_count[3];		// �ʂ�߂����G�̃J�E���g
	Player* player;			// �v���C���[
	Enemy** enemy;			// �G
public:
	GameMainScene();
	~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	// �����蔻��
	bool IsHitCheck(Player* p, Enemy* e);
};
