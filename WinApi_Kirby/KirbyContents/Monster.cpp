﻿#include "Monster.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Right_NormalMonster.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_NormalMonster.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Enermy\\NormalEnermy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_NormalMonster.Bmp"), 5, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_NormalMonster.Bmp"), 5, 3);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Monster);

		MainRenderer->CreateAnimation("Right_Monster_Idle", "Right_NormalMonster.Bmp", 0, 3, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Monster_Walk", "Right_NormalMonster.Bmp", 9, 12, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Monster_Damage", "Right_NormalMonster.Bmp", 4, 8, 0.2f, false);

		MainRenderer->CreateAnimation("Left_Monster_Idle", "Left_NormalMonster.Bmp", 0, 3, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Monster_Walk", "Left_NormalMonster.Bmp", 9, 12, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Monster_Damage", "Left_NormalMonster.Bmp", 4, 8, 0.2f, false);

		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionPos(MONSTERBODYCOLLISONPOS);
		BodyCollision->SetCollisionScale(MONSTERBODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}

	ChangeState(MonsterState::Idle);
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
		case MonsterState::Damage:
			DamageStart();
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

	if (Dir == ActorDir::Left)
	{
		CheckDir = ActorDir::Right;
	}
	
	if (Dir == ActorDir::Right)
	{
		CheckDir = ActorDir::Left;
	}

	if (CheckDir != Dir)
	{
		Dir = CheckDir;
		ChangeAnimationState(CurState);
	}
}

void Monster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Monster_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Monster_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}