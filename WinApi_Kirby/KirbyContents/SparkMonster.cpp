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

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_SparkMonster.Bmp"), 5, 4);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_SparkMonster.Bmp"), 5, 4);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Spark_Monster_Walk", "Right_SparkMonster.Bmp", 0, 3, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Spark_Monster_Attack", "Right_SparkMonster.Bmp", 6, 18, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_Monster_Damage", "Right_SparkMonster.Bmp", 4, 5, 0.2f, true);

		MainRenderer->CreateAnimation("Left_Spark_Monster_Walk", "Left_SparkMonster.Bmp", 0, 3, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Spark_Monster_Attack", "Left_SparkMonster.Bmp", 6, 18, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_Monster_Damage", "Left_SparkMonster.Bmp", 4, 5, 0.2f, true);

		MainRenderer->ChangeAnimation("Right_Spark_Monster_Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionPos(MONSTERBODYCOLLISONPOS);
		BodyCollision->SetCollisionScale(MONSTERBODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}

	ChangeState(MonsterState::Walk);
}

void SparkMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
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

void SparkMonster::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
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