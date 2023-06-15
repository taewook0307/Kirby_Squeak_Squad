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
	if (3.0f < GetLiveTime())
	{
		ChangeState(BossState::Idle);
		return;
	}
}

void BossMonster::DeathUpdate(float _Delta)
{

}