#pragma once

#include "ActorEnum.h"

#include <GameEngineCore/GameEngineLevel.h>

class KirbyUI;
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

	static MonsterType& GetLevelPlayerForm();
	
	static void PlusPlayerLife();

protected:
	static void SetLevelPlayerForm(const MonsterType& _Value);

	static int PlayerLifeCount;

	static void MinusPlayerLife();

private:
	static MonsterType LevelPlayerForm;

	static KirbyUI* LevelPlayerUI;
};