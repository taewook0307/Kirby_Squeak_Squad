#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class Ground;
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
	Ground* BossStage = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};