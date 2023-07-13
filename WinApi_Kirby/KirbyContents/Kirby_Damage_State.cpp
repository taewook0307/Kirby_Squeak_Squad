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
	GameEngineSound::SoundPlay("Damage.wav");
	SetGravityVector(float4::UP * JumpPower * 0.5f);
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

	float4 CollisionMasterPos = CollisionMaster->GetPos();
	float4 DamageDirPos = GetPos() - CollisionMasterPos;

	if (DamageDirPos.X < 0.0f)
	{
		Dir = ActorDir::Right;
		MovePos = float4::LEFT * Speed * 0.7f * _Delta;
		CheckPos = LEFTBOTCHECKPOS;
	}
	else if(DamageDirPos.X >= 0.0f)
	{
		Dir = ActorDir::Left;
		MovePos = float4::RIGHT * Speed * 0.7f * _Delta;
		CheckPos = RIGHTBOTCHECKPOS;
	}

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (XColor == EMPTYCOLOR || XColor == DOORCOLOR)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}

	else
	{
		GravityReset();

		ChangeState(KirbyState::Idle);
		return;
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