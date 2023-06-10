#pragma once

#include "ActorEnum.h"

#include <GameEngineCore/GameEngineLevel.h>

class SubLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SubLevel();
	~SubLevel();

	// delete Function
	SubLevel(const SubLevel& _Other) = delete;
	SubLevel(SubLevel&& _Other) noexcept = delete;
	SubLevel& operator=(const SubLevel& _Other) = delete;
	SubLevel& operator=(SubLevel&& _Other) noexcept = delete;

	static int GetPlayerLife();

protected:
	static void SetLevelPlayerForm(const MonsterType& _Value);

	static MonsterType& GetLevelPlayerForm();

	static int PlayerLifeCount;

	static void MinusPlayerLife();
private:
	static MonsterType LevelPlayerForm;
};