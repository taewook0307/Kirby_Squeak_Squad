#pragma once

#include "SubLevel.h"

#include <list>

class Ground;
class Kirby;
class Monster;
class GameEngineRenderer;
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

	Kirby* LevelPlayer = nullptr;
	float4 SavePos = float4::ZERO;
	GameEngineRenderer* FormUI = nullptr;

	Monster* LevelMonster = nullptr;
	Monster* LevelFireMonster = nullptr;
	Monster* LevelTornadoMonster = nullptr;
	Monster* LevelSparkMonster = nullptr;
	Monster* LevelIceMonster = nullptr;
	Ground* FirstStage = nullptr;
	std::list<Monster*> AllLevelMonster;
};