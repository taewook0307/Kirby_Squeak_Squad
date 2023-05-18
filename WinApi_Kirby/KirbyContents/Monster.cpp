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
	case ActorState::Attack:
		return AttackUpdate(_Delta);
	case ActorState::Damage:
		return DamageUpdate(_Delta);
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
		case ActorState::Attack:
			AttackStart();
			break;
		case ActorState::Damage:
			DamageStart();
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

void Monster::DirChange(int _Value)
{
	ActorDir CheckDir = Dir;

	switch (_Value)
	{
	case 0:
		CheckDir = ActorDir::Left;
		break;
	case 1:
		CheckDir = ActorDir::Right;
		break;
	default:
		break;
	}

	if (CheckDir != Dir)
	{
		Dir = CheckDir;
	}
}