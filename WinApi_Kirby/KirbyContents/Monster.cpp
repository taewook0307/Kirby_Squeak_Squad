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
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	case MonsterState::Walk:
		return WalkUpdate(_Delta);
	case MonsterState::Attack:
		return AttackUpdate(_Delta);
	case MonsterState::Damage:
		return DamageUpdate(_Delta);
	case MonsterState::Jump:
		return JumpUpdate(_Delta);
	default:
		break;
	}
}

void Monster::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Walk:
			WalkStart();
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		case MonsterState::Damage:
			DamageStart();
			break;
		case MonsterState::Jump:
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