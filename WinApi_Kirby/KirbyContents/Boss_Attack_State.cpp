#include "BossMonster.h"
#include "BossAttackObject.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

void BossMonster::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}

void BossMonster::AttackRunStart()
{
	ChangeAnimationState("AttackRun");
}

void BossMonster::AttackStart()
{
	ChangeAnimationState("Attack");
}

void BossMonster::AttackToIdleStart()
{
	ChangeAnimationState("AttackToIdle");
}

void BossMonster::AttackReadyUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	static float ShoutingTimer = 0.0f;

	if (ShoutingTimer > 2.0f)
	{
		ShoutingTimer = 0.0f;
		ChangeState(BossState::Attack);
		return;
	}

	ShoutingTimer += _Delta;
}

void BossMonster::AttackRunUpdate(float _Delta)
{

}

void BossMonster::AttackUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		BossAttackObject* SummonAttacker = GetLevel()->CreateActor<BossAttackObject>(RenderOrder::Boss);
		SummonAttacker->SetPos(GetPos());
		SummonAttacker->SetGroundBitMap(GetGroundBitMap());

		ChangeState(BossState::AttackToIdle);
		return;
	}
}

void BossMonster::AttackToIdleUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::Idle);
		return;
	}
}