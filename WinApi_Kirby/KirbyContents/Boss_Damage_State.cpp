#include "BossMonster.h"

void BossMonster::DamageStart()
{
	ChangeAnimationState("Damage");
}

void BossMonster::DeathStart()
{
	ChangeAnimationState("Death");
}

void BossMonster::DamageUpdate(float _Delta)
{

}

void BossMonster::DeathUpdate(float _Delta)
{

}