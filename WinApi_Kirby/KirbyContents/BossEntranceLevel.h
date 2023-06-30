#pragma once

#include "SubLevel.h"

class HealItem;
class BossEntranceLevel : public SubLevel
{
public:
	// constrcuter destructer
	BossEntranceLevel();
	~BossEntranceLevel();

	// delete Function
	BossEntranceLevel(const BossEntranceLevel& _Other) = delete;
	BossEntranceLevel(BossEntranceLevel&& _Other) noexcept = delete;
	BossEntranceLevel& operator=(const BossEntranceLevel& _Other) = delete;
	BossEntranceLevel& operator=(BossEntranceLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;

	HealItem* HealItem1 = nullptr;
	HealItem* HealItem2 = nullptr;
};

