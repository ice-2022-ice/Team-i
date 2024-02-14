#pragma once
#include"SceneBase.h"
class Rouding : public SceneBase
{
public:
	Rouding();
	virtual ~Rouding();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:

};