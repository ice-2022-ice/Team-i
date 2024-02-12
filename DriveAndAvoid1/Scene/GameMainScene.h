#pragma once
#include "SceneBase.h"
#include "../Object/Player.h" /*../Object/Player.h*/
#include "../Object/Enemy.h"  /*../Object/Enemy.h*/

class GameMainScene:public SceneBase
{
private:
	int power;				// Œ»İ‚Ìƒpƒ[
	int back_ground;		// ”wŒi‰æ‘œ
	int enemy_image[3];		// “G‰æ‘œ
	int enemy_count[3];		// ’Ê‚è‰ß‚¬‚½“G‚ÌƒJƒEƒ“ƒg
	Player* player;			// ƒvƒŒƒCƒ„[
	Enemy** enemy;			// “G
public:
	GameMainScene();
	~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	// ‚ ‚½‚è”»’è
	bool IsHitCheck(Player* p, Enemy* e);
};

