#include "Monster.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{

}

void Monster::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Monster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ActorState::Idle:
		return IdleUpdate(_Delta);
	case ActorState::Walk:
		return WalkUpdate(_Delta);
	case ActorState::Run:
		return RunUpdate(_Delta);
	case ActorState::Stop:
		return StopUpdate(_Delta);
	case ActorState::Jump:
		return JumpUpdate(_Delta);
	default:
		break;
	}
}

void Monster::ChangeState(ActorState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case ActorState::Idle:
			IdleStart();
			break;
		case ActorState::Walk:
			WalkStart();
			break;
		case ActorState::Run:
			RunStart();
			break;
		case ActorState::Stop:
			StopStart();
			break;
		case ActorState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void Monster::DirChange()
{
	ActorDir CheckDir = Dir;

	if (true == GameEngineInput::IsDown('A'))
	{
		CheckDir = ActorDir::Left;
	}
	if (true == GameEngineInput::IsDown('D'))
	{
		CheckDir = ActorDir::Right;
	}

	if (CheckDir != Dir)
	{
		Dir = CheckDir;
	}
}