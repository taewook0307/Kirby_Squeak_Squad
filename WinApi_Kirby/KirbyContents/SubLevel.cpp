#include "SubLevel.h"

MonsterType SubLevel::LevelPlayerForm = MonsterType::Normal;

int SubLevel::PlayerLifeCount = 3;

SubLevel::SubLevel()
{
}

SubLevel::~SubLevel()
{
}

void SubLevel::SetLevelPlayerForm(const MonsterType& _Value)
{
	LevelPlayerForm = _Value;
}

MonsterType& SubLevel::GetLevelPlayerForm()
{
	return LevelPlayerForm;
}

int SubLevel::GetPlayerLife()
{
	return PlayerLifeCount;
}

void SubLevel::MinusPlayerLife()
{
	--PlayerLifeCount;
}