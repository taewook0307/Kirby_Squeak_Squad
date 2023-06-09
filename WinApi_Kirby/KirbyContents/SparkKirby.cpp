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

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_SparkKirby.Bmp"), 10, 17);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_SparkKirby.Bmp"), 10, 17);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Monster);

		MainRenderer->CreateAnimation("Right_Spark_Idle", "Right_SparkKirby.Bmp", 0, 7, 0.125f, true);
		MainRenderer->CreateAnimation("Right_Spark_Down", "Right_SparkKirby.Bmp", 8, 15, 0.125f, true);
		MainRenderer->CreateAnimation("Right_Spark_Slide", "Right_SparkKirby.Bmp", 16, 25, 0.1f, false);
		MainRenderer->FindAnimation("Right_Spark_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Right_Spark_Jump", "Right_SparkKirby.Bmp", 26, 27, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_JumpToDrop", "Right_SparkKirby.Bmp", 28, 35, 0.03f, false);
		MainRenderer->CreateAnimation("Right_Spark_JumpToLand", "Right_SparkKirby.Bmp", 36, 36, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Spark_Walk", "Right_SparkKirby.Bmp", 37, 56, 0.025f, true);
		MainRenderer->CreateAnimation("Right_Spark_Run", "Right_SparkKirby.Bmp", 57, 64, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Spark_Stop", "Right_SparkKirby.Bmp", 65, 68, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_StopToIdle", "Right_SparkKirby.Bmp", 69, 70, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_Breathe", "Right_SparkKirby.Bmp", 71, 76, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_Fly", "Right_SparkKirby.Bmp", 77, 105, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Spark_BreatheOutLand", "Right_SparkKirby.Bmp", 106, 107, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_BreatheOut", "Right_SparkKirby.Bmp", 106, 107, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_Drop", "Right_SparkKirby.Bmp", 108, 109, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_FlyToLand", "Right_SparkKirby.Bmp", 124, 124, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_FlyToTurnUp", "Right_SparkKirby.Bmp", 110, 121, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_FlyToTurnLand", "Right_SparkKirby.Bmp", 122, 123, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_LevelMove", "Right_SparkKirby.Bmp", 125, 129, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_Damage", "Right_SparkKirby.Bmp", 130, 132, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Spark_DamageLand", "Right_SparkKirby.Bmp", 133, 136, 0.15f, false);
		MainRenderer->CreateAnimation("Right_Spark_AttackReady", "Right_SparkKirby.Bmp", 137, 139, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_Attack", "Right_SparkKirby.Bmp", 140, 143, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_AttackToIdle", "Right_SparkKirby.Bmp", 144, 145, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Spark_Change", "Right_SparkKirby.Bmp", 146, 160, 0.1f, false);
		MainRenderer->FindAnimation("Right_Spark_Change")->Inters[7] = 0.3f;

		MainRenderer->CreateAnimation("Left_Spark_Idle", "Left_SparkKirby.Bmp", 0, 7, 0.125f, true);
		MainRenderer->CreateAnimation("Left_Spark_Down", "Left_SparkKirby.Bmp", 8, 15, 0.125f, true);
		MainRenderer->CreateAnimation("Left_Spark_Slide", "Left_SparkKirby.Bmp", 16, 25, 0.1f, false);
		MainRenderer->FindAnimation("Left_Spark_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Left_Spark_Jump", "Left_SparkKirby.Bmp", 26, 27, 1.0f, true);
		MainRenderer->CreateAnimation("Left_Spark_JumpToDrop", "Left_SparkKirby.Bmp", 28, 35, 0.03f, false);
		MainRenderer->CreateAnimation("Left_Spark_JumpToLand", "Left_SparkKirby.Bmp", 36, 36, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Spark_Walk", "Left_SparkKirby.Bmp", 37, 56, 0.025f, true);
		MainRenderer->CreateAnimation("Left_Spark_Run", "Left_SparkKirby.Bmp", 57, 64, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Spark_Stop", "Left_SparkKirby.Bmp", 65, 68, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Spark_StopToIdle", "Left_SparkKirby.Bmp", 69, 70, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_Breathe", "Left_SparkKirby.Bmp", 71, 76, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_Fly", "Left_SparkKirby.Bmp", 77, 105, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Spark_BreatheOutLand", "Left_SparkKirby.Bmp", 106, 107, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_BreatheOut", "Left_SparkKirby.Bmp", 106, 107, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_Drop", "Left_SparkKirby.Bmp", 108, 109, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Spark_FlyToLand", "Left_SparkKirby.Bmp", 124, 124, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_FlyToTurnUp", "Left_SparkKirby.Bmp", 110, 121, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_FlyToTurnLand", "Left_SparkKirby.Bmp", 122, 123, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Spark_LevelMove", "Left_SparkKirby.Bmp", 125, 129, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_Damage", "Left_SparkKirby.Bmp", 130, 132, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Spark_DamageLand", "Left_SparkKirby.Bmp", 133, 136, 0.15f, false);
		MainRenderer->CreateAnimation("Left_Spark_AttackReady", "Left_SparkKirby.Bmp", 137, 139, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_Attack", "Left_SparkKirby.Bmp", 140, 143, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Spark_AttackToIdle", "Left_SparkKirby.Bmp", 144, 145, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Spark_Change", "Left_SparkKirby.Bmp", 146, 160, 0.1f, false);
		MainRenderer->FindAnimation("Left_Spark_Change")->Inters[7] = 0.3f;

		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::Body);
		BodyCollision->SetCollisionPos(BODYCOLLISIONPOS);
		BodyCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);

		AttackCollision = CreateCollision(CollisionOrder::SpecialAttack);
		AttackCollision->SetCollisionPos(BODYCOLLISIONPOS);
		AttackCollision->SetCollisionScale(SPARKATTACKCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}

	AttackCollision->Off();
	ChangeState(KirbyState::Change);
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