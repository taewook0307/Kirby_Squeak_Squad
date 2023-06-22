#pragma once

#include "SubLevel.h"

class BossMonster;
class BossUI;
class BossStageLevel : public SubLevel
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
	BossMonster* Boss = nullptr;
	BossUI* BossUIObject = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
};