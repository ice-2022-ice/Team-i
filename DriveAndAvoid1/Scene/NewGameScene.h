#pragma once
#include"SceneBase.h"
class NewGameScene : public SceneBase
{
private:
	int power;				// åªç›ÇÃÉpÉèÅ[
	void NGS_Data();
public:
	NewGameScene();
	virtual ~NewGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	
};

