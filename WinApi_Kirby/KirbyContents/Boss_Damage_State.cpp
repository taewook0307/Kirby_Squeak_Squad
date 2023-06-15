#include "BossMonster.h"

void BossMonster::DamageStart()
{
	NoDamage = true;
	ChangeAnimationState("Damage");
}

void BossMonster::DeathStart()
{
	ChangeAnimationState("Death");
}

void BossMonster::DamageUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	static float DamageTimer = 0.0f;

	if (1.0f < DamageTimer)
	{
		DamageTimer = 0.0f;
		ChangeState(BossState::Idle);
		return;
	}

	DamageTimer += _Delta;
}

void BossMonster::DeathUpdate(float _Delta)
{

}