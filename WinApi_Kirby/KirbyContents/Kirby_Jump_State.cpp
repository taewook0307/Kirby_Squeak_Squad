#include "Kirby.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

void Kirby::JumpStart()
{
	ChangeAnimationState("Jump");
	SetGravityVector(float4::UP * JumpPower);
	GameEngineSound::SoundPlay("Jump.wav");
}

void Kirby::JumpToDropStart()
{
	ChangeAnimationState("JumpToDrop");
}

void Kirby::JumpToLandStart()
{
	ChangeAnimationState("JumpToLand");
}

void Kirby::JumpUpdate(float _Delta)
{
	DirCheck();

	unsigned int Color = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
		ChangeState(KirbyState::JumpToDrop);
		return;
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

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(KirbyState::Breathe);
		return;
	}

	if (true == GameEngineInput::IsPress('C'))
	{
		GravityReset();
		ChangeState(KirbyState::AttackReady);
		return;
	}

	if (GetGravityVector().Y >= 0.0f)
	{
		GravityReset();
		ChangeState(KirbyState::JumpToDrop);
		return;
	}
}

void Kirby::JumpToDropUpdate(float _Delta)
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

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
		{
			MovePos = { -Speed * _Delta, 0.0f };
			CheckPos = LEFTBOTCHECKPOS;
		}

		if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
		{
			MovePos = { Speed * _Delta, 0.0f };
			CheckPos = RIGHTBOTCHECKPOS;
		}

		ObstacleCheck(MovePos);

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}
	else
	{
		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
		{
			ChangeState(KirbyState::Walk);
			return;
		}

		ChangeState(KirbyState::JumpToLand);
		return;
	}

	if (true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
		{
			ChangeState(KirbyState::Walk);
			return;
		}

		ChangeState(KirbyState::JumpToLand);
		return;
	}
}

void Kirby::JumpToLandUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd() || true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
		{
			ChangeState(KirbyState::Walk);
			return;
		}

		ChangeState(KirbyState::Idle);
		return;
	}
}
