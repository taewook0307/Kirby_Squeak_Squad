#include "BossMonster.h"
#include "Monster.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

void BossMonster::MonsterSummonReadyStart()
{
	GameEngineSound::SoundPlay("BossShout.wav");
	ChangeAnimationState("MonsterSummonReady");
}

void BossMonster::MonsterSummonJumpStart()
{
	ChangeAnimationState("MonsterSummonJump");
	SetGravityVector(float4::UP * BossJumpPower);
}

void BossMonster::MonsterSummonDropStart()
{
	ChangeAnimationState("MonsterSummonDrop");
}

void BossMonster::MonsterSummonStart()
{
	GameEngineSound::SoundPlay("BossAttack.wav");
	ChangeAnimationState("MonsterSummon");
}

void BossMonster::MonsterSummonReadyUpdate(float _Delta)
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
		ChangeState(BossState::MonsterSummonJump);
		return;
	}
}

void BossMonster::MonsterSummonJumpUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	if (0.0f < GetGravityVector().Y)
	{
		ChangeState(BossState::MonsterSummonDrop);
		return;
	}
}

void BossMonster::MonsterSummonDropUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
		ChangeState(BossState::MonsterSummon);
		return;
	}
}

void BossMonster::MonsterSummonUpdate(float _Delta)
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
		float4 WinScale = GameEngineWindow::MainWindow.GetScale();
		Monster* SummonMonster = GetLevel()->CreateActor<Monster>(UpdateOrder::Monster);
		SummonMonster->SetPos({ WinScale.Half().Half().X, 100.0f });
		SummonMonster->SetGroundBitMap(GetGroundBitMap());

		ChangeState(BossState::Idle);
		return;
	}
}