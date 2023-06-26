#include "BossMonster.h"
#include "BossAttackObject.h"
#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

void BossMonster::AttackReadyStart()
{
	GameEngineSound::SoundPlay("BossShout.wav");
	ChangeAnimationState("AttackReady");
}

void BossMonster::AttackRunStart()
{
	ChangeAnimationState("AttackRun");
}

void BossMonster::AttackStart()
{
	GameEngineSound::SoundPlay("BossAttack.wav");
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
		ChangeState(BossState::AttackRun);
		return;
	}

	ShoutingTimer += _Delta;
}

void BossMonster::AttackRunUpdate(float _Delta)
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float MaxPos = GetPos().X;

	float4 KirbyPos = Kirby::GetMainKirby()->GetPos();
	float Distance = static_cast<float>(fabs(GetPos().X - KirbyPos.X));

	if (ActorDir::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * 2.0f * _Delta;
		CheckPos = LEFTCHECKPOS;
		MaxPos = WinScale.Half().Half().X;

		if (GetPos().X <= MaxPos || Distance < 250.0f)
		{
			ChangeState(BossState::Attack);
			return;
		}
		else
		{
			AddPos(MovePos);
		}
	}
	else
	{
		MovePos = float4::RIGHT * Speed * 2.0f * _Delta;
		CheckPos = RIGHTCHECKPOS;
		MaxPos = WinScale.Half().Half().X + WinScale.Half().X;

		if (GetPos().X >= MaxPos || Distance < 250.0f)
		{
			ChangeState(BossState::Attack);
			return;
		}
		else
		{
			AddPos(MovePos);
		}
	}
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
		BossAttackObject* SummonAttacker = GetLevel()->CreateActor<BossAttackObject>(UpdateOrder::Monster);
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