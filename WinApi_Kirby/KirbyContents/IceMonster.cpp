#include "IceMonster.h"
#include "ActorEnum.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

IceMonster::IceMonster()
{
}

IceMonster::~IceMonster()
{
}

void IceMonster::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Enermy\\IceEnermy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_IceEnermy.Bmp"), 5, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_IceEnermy.Bmp"), 5, 3);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Ice_Monster_Idle", "Right_IceEnermy.Bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_Monster_Walk", "Right_IceEnermy.Bmp", 1, 2, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Ice_Monster_Attack", "Right_IceEnermy.Bmp", 3, 8, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Ice_Monster_Damage", "Right_IceEnermy.Bmp", 9, 10, 0.2f, false);

		MainRenderer->CreateAnimation("Left_Ice_Monster_Idle", "Left_IceEnermy.Bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_Monster_Walk", "Left_IceEnermy.Bmp", 1, 2, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Ice_Monster_Attack", "Left_IceEnermy.Bmp", 3, 8, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Ice_Monster_Damage", "Left_IceEnermy.Bmp", 9, 10, 0.2f, false);

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

void IceMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Ice_Monster_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Ice_Monster_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}