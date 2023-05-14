#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class ThirdStageLevel : public GameEngineLevel
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

};

