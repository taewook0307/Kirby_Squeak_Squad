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

// 공기 들이마시는 상태
void Kirby::BreatheUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Fly);
		return;
	}
}

// 비행 상태
void Kirby::FlyUpdate(float _Delta)
{
	// 방향 체크
	DirCheck();

	float4 FlyPos = float4::UP * FlyPower * _Delta;
	
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	float4 UpPos = GetPos() += FlyPos;
	// 현재 위치에서 올라갈 시 화면 밖으로 나가는지 확인
	if (UpPos.Y > 100.0f)
	{
		AddPos(FlyPos);
	}

	// 방향 변경을 위해 멤버 변수값 빼주기
	FlyPower -= 10.0f;

	// 맴버 변수값 초기값으로 변경 후 다시 위로 이동
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

	// 스페이스바 누르면 낙하 상태로 변경
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		FlyPower = BASEPOWER;
		ChangeState(KirbyState::BreatheOut);
		return;
	}

	float4 DownCheckPos = { 0.0f, 0.0f };
	unsigned int DownColor = GetGroundColor(EMPTYCOLOR, DownCheckPos);

	// 바닥에 닿고 FlyPos의 Y값이 아래 방향이면 착지 상태로 변경
	if (EMPTYCOLOR != DownColor && FlyPos.Y > 0)
	{
		FlyPower = BASEPOWER;
		ChangeState(KirbyState::BreatheOutLand);
		return;
	}
}

// 낙하 상태를 거치지 않고 착지한 상태
void Kirby::BreatheOutLandUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

// 공중에서 낙하하기 위해 공기를 내뱉는 상태
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

	// 예외처리
	else
	{
		if (true == MainRenderer->IsAnimationEnd())
		{
			ChangeState(KirbyState::Idle);
			return;
		}
	}

	// 애니메이션이 다 실행되면 낙하 상태로 변경
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Drop);
		return;
	}
}

// 낙하 상태
void Kirby::DropUpdate(float _Delta)
{
	// 낙하 시간을 알기 위한 static 지역변수
	static float DropTimer = 0.0f;

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	// 흰 공간에 있을 경우
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
	// 흰 공간이 아닌 경우(지면에 닿았을 경우)
	else
	{
		GravityReset();
		// 떨어진 시간이 1초 이하면 착지 상태로 변경
		if (DropTimer < 1.0f)
		{
			DropTimer = 0.0f;
			ChangeState(KirbyState::FlyToLand);
			return;
		}
		// 1초 이상이면 착지 후 턴 상태로 변경
		else
		{
			DropTimer = 0.0f;
			ChangeState(KirbyState::FlyToTurnUp);
			return;
		}
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

// 바닥에 부딪힌 후 턴하면서 살짝 위로 올라가는 상태
void Kirby::FlyToTurnUpUpdate(float _Delta)
{
	float4 FlyPos = float4::UP * FlyPower * 0.7f * _Delta;
	float4 CheckPos = float4::ZERO;

	// 왼쪽 방향에 경우 왼쪽 위로 이동
	if (Dir == ActorDir::Left)
	{
		FlyPos = { -Speed * 0.3f * _Delta, -FlyPower * 0.7f * _Delta };
		CheckPos = { -50.0f, -50.0f };
	}

	// 오른쪽 방향에 경우 오른쪽 위로 이동
	if (Dir == ActorDir::Right)
	{
		FlyPos = { Speed * 0.3f * _Delta, -FlyPower * 0.7f * _Delta };
		CheckPos = { 50.0f, -50.0f };
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

	// 벽이 있는 지 확인 후 없으면 위치값 위로 이동
	if (EMPTYCOLOR == Color)
	{
		AddPos(FlyPos);
	}

	FlyPower -= 10.0f;
	
	// 더해주는 Pos값이 아래방향으로 바뀌면 FlyToTurnLand 상태로 변환
	if (FlyPos.Y > 0)
	{
		ChangeState(KirbyState::FlyToTurnLand);
		return;
	}
}

// 아래 방향으로 낙하
void Kirby::FlyToTurnLandUpdate(float _Delta)
{
	float4 FlyPos = float4::UP * FlyPower * 0.7f * _Delta;
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	// 왼쪽 방향으로 이동하는 Pos 값 및 CheckPos 값 설정
	if (Dir == ActorDir::Left)
	{
		MovePos = { -Speed * 0.3f * _Delta, 0.0f };
		CheckPos = { -50.0f, -30.0f };
	}

	// 오른쪽 방향으로 이동하는 Pos 값 및 CheckPos 값 설정
	if (Dir == ActorDir::Right)
	{
		MovePos = { Speed * 0.3f * _Delta, 0.0f };
		CheckPos = { 50.0f, -30.0f };
	}

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	// 왼쪽 혹은 오른쪽 방향에 벽이 없을경우 X방향 Y방향 전체 이동
	if (EMPTYCOLOR == XColor)
	{
		AddPos(MovePos);
		AddPos(FlyPos);
	}
	else
	{
		// 왼쪽 혹은 오른쪽 방향에 벽이 있을 경우 Y방향만 이동
		if (EMPTYCOLOR == Color)
		{
			AddPos(FlyPos);
		}
		else
		{
			ChangeState(KirbyState::FlyToLand);
			return;
		}
	}

	// 지면을 만나면 착지 상태로 이동
	if(EMPTYCOLOR != Color)
	{
		FlyPower = BASEPOWER;
		ChangeState(KirbyState::FlyToLand);
		return;
	}
	
	FlyPower -= 10.0f;
}