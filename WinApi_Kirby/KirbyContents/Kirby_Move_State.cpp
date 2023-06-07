#include "Kirby.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void Kirby::SlideStart()
{
	ChangeAnimationState("Slide");
}

void Kirby::WalkStart()
{
	ChangeAnimationState("Walk");
}

void Kirby::RunStart()
{
	ChangeAnimationState("Run");
}

void Kirby::StopStart()
{
	ChangeAnimationState("Stop");
}

void Kirby::StopToIdleStart()
{
	ChangeAnimationState("StopToIdle");
}


void Kirby::SlideUpdate(float _Delta)
{
	KirbyGravity(_Delta);

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float CopySpeed = Speed / 1.5f;

	static float SlideTimer = 0.0f;

	// 왼쪽으로 슬라이딩
	if (Dir == ActorDir::Left && SlideTimer <= 1.0f)
	{
		MovePos = { -CopySpeed * _Delta, 0.0f };
		CheckPos = LEFTCHECKPOS;

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
		SlideTimer += _Delta;
		return;
	}

	// 오른쪽으로 슬라이딩
	if (Dir == ActorDir::Right && SlideTimer <= 1.0f)
	{
		MovePos = { CopySpeed * _Delta, 0.0f };
		CheckPos = RIGHTCHECKPOS;

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}

		SlideTimer += _Delta;
		return;
	}

	// 슬라이딩 정지 애니메이션
	if (SlideTimer <= 1.2f || SlideTimer >= 1.0f)
	{
		SlideTimer += _Delta;
	}

	// 슬라이딩 정지 후 대기 상태 전환
	if (true == MainRenderer->IsAnimationEnd())
	{
		SlideTimer = 0.0f;
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::WalkUpdate(float _Delta)
{
	DirCheck();

	KirbyGravity(_Delta);

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	// 왼쪽 이동
	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTCHECKPOS;
	}

	// 오른쪽 이동
	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTCHECKPOS;
	}

	// 이동 방향 앞에 장애물 여부 확인 후 이동
	{
		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	// 웅크리기 상태 이동
	if (true == GameEngineInput::IsDown('S'))
	{
		ChangeState(KirbyState::Down);
		return;
	}

	// 점프 상태 이동
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
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

	// 이동하지 않을 시 대기 상태 이동
	if (MovePos == float4::ZERO)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::RunUpdate(float _Delta)
{
	DirCheck();

	KirbyGravity(_Delta);

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	// 왼쪽 이동
	if (true == GameEngineInput::IsPress('Q') && Dir == ActorDir::Left)
	{
		MovePos = { -RunSpeed * _Delta, 0.0f };
		CheckPos = LEFTCHECKPOS;
	}

	// 오른쪽 이동
	if (true == GameEngineInput::IsPress('E') && Dir == ActorDir::Right)
	{
		MovePos = { RunSpeed * _Delta, 0.0f };
		CheckPos = RIGHTCHECKPOS;
	}

	// 이동 방향 앞에 장애물 여부 확인 후 이동
	{
		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	// 웅크리기 상태 이동
	if (true == GameEngineInput::IsDown('S'))
	{
		ChangeState(KirbyState::Down);
		return;
	}

	// 점프 상태 이동
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(KirbyState::Jump);
		return;
	}

	// 이동하지 않을 시 대기 상태 이동
	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(KirbyState::Stop);
		return;
	}
}

void Kirby::StopUpdate(float _Delta)
{
	KirbyGravity(_Delta);

	float4 MovePos = float4::ZERO;
	float4 OppositePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	float RunSpeed = Speed * 2.0f;

	if (ActorDir::Left == Dir)
	{
		MovePos = { -RunSpeed * _Delta, 0.0f };
		CheckPos = LEFTCHECKPOS;
	}

	if (ActorDir::Right == Dir)
	{
		MovePos = { RunSpeed * _Delta, 0.0f };
		CheckPos = RIGHTCHECKPOS;
	}

	OppositePos = MovePos * -0.1f;

	unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

	Speed *= 0.8f;

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{	
		AddPos(MovePos += OppositePos);
		CameraMove(MovePos += OppositePos);
	}

	if (ActorDir::Left == Dir && MovePos.X > -1.0f
		|| ActorDir::Right == Dir && MovePos.X < 1.0f
		|| EMPTYCOLOR != Color)
	{
		DirCheck();
		Speed = BASEPOWER;
		ChangeState(KirbyState::StopToIdle);
		return;
	}
}

void Kirby::StopToIdleUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}