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

protected:
	static MonsterType LevelPlayerForm;

private:

};