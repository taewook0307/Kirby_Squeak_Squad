#include "BossMonster.h"

void BossMonster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void BossMonster::WalkStart()
{
	ChangeAnimationState("Walk");
}

void BossMonster::IdleUpdate(float _Delta)
{

}

void BossMonster::WalkUpdate(float _Delta)
{

}