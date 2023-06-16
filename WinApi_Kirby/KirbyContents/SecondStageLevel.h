#pragma once

#include "SubLevel.h"

class Ground;
class Kirby;
class Monster;
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
	
	Ground* SecondStage = nullptr;
	Kirby* LevelPlayer = nullptr;
	Monster* LevelMonster = nullptr;
	float4 SavePos = float4::ZERO;
};