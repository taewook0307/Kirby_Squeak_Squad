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
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Enermy\\NormalEnermy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_NormalMonster.Bmp"), 5, 4);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_NormalMonster.Bmp"), 5, 4);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Idle", "Right_NormalMonster.Bmp", 0, 3, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Walk", "Right_NormalMonster.Bmp", 4, 11, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Idle", "Right_NormalMonster.Bmp", 12, 14, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Idle", "Right_NormalMonster.Bmp", 15, 15, 0.2f, true);

		MainRenderer->CreateAnimation("Left_Idle", "Right_NormalMonster.Bmp", 0, 3, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Walk", "Right_NormalMonster.Bmp", 4, 11, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Idle", "Right_NormalMonster.Bmp", 12, 14, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Idle", "Right_NormalMonster.Bmp", 15, 15, 0.2f, true);
	}
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

void Monster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}