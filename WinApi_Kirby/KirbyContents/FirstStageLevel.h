#pragma once

#include "SubLevel.h"

#include <list>

class Ground;
class Kirby;
class Monster;
class FirstStageLevel : public SubLevel
{
public:
	// constrcuter destructer
	FirstStageLevel();
	~FirstStageLevel();

	// delete Function
	FirstStageLevel(const FirstStageLevel& _Other) = delete;
	FirstStageLevel(FirstStageLevel&& _Other) noexcept = delete;
	FirstStageLevel& operator=(const FirstStageLevel& _Other) = delete;
	FirstStageLevel& operator=(FirstStageLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;

	float4 SavePos = float4::ZERO;
	Kirby* LevelPlayer = nullptr;
	Monster* LevelMonster = nullptr;
	Monster* LevelFireMonster = nullptr;
	Monster* LevelTornadoMonster = nullptr;
	Monster* LevelSparkMonster = nullptr;
	Ground* FirstStage = nullptr;
	std::list<Monster*> AllLevelMonster;
};