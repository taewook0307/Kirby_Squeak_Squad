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
	NoDamage = true;
	ChangeAnimationState("Damage");
	SetGravityVector(float4::UP * JumpPower * 0.5f);
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
	Gravity(_Delta);

	if (KirbyHp <= 0)
	{
		ChangeState(KirbyState::Death);
		return;
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	GameEngineCollision* CurCollision = Col[Col.size() - 1];
	GameEngineActor* CollisionMaster = CurCollision->GetActor();

	static float4 CollisionMasterPos = CollisionMaster->GetPos();
	static float4 DamageDirPos = GetPos() - CollisionMasterPos;

	if (DamageDirPos.X < 0.0f)
	{
		Dir = ActorDir::Right;
		MovePos = float4::LEFT * Speed * 0.5f * _Delta;
		CheckPos = LEFTBOTCHECKPOS;
	}
	else
	{
		Dir = ActorDir::Left;
		MovePos = float4::RIGHT * Speed * 0.5f * _Delta;
		CheckPos = RIGHTBOTCHECKPOS;
	}

	ObstacleCheck(MovePos);

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (XColor == EMPTYCOLOR || XColor == DOORCOLOR)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}

	if (GetGravityVector().Y >= 0.0f)
	{
		GravityReset();
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

	else if (true == MainRenderer->IsAnimationEnd() && FLOORCOLOR == Color)
	{
		GravityReset();

		ChangeState(KirbyState::Idle);
		return;
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (Dir == ActorDir::Right)
	{
		MovePos = float4::LEFT * Speed * 0.5f * _Delta;
		CheckPos = LEFTBOTCHECKPOS;
	}
	else
	{
		MovePos = float4::RIGHT * Speed * 0.5f * _Delta;
		CheckPos = RIGHTBOTCHECKPOS;
	}

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (XColor == EMPTYCOLOR || XColor == DOORCOLOR)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}
}

void Kirby::DeathUpdate(float _Delta)
{
	Gravity(_Delta);

	BodyCollision->Off();
	
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	float4 ReStartPos = GetPos();

	if (WinScale.Y < GetPos().Y)
	{
		DeathCheck = true;
		return;
	}
}