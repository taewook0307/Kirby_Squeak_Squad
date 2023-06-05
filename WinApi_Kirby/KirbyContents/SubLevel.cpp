#include "SubLevel.h"

MonsterType SubLevel::LevelPlayerForm = MonsterType::Normal;

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