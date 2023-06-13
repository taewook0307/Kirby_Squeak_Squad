#include "BossMonster.h"

void BossMonster::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}

void BossMonster::AttackStart()
{
	ChangeAnimationState("Attack");
}

void BossMonster::AttackToIdleStart()
{
	ChangeAnimationState("AttackToIdle");
}

void BossMonster::AttackReady(float _Delta)
{

}

void BossMonster::AttackUpdate(float _Delta)
{

}

void BossMonster::AttackToIdle(float _Delta)
{

}