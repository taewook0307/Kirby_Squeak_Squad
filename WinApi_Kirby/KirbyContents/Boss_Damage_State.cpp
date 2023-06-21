#include "BossMonster.h"
#include "EndingItem.h"
#include "KirbyGameEnum.h"

#include<GameEngineCore/GameEngineLevel.h>

void BossMonster::DamageStart()
{
	NoDamage = true;
	ChangeAnimationState("Damage");
}

void BossMonster::DeathJumpStart()
{
	ChangeAnimationState("DeathJump");
	SetGravityVector(float4::UP * BossJumpPower * 0.5f);
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

	if (BossHp <= 0)
	{
		ChangeState(BossState::DeathJump);
		return;
	}

	DamageTimer += _Delta;
}

void BossMonster::DeathJumpUpdate(float _Delta)
{
	BossDeath = true;

	unsigned int Color = 0;

	if (GetGravityVector().Y < 0.0f)
	{
		Color = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);
	}
	else
	{
		Color = GetGroundColor(EMPTYCOLOR);
	}

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
		ChangeState(BossState::Death);
		return;
	}
}

void BossMonster::DeathUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();

		if (false == EndingCheck)
		{
			EndingTimer -= _Delta;
		}
	}

	unsigned int UpColor = GetGroundColor(EMPTYCOLOR, float4::UP);

	while (EMPTYCOLOR != UpColor)
	{
		AddPos(float4::UP);
		UpColor = GetGroundColor(EMPTYCOLOR, float4::UP);
	}

	if (EndingTimer < 0.0f)
	{
		EndingCheck = true;
		EndingTimer = 3.0f;
	}

	if (true == EndingCheck && false == EndingItemCreate)
	{
		EndingItem* EndingBox = GetLevel()->CreateActor<EndingItem>(UpdateOrder::PlayerObject);
		EndingBox->SetPos({ WinScale.Half().X, 100.0f });
		EndingBox->SetGroundBitMap(GetGroundBitMap());
		EndingItemCreate = true;
	}
}