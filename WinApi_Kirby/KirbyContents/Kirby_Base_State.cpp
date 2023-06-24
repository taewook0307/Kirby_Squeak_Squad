#include "Kirby.h"
#include "TranslucentBlock.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>

void Kirby::KirbyGravity(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GravityReset();
	}
	
	if (EMPTYCOLOR == Color && false == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect)
		|| DOORCOLOR == Color && false == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		Gravity(_Delta);
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
	GameEngineSound::SoundPlay("Move.wav");
}

void Kirby::ChangeStart()
{
	ChangeAnimationState("Change");
}

void Kirby::IdleUpdate(float _Delta)
{
	DirCheck();

	KirbyGravity(_Delta);

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	// 걷기 상태 전환
	if (true == GameEngineInput::IsDown('A') && Color == FLOORCOLOR
		|| true == GameEngineInput::IsDown('D') && Color == FLOORCOLOR
		|| true == GameEngineInput::IsPress('A') && Color == FLOORCOLOR
		|| true == GameEngineInput::IsPress('D') && Color == FLOORCOLOR
		|| true == GameEngineInput::IsDown('A') && true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect)
		|| true == GameEngineInput::IsDown('D') && true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect)
		|| true == GameEngineInput::IsPress('A') && true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect)
		|| true == GameEngineInput::IsPress('D') && true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		DirCheck();
		ChangeState(KirbyState::Walk);
		return;
	}

	// 웅크리기 상태 전환
	if (true == GameEngineInput::IsDown('S') && Color == FLOORCOLOR
		|| true == GameEngineInput::IsPress('S') && Color == FLOORCOLOR
		|| true == GameEngineInput::IsDown('S') && true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect)
		|| true == GameEngineInput::IsPress('S') && true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		DirCheck();
		ChangeState(KirbyState::Down);
		return;
	}

	// 점프 상태 전환
	if (true == GameEngineInput::IsDown(VK_SPACE) && Color == FLOORCOLOR
		|| true == GameEngineInput::IsDown(VK_SPACE) && true == BodyCollision->Collision(CollisionOrder::FloorObstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		DirCheck();
		ChangeState(KirbyState::Jump);
		return;
	}

	// 공격 상태 전환
	if (true == GameEngineInput::IsDown('C'))
	{
		DirCheck();
		ChangeState(KirbyState::AttackReady);
		return;
	}

	// 다음 스테이지 넘어가기 상태 전환
	{
		unsigned int Color = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);

		if (true == GameEngineInput::IsDown('W') && DOORCOLOR == Color)
		{
			ChangeState(KirbyState::LevelMove);
			return;
		}
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

void Kirby::ChangeUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
		{
			ChangeState(KirbyState::Walk);
			return;
		}

		ChangeState(KirbyState::Idle);
		return;
	}
}