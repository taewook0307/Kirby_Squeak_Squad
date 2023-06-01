#include "SparkMonster.h"
#include "ActorEnum.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

SparkMonster::SparkMonster()
{
}

SparkMonster::~SparkMonster()
{
}

void SparkMonster::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Enermy\\SparkEnermy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_SparkEnermy.Bmp"), 5, 4);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_SparkEnermy.Bmp"), 5, 4);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Spark_Monster_Idle", "Right_SparkEnermy.Bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_Monster_Walk", "Right_SparkEnermy.Bmp", 0, 3, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Spark_Monster_Attack", "Right_SparkEnermy.Bmp", 6, 18, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_Monster_Damage", "Right_SparkEnermy.Bmp", 4, 5, 0.2f, false);

		MainRenderer->CreateAnimation("Left_Spark_Monster_Idle", "Left_SparkEnermy.Bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_Monster_Walk", "Left_SparkEnermy.Bmp", 0, 3, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Spark_Monster_Attack", "Left_SparkEnermy.Bmp", 6, 18, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_Monster_Damage", "Left_SparkEnermy.Bmp", 4, 5, 0.2f, false);

		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionPos(MONSTERBODYCOLLISONPOS);
		BodyCollision->SetCollisionScale(MONSTERBODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);

		AttackCollision = CreateCollision(CollisionOrder::MonsterBody);
		AttackCollision->SetCollisionPos(MONSTERBODYCOLLISONPOS);
		AttackCollision->SetCollisionScale(float4 MONSTERBODYCOLLISIONSCALE * 2.0f);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}

	AttackCollision->Off();
	ChangeState(MonsterState::Idle);
}

void SparkMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Spark_Monster_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Spark_Monster_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}