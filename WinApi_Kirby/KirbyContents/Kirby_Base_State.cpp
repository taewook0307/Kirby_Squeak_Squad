#include "Kirby.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

//--------------------------------------------------------------------------------------------------------------------------------------------
void Kirby::KirbyGravity(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);

		unsigned int CheckColor = GetGroundColor(EMPTYCOLOR, float4::DOWN);

		while (CheckColor == EMPTYCOLOR || CheckColor == DOORCOLOR)
		{
			CheckColor = GetGroundColor(EMPTYCOLOR, float4::DOWN);
			AddPos(float4::DOWN);
		}
	}
	else
	{
		unsigned int CheckColor = GetGroundColor(EMPTYCOLOR, float4::UP);

		while (CheckColor != EMPTYCOLOR && CheckColor != DOORCOLOR)
		{
			CheckColor = GetGroundColor(EMPTYCOLOR, float4::UP);
			AddPos(float4::UP);
		}

		GravityReset();
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------

void Kirby::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Kirby::DownStart()
{
	ChangeAnimationState("Down");
}

void Kirby::LevelMoveStart()
{
	ChangeAnimationState("LevelMove");
}

void Kirby::IdleUpdate(float _Delta)
{
	BodyCollision->On();

	DirCheck();

	KirbyGravity(_Delta);

	// 걷기 상태 이동
	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(KirbyState::Walk);
		return;
	}

	// 웅크리기 상태 이동
	if (true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsPress('S'))
	{
		DirCheck();
		ChangeState(KirbyState::Down);
		return;
	}

	// 점프 상태 이동
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		DirCheck();
		ChangeState(KirbyState::Jump);
		return;
	}

	// 달리기 상태 이동
	if (true == GameEngineInput::IsDown('E')
		|| true == GameEngineInput::IsDown('Q'))
	{
		DirCheck();
		ChangeState(KirbyState::Run);
		return;
	}

	if (true == GameEngineInput::IsPress('F'))
	{
		DirCheck();
		ChangeState(KirbyState::Breathe);
		return;
	}

	if (true == GameEngineInput::IsDown('C'))
	{
		DirCheck();
		ChangeState(KirbyState::AttackReady);
		return;
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR, UPCHECKPOS);

	if (true == GameEngineInput::IsDown('W') && DOORCOLOR == Color)
	{
		ChangeState(KirbyState::LevelMove);
		return;
	}
}

void Kirby::DownUpdate(float _Delta)
{
	DirCheck();

	KirbyGravity(_Delta);

	// 슬라이딩 상태 전환
	if (true == GameEngineInput::IsDown('A') && Dir == ActorDir::Left
		|| true == GameEngineInput::IsDown('D') && Dir == ActorDir::Right)
	{
		ChangeState(KirbyState::Slide);
	}

	// 웅크리기 상태 유지
	else if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Down);
		return;
	}

	// 대기 상태 전환
	if (true == GameEngineInput::IsUp('S'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::LevelMoveUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		MapChangeAnimationEnd = true;
		return;
	}
}