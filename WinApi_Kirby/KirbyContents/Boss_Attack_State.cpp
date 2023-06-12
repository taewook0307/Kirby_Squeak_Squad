#include "BossMonster.h"

void BossMonster::SearchStart()
{
	ChangeAnimationState("Search");
}

void BossMonster::AttackSummonStart()
{
	ChangeAnimationState("AttackSummon");
}

void BossMonster::AttackStart()
{
	ChangeAnimationState("Attack");
}

void BossMonster::MonsterSummonStart()
{
	ChangeAnimationState("MonsterSummon");
}

void BossMonster::SearchUpdate(float _Delta)
{

}

void BossMonster::AttackSummonUpdate(float _Delta)
{

}

void BossMonster::AttackUpdate(float _Delta)
{

}

void BossMonster::MonsterSummonUpdate(float _Delta)
{

}