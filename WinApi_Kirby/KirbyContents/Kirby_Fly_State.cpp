#include "Kirby.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

void Kirby::BreatheStart()
{
	ChangeAnimationState("Breathe");
	SetGravityVector(float4::UP * FlyPower * 0.5f);
	GameEngineSound::SoundPlay("Breathe.wav");
}

void Kirby::FlyStart()
{	
	ChangeAnimationState("Fly");
	SetGravityVector(float4::UP * FlyPower);
	GameEngineSound::SoundPlay("Fly.wav");
}

void Kirby::BreatheOutStart()
{
	ChangeAnimationState("BreatheOut");
	GameEngineSound::SoundPlay("BreatheOut.wav");
}

void Kirby::DropStart()
{
	ChangeAnimationState("Drop");
	DropStartPos = GetPos();
}

void Kirby::FlyToLandStart()
{
	ChangeAnimationState("FlyToLand");
}

void Kirby::FlyToTurnUpStart()
{
	ChangeAnimationState("FlyToTurnUp");
	SetGravityVector(float4::UP * JumpPower * 0.5f);
	GameEngineSound::SoundPlay("Drop.wav");
}

void Kirby::FlyToTurnLandStart()
{
	ChangeAnimationState("FlyToTurnLand");
}

// 공기 들이마시는 상태
void Kirby::BreatheUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		FlyGravity(_Delta);
	}
	else if (FLOORCOLOR == Color || true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GravityReset();
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Fly);
		return;
	}
}

// 비행 상태
void Kirby::FlyUpdate(float _Delta)
{
	DirCheck();

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (GetGravityVector().Y > 0.0f)
	{
		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			FlyGravity(_Delta);
		}
		else
		{
			GravityReset();

			unsigned int CheckColor = GetGroundColor(EMPTYCOLOR, float4::UP);

			while (FLOORCOLOR == CheckColor)
			{
				CheckColor = GetGroundColor(EMPTYCOLOR, float4::UP);
				AddPos(float4::UP);
			}
		}
	}
	else
	{
		FlyGravity(_Delta);
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	
	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}

	ObstacleCheck(MovePos);

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == XColor || DOORCOLOR == XColor)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{

		GameEngineSound::SoundPlay("Fly.wav");
		SetGravityVector(float4::UP * FlyPower);
	}

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(KirbyState::BreatheOut);
		return;
	}
}

// 공중에서 낙하하기 위해 공기를 내뱉는 상태
void Kirby::BreatheOutUpdate(float _Delta)
{
	KirbyGravity(_Delta);

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Drop);
		return;
	}
}

// 낙하 상태
void Kirby::DropUpdate(float _Delta)
{
	DirCheck();

	KirbyGravity(_Delta);

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(KirbyState::Breathe);
		return;
	}

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(KirbyState::AttackReady);
		return;
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (FLOORCOLOR == Color || true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		LandPos = GetPos();

		float DropDistance = static_cast<float>(fabs(DropStartPos.Y - LandPos.Y));

		if (DropDistance > 400.0f)
		{
			GravityReset();
			ChangeState(KirbyState::FlyToTurnUp);
			return;
		}
		else
		{
			if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
			{
				ChangeState(KirbyState::Walk);
				return;
			}

			ChangeState(KirbyState::FlyToLand);
			return;
		}
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTCHECKPOS;
	}

	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTCHECKPOS;
	}

	ObstacleCheck(MovePos);

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == XColor || DOORCOLOR == XColor)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}
}

// 바닥에 부딪힌 후 턴하면서 살짝 위로 올라가는 상태
void Kirby::FlyToTurnUpUpdate(float _Delta)
{
	DirCheck();

	unsigned int TopColor = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);

	if (EMPTYCOLOR == TopColor || DOORCOLOR == TopColor)
	{
		Gravity(_Delta);
	}
	else
	{
		SetGravityVector(float4::DOWN);
		Gravity(_Delta);
	}

	if (GetGravityVector().Y >= 0.0f)
	{
		ChangeState(KirbyState::FlyToTurnLand);
		return;
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && ActorDir::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * 0.5f * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	if (true == GameEngineInput::IsPress('D') && ActorDir::Right == Dir)
	{
		MovePos = float4::RIGHT * Speed * 0.5f * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}

	ObstacleCheck(MovePos);

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == XColor || DOORCOLOR == XColor)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}
}

// 아래 방향으로 낙하
void Kirby::FlyToTurnLandUpdate(float _Delta)
{
	DirCheck();

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else if(FLOORCOLOR == Color || true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GravityReset();

		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
		{
			ChangeState(KirbyState::Walk);
			return;
		}

		ChangeState(KirbyState::FlyToLand);
		return;
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && ActorDir::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * 0.5f * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	if (true == GameEngineInput::IsPress('D') && ActorDir::Right == Dir)
	{
		MovePos = float4::RIGHT * Speed * 0.5f * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}

	ObstacleCheck(MovePos);

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == XColor || DOORCOLOR == XColor)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}
}

// 착지 상태
void Kirby::FlyToLandUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}