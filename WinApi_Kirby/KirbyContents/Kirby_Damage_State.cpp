#include "Kirby.h"
#include "KirbyGameEnum.h"
#include "AttackObject.h"
#include "Monster.h"

#include <math.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

void Kirby::DamageStart()
{
	ChangeAnimationState("Damage");
}

void Kirby::DamageLandStart()
{
	ChangeAnimationState("DamageLand");
}

void Kirby::DeathStart()
{
	ChangeAnimationState("Death");
	SetGravityVector(float4::UP * JumpPower);
}

void Kirby::DamageUpdate(float _Delta)
{
	BodyCollision->Off();
	GravityReset();

	float4 FlyPos = float4::UP * FlyPower * 0.5f * _Delta;
	float4 MovePos = float4::ZERO;
	float4 XCheckPos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	GameEngineCollision* CurMonsterCollision = Col[Col.size() - 1];
	GameEngineActor* CurMonster = CurMonsterCollision->GetActor();
	Monster* ColMonster = dynamic_cast<Monster*>(CurMonster);
	int MonsterAtt = ColMonster->GetMonsterAtt();
	float4 DirPos = GetPos() - CurMonster->GetPos();
	unsigned int Color = 0;
	unsigned int XColor = 0;

	if (FlyPos.Y < 0)
	{
		CheckPos = TOPCHECKPOS;
		Color = GetGroundColor(EMPTYCOLOR, CheckPos);
	}
	else
	{
		Color = GetGroundColor(EMPTYCOLOR);
	}


	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		AddPos(FlyPos);
	}

	if (DirPos.X > 0.0f)
	{
		MovePos = { Speed * _Delta, 0.0f };
		XCheckPos = RIGHTBOTCHECKPOS;
		XColor = GetGroundColor(EMPTYCOLOR, XCheckPos);
	}
	else
	{
		MovePos = { -Speed * _Delta, 0.0f };
		XCheckPos = LEFTBOTCHECKPOS;
		XColor = GetGroundColor(EMPTYCOLOR, XCheckPos);
	}

	if (XColor == EMPTYCOLOR || XColor == DOORCOLOR)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}

	FlyPower -= 25.0f;

	if (true == MainRenderer->IsAnimationEnd() && EMPTYCOLOR != Color
		|| true == MainRenderer->IsAnimationEnd() && DOORCOLOR != Color)
	{
		FlyPower = BASEPOWER;
		Damage(MonsterAtt);

		if (Hp < 0)
		{
			ChangeState(KirbyState::Death);
			return;
		}

		ChangeState(KirbyState::DamageLand);
		return;
	}
}

void Kirby::DamageLandUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}

	if (true == MainRenderer->IsAnimationEnd() && EMPTYCOLOR != Color)
	{
		GravityReset();
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::DeathUpdate(float _Delta)
{
	Gravity(_Delta);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	float4 ReStartPos = GetPos();

	if (WinScale.Y < GetPos().Y)
	{
		DeathCheck = true;
		return;
	}
}