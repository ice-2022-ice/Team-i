#pragma once
#include"SceneBase.h"
class Rouding : public SceneBase
{
private:
	int x;
	int y;

	int timer;
	int Rouding_image;
	void RUD_Data();

public:
	Rouding();
	virtual ~Rouding();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	eSceneType GetNowScene() const;

};