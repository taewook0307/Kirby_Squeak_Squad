#pragma once

#include "SubLevel.h"

class Monster;
class HealItem;
class Obstacle;
class SecondStageLevel : public SubLevel
{
public:
	// constrcuter destructer
	SecondStageLevel();
	~SecondStageLevel();

	// delete Function
	SecondStageLevel(const SecondStageLevel& _Other) = delete;
	SecondStageLevel(SecondStageLevel&& _Other) noexcept = delete;
	SecondStageLevel& operator=(const SecondStageLevel& _Other) = delete;
	SecondStageLevel& operator=(SecondStageLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;

	class BackGround* Back = nullptr;

	Monster* LevelMonster = nullptr;
	Monster* CheetMonster = nullptr;

	HealItem* LevelHealItem = nullptr;

	Obstacle* LevelObstacle = nullptr;
	Obstacle* LevelFloorObstacle1 = nullptr;
	Obstacle* LevelBiggerObstacle = nullptr;
};