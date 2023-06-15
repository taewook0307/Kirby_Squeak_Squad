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
	NoDamage = true;

	unsigned int Color = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	if (GetGravityVector().Y >= 0.0f)
	{
		GravityReset();
		ChangeState(KirbyState::DamageLand);
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

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	float4 ReStartPos = GetPos();

	if (WinScale.Y < GetPos().Y)
	{
		DeathCheck = true;
		return;
	}
}