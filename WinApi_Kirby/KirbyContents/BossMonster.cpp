#include "BossMonster.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

BossMonster::BossMonster()
{
}

BossMonster::~BossMonster()
{
}

void BossMonster::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Right_Boss.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_Boss.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Boss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Boss.Bmp"), 5, 7);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Boss.Bmp"), 5, 7);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Boss);

		MainRenderer->CreateAnimation("Right_Boss_Idle", "Right_Boss.Bmp", 0, 3, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Boss_Walk", "Right_Boss.Bmp", 4, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Boss_JumpStart", "Right_Boss.Bmp", 8, 8, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Boss_Jump", "Right_Boss.Bmp", 9, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Boss_Drop", "Right_Boss.Bmp", 10, 11, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Boss_Search", "Right_Boss.Bmp", 12, 13, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Boss_AttackSumon", "Right_Boss.Bmp", 14, 16, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Boss_Attack", "Right_Boss.Bmp", 17, 18, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Boss_MonsterSummon", "Right_Boss.Bmp", 19, 28, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Boss_Damage", "Right_Boss.Bmp", 29, 29, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Boss_Death", "Right_Boss.Bmp", 30, 32, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Boss_Idle", "Left_Boss.Bmp", 0, 3, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Boss_Walk", "Left_Boss.Bmp", 4, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Boss_JumpStart", "Left_Boss.Bmp", 8, 8, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Boss_Jump", "Left_Boss.Bmp", 9, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Boss_Drop", "Left_Boss.Bmp", 10, 11, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Boss_Search", "Left_Boss.Bmp", 12, 13, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Boss_AttackSumon", "Left_Boss.Bmp", 14, 16, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Boss_Attack", "Left_Boss.Bmp", 17, 18, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Boss_MonsterSummon", "Left_Boss.Bmp", 19, 28, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Boss_Damage", "Left_Boss.Bmp", 29, 29, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Boss_Death", "Left_Boss.Bmp", 30, 32, 0.1f, false);
	
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::BossBody);

		SearchCollision = CreateCollision(CollisionOrder::BossSearch);
	}

	ChangeState(BossState::Idle);
}

void BossMonster::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void BossMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BossState::Idle:
		return IdleUpdate(_Delta);
	case BossState::Walk:
		return WalkUpdate(_Delta);
	case BossState::JumpReady:
		return JumpReadyUpdate(_Delta);
	case BossState::Jump:
		return JumpUpdate(_Delta);
	case BossState::Drop:
		return DropUpdate(_Delta);
	case BossState::Search:
		return SearchUpdate(_Delta);
	case BossState::AttackSummon:
		return AttackSummonUpdate(_Delta);
	case BossState::Attack:
		return AttackUpdate(_Delta);
	case BossState::MonsterSummon:
		return MonsterSummonUpdate(_Delta);
	case BossState::Damage:
		return DamageUpdate(_Delta);
	case BossState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void BossMonster::ChangeState(BossState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BossState::Idle:
			IdleStart();
			break;
		case BossState::Walk:
			WalkStart();
			break;
		case BossState::JumpReady:
			JumpReadyStart();
			break;
		case BossState::Jump:
			JumpStart();
			break;
		case BossState::Drop:
			DropStart();
			break;
		case BossState::Search:
			SearchStart();
			break;
		case BossState::AttackSummon:
			AttackSummonStart();
			break;
		case BossState::Attack:
			AttackStart();
			break;
		case BossState::MonsterSummon:
			MonsterSummonStart();
			break;
		case BossState::Damage:
			DamageStart();
			break;
		case BossState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void BossMonster::DirChange()
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

void BossMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Boss_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Boss_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}