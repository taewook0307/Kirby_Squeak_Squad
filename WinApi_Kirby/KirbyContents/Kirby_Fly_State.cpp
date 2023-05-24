#include "Kirby.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

void Kirby::BreatheStart()
{
	ChangeAnimationState("Breathe");
}

void Kirby::FlyStart()
{
	ChangeAnimationState("Fly");
}

void Kirby::BreatheOutLandStart()
{
	ChangeAnimationState("BreatheOutLand");
}

void Kirby::BreatheOutStart()
{
	ChangeAnimationState("BreatheOut");
}

void Kirby::DropStart()
{
	ChangeAnimationState("Drop");
}

void Kirby::FlyToLandStart()
{
	ChangeAnimationState("FlyToLand");
}

void Kirby::FlyToTurnUpStart()
{
	ChangeAnimationState("FlyToTurnUp");
}

void Kirby::FlyToTurnLandStart()
{
	ChangeAnimationState("FlyToTurnLand");
}

void Kirby::BreatheUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Fly);
		return;
	}
}

void Kirby::FlyUpdate(float _Delta)
{
	DirCheck();

	float4 FlyPos = float4::UP * FlyPower * _Delta;
	
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	float4 UpPos = GetPos() += FlyPos;
	if (UpPos.Y > 100.0f)
	{
		AddPos(FlyPos);
	}

	FlyPower -= 10.0f;

	if (true == GameEngineInput::IsDown('F'))
	{
		FlyPower = BASEPOWER;

		UpPos = GetPos() += FlyPos;

		if (UpPos.Y > 100.0f)
		{
			AddPos(FlyPos);
		}
	}

	// 오른쪽 이동
	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = { 50.0f, -50.0f };
	}

	// 왼쪽 이동
	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = { -50.0f, -50.0f };
	}

	// 이동 방향 앞에 장애물 여부 확인 후 이동
	{
		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		FlyPower = BASEPOWER;
		ChangeState(KirbyState::BreatheOut);
		return;
	}

	float4 DownCheckPos = { 0.0f, 0.0f };
	unsigned int DownColor = GetGroundColor(EMPTYCOLOR, DownCheckPos);

	if (EMPTYCOLOR != DownColor && FlyPos.Y > 0)
	{
		FlyPower = BASEPOWER;
		ChangeState(KirbyState::BreatheOutLand);
		return;
	}
}

void Kirby::BreatheOutLandUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::BreatheOutUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		// 오른쪽 이동
		if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
		{
			MovePos = { Speed * _Delta, 0.0f };
			CheckPos = { 30.0f, -50.0f };
		}

		// 왼쪽 이동
		if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
		{
			MovePos = { -Speed * _Delta, 0.0f };
			CheckPos = { -30.0f, -50.0f };
		}

		// 이동 방향 앞에 장애물 여부 확인 후 이동
		{
			unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

			if (EMPTYCOLOR == XColor)
			{
				AddPos(MovePos);
				CameraMove(MovePos);
			}
		}
	}
	else
	{
		if (true == MainRenderer->IsAnimationEnd())
		{
			ChangeState(KirbyState::Idle);
			return;
		}
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Drop);
		return;
	}
}

void Kirby::DropUpdate(float _Delta)
{
	static float DropTimer = 0.0f;

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		DropTimer += _Delta;
		Gravity(_Delta);

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		// 오른쪽 이동
		if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
		{
			MovePos = { Speed * _Delta, 0.0f };
			CheckPos = { 30.0f, -50.0f };
		}

		// 왼쪽 이동
		if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
		{
			CheckPos = { -30.0f, -50.0f };
			MovePos = { -Speed * _Delta, 0.0f };
		}

		// 이동 방향 앞에 장애물 여부 확인 후 이동
		{
			unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

			if (EMPTYCOLOR == XColor)
			{
				AddPos(MovePos);
				CameraMove(MovePos);
			}
		}
	}
	else
	{
		GravityReset();
		if (DropTimer < 1.0f)
		{
			DropTimer = 0.0f;
			ChangeState(KirbyState::FlyToLand);
			return;
		}
		else
		{
			DropTimer = 0.0f;
			ChangeState(KirbyState::FlyToTurnUp);
			return;
		}
	}
}

void Kirby::FlyToLandUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::FlyToTurnUpUpdate(float _Delta)
{
	float4 FlyPos = float4::UP * FlyPower * 0.7f * _Delta;
	float4 CheckPos = float4::ZERO;

	if (Dir == ActorDir::Left)
	{
		FlyPos = { -Speed * 0.3f * _Delta, -FlyPower * 0.7f * _Delta };
		CheckPos = { -50.0f, -50.0f };
	}

	if (Dir == ActorDir::Right)
	{
		FlyPos = { Speed * 0.3f * _Delta, -FlyPower * 0.7f * _Delta };
		CheckPos = { 50.0f, -50.0f };
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == Color)
	{
		AddPos(FlyPos);
	}

	FlyPower -= 10.0f;
	
	if (FlyPos.Y > 0)
	{
		ChangeState(KirbyState::FlyToTurnLand);
		return;
	}
}

void Kirby::FlyToTurnLandUpdate(float _Delta)
{
	float4 FlyPos = float4::UP * FlyPower * 0.7f * _Delta;
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (Dir == ActorDir::Left)
	{
		MovePos = { -Speed * 0.3f * _Delta, 0.0f };
		CheckPos = { -50.0f, -30.0f };
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { Speed * 0.3f * _Delta, 0.0f };
		CheckPos = { 50.0f, -30.0f };
	}

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == XColor)
	{
		AddPos(MovePos);
		AddPos(FlyPos);
	}
	else
	{
		if (EMPTYCOLOR == Color)
		{
			AddPos(FlyPos);
		}
	}

	if(EMPTYCOLOR != Color)
	{
		FlyPower = BASEPOWER;
		ChangeState(KirbyState::FlyToLand);
		return;
	}
	
	FlyPower -= 10.0f;
}