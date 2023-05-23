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

		MainRenderer->CreateAnimation("Right_Spark_Idle", "Right_SparkKirby.Bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_Down", "Right_SparkKirby.Bmp", 8, 15, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_Slide", "Right_SparkKirby.Bmp", 16, 20, 0.25f, true);
		MainRenderer->CreateAnimation("Right_Spark_Jump", "Right_SparkKirby.Bmp", 21, 22, 1.5f, true);
		MainRenderer->CreateAnimation("Right_Spark_JumpToDown", "Right_SparkKirby.Bmp", 23, 30, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Spark_JumpToLand", "Right_SparkKirby.Bmp", 30, 31, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Spark_Walk", "Right_SparkKirby.Bmp", 32, 51, 0.05f, true);


		MainRenderer->CreateAnimation("Left_Spark_Idle", "Left_SparkKirby.Bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Spark_Down", "Left_SparkKirby.Bmp", 8, 15, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Spark_Slide", "Left_SparkKirby.Bmp", 16, 20, 0.25f, true);
		MainRenderer->CreateAnimation("Left_Spark_Jump", "Left_SparkKirby.Bmp", 21, 22, 1.5f, true);
		MainRenderer->CreateAnimation("Left_Spark_JumpToDown", "Left_SparkKirby.Bmp", 23, 30, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Spark_JumpToLand", "Left_SparkKirby.Bmp", 30, 31, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Spark_Walk", "Left_SparkKirby.Bmp", 32, 51, 0.05f, true);

		MainRenderer->ChangeAnimation("Right_Spark_Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(4.0f);
	}

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