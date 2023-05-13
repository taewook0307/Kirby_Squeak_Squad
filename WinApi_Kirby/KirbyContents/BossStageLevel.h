#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class BossStageLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BossStageLevel();
	~BossStageLevel();

	// delete Function
	BossStageLevel(const BossStageLevel& _Other) = delete;
	BossStageLevel(BossStageLevel&& _Other) noexcept = delete;
	BossStageLevel& operator=(const BossStageLevel& _Other) = delete;
	BossStageLevel& operator=(BossStageLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};