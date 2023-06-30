#pragma once

#include "SubLevel.h"

class ThirdStageLevel : public SubLevel
{
public:
	// constrcuter destructer
	ThirdStageLevel();
	~ThirdStageLevel();

	// delete Function
	ThirdStageLevel(const ThirdStageLevel& _Other) = delete;
	ThirdStageLevel(ThirdStageLevel&& _Other) noexcept = delete;
	ThirdStageLevel& operator=(const ThirdStageLevel& _Other) = delete;
	ThirdStageLevel& operator=(ThirdStageLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;

	class BackGround* Back = nullptr;
};