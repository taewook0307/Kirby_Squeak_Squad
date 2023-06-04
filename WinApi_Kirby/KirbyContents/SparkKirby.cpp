#include "SparkKirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

SparkKirby::SparkKirby()
{
}

SparkKirby::~SparkKirby()
{
}

void SparkKirby::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Right_SparkKirby.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_SparkKirby.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\SparkKirby\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_SparkKirby.Bmp"), 10, 14);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_SparkKirby.Bmp"), 10, 14);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Spark_Idle", "Right_SparkKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Spark_Down", "Right_SparkKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Spark_Slide", "Right_SparkKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Right_Spark_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Right_Spark_Jump", "Right_SparkKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_JumpToDown", "Right_SparkKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_JumpToLand", "Right_SparkKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Spark_Walk", "Right_SparkKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Spark_Run", "Right_SparkKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Spark_Stop", "Right_SparkKirby.Bmp", 42, 42, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_StopToIdle", "Right_SparkKirby.Bmp", 43, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_Breathe", "Right_SparkKirby.Bmp", 45, 49, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_Fly", "Right_SparkKirby.Bmp", 50, 67, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Spark_BreatheOutLand", "Right_SparkKirby.Bmp", 68, 69, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_BreatheOut", "Right_SparkKirby.Bmp", 68, 69, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Spark_Drop", "Right_SparkKirby.Bmp", 70, 71, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_FlyToLand", "Right_SparkKirby.Bmp", 83, 85, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Spark_FlyToTurnUp", "Right_SparkKirby.Bmp", 72, 78, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_FlyToTurnLand", "Right_SparkKirby.Bmp", 79, 82, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_LevelMove", "Right_SparkKirby.Bmp", 86, 89, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_Damage", "Right_SparkKirby.Bmp", 90, 92, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_DamageLand", "Right_SparkKirby.Bmp", 93, 94, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Spark_AttackReady", "Right_SparkKirby.Bmp", 95, 101, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_AttackLoop", "Right_SparkKirby.Bmp", 101, 116, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_Attack", "Right_SparkKirby.Bmp", 117, 119, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Spark_Idle", "Left_SparkKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Spark_Down", "Left_SparkKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Spark_Slide", "Left_SparkKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Left_Spark_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Left_Spark_Jump", "Left_SparkKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_JumpToDown", "Left_SparkKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_JumpToLand", "Left_SparkKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Spark_Walk", "Left_SparkKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Spark_Run", "Left_SparkKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Spark_Stop", "Left_SparkKirby.Bmp", 42, 42, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Spark_StopToIdle", "Left_SparkKirby.Bmp", 43, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_Breathe", "Left_SparkKirby.Bmp", 45, 49, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_Fly", "Left_SparkKirby.Bmp", 50, 67, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Spark_BreatheOutLand", "Left_SparkKirby.Bmp", 68, 69, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_BreatheOut", "Left_SparkKirby.Bmp", 68, 69, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Spark_Drop", "Left_SparkKirby.Bmp", 70, 71, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_FlyToLand", "Left_SparkKirby.Bmp", 83, 85, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Spark_FlyToTurnUp", "Left_SparkKirby.Bmp", 72, 78, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_FlyToTurnLand", "Left_SparkKirby.Bmp", 79, 82, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_LevelMove", "Left_SparkKirby.Bmp", 86, 89, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_Damage", "Left_SparkKirby.Bmp", 90, 92, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_DamageLand", "Left_SparkKirby.Bmp", 93, 94, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Spark_AttackReady", "Left_SparkKirby.Bmp", 95, 101, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_AttackLoop", "Left_SparkKirby.Bmp", 101, 116, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Spark_Attack", "Left_SparkKirby.Bmp", 117, 119, 0.1f, false);

		MainRenderer->ChangeAnimation("Right_Spark_Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::Body);
		BodyCollision->SetCollisionPos(BODYCOLLISIONPOS);
		BodyCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);

		AttackCollision = CreateCollision(CollisionOrder::SpecialAttack);
		if (Dir == ActorDir::Left)
		{
			AttackCollision->SetCollisionPos(BODYCOLLISIONPOS);
		}
		else
		{
			AttackCollision->SetCollisionPos(BODYCOLLISIONPOS);
		}
		AttackCollision->SetCollisionScale(SPARKATTACKCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}

	AttackCollision->Off();
	ChangeState(KirbyState::Idle);
}

void SparkKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Spark_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Spark_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}