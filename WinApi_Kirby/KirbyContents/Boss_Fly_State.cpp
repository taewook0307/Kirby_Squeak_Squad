#include "BossMonster.h"
#include "BossAttackObject.h"
#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

void BossMonster::FlyReadyStart()
{
	ChangeAnimationState("FlyReady");
}

void BossMonster::FlyUpStart()
{
	ChangeAnimationState("FlyUp");
	GameEngineSound::SoundPlay("Jump.wav");
	SetGravityVector(float4::UP * BossJumpPower);
}

void BossMonster::FlyStart()
{
	ChangeAnimationState("Fly");
}

void BossMonster::FlyDropStart()
{
	ChangeAnimationState("FlyDrop");
}

void BossMonster::FlyReadyUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::FlyUp);
		return;
	}
}

void BossMonster::FlyUpUpdate(float _Delta)
{
	Gravity(_Delta);

	if (GetGravityVector().Y >= 0.0f)
	{
		ChangeState(BossState::Fly);
		return;
	}

}

void BossMonster::FlyUpdate(float _Delta)
{
	size_t CurFrameValue = MainRenderer->GetCurFrame();

	if (1 == CurFrameValue)
	{
		if (FlySoundCount > 0)
		{
			GameEngineSound::SoundPlay("Fly.wav");
			--FlySoundCount;
		}
	}
	else
	{
		FlySoundCount = 1;
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (ActorDir::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == Color)
	{
		AddPos(MovePos);
	}
	else
	{
		ChangeState(BossState::FlyDrop);
		return;
	}

	float KirbyPosX = Kirby::GetMainKirby()->GetPos().X;
	float PosX = GetPos().X;
	float DistanceX = static_cast<float>(fabs(KirbyPosX - PosX));

	if (DistanceX < 30.0f)
	{
		ChangeState(BossState::FlyDrop);
		return;
	}
}

void BossMonster::FlyDropUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		FlyGravity(_Delta);
	}
	else
	{
		GravityReset();
		GameEngineSound::SoundPlay("BossDrop.wav");

		BossAttackObject* LeftObject = GetLevel()->CreateActor<BossAttackObject>(UpdateOrder::Monster);
		LeftObject->SetPos(GetPos() + float4::LEFT * 180.0f);
		LeftObject->MoveOff();
		LeftObject->SetGroundBitMap(GetGroundBitMap());

		BossAttackObject* RightObject = GetLevel()->CreateActor<BossAttackObject>(UpdateOrder::Monster);
		RightObject->SetPos(GetPos() + float4::RIGHT * 180.0f);
		RightObject->MoveOff();
		RightObject->SetGroundBitMap(GetGroundBitMap());

		ChangeState(BossState::Idle);
		return;
	}
}