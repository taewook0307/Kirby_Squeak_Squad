#include "FireMonster.h"
#include "ActorEnum.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

FireMonster::FireMonster()
{
}

FireMonster::~FireMonster()
{
}

void FireMonster::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Enermy\\FireEnermy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_FireEnermy.Bmp"), 5, 4);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_FireEnermy.Bmp"), 5, 4);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Fire_Monster_Idle", "Right_FireEnermy.Bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Fire_Monster_Walk", "Right_FireEnermy.Bmp", 1, 5, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Fire_Monster_Attack", "Right_FireEnermy.Bmp", 6, 12, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Fire_Monster_Damage", "Right_FireEnermy.Bmp", 13, 15, 0.2f, false);

		MainRenderer->CreateAnimation("Left_Fire_Monster_Idle", "Left_FireEnermy.Bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Fire_Monster_Walk", "Left_FireEnermy.Bmp", 1, 5, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Fire_Monster_Attack", "Left_FireEnermy.Bmp", 6, 12, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Fire_Monster_Damage", "Left_FireEnermy.Bmp", 13, 15, 0.2f, false);

		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionPos(MONSTERBODYCOLLISONPOS);
		BodyCollision->SetCollisionScale(MONSTERBODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);

		SearchCollision = CreateCollision(CollisionOrder::MonsterSearch);
		SearchCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		SearchCollision->SetCollisionScale(SEARCHCOLLISONSCALE);
		SearchCollision->SetCollisionType(CollisionType::Rect);

		AttackCollision = CreateCollision(CollisionOrder::MonsterAttack);
		AttackCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		AttackCollision->SetCollisionScale(ATTACKCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}

	AttackCollision->Off();
	ChangeState(MonsterState::Idle);
}

void FireMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Fire_Monster_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Fire_Monster_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}