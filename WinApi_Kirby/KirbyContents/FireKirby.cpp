#include "FireKirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

FireKirby::FireKirby()
{
}

FireKirby::~FireKirby()
{
}

void FireKirby::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Right_FireKirby.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_FireKirby.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\FireKirby\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_FireKirby.Bmp"), 10, 14);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_FireKirby.Bmp"), 10, 14);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Fire_Idle", "Right_FireKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Fire_Down", "Right_FireKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Fire_Slide", "Right_FireKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Right_Fire_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Right_Fire_Jump", "Right_FireKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Fire_JumpToDown", "Right_FireKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Fire_JumpToLand", "Right_FireKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Fire_Walk", "Right_FireKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Fire_Run", "Right_FireKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Fire_Stop", "Right_FireKirby.Bmp", 42, 42, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Fire_StopToIdle", "Right_FireKirby.Bmp", 43, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Fire_Breathe", "Right_FireKirby.Bmp", 45, 49, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Fire_Fly", "Right_FireKirby.Bmp", 50, 67, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Fire_BreatheOutLand", "Right_FireKirby.Bmp", 68, 69, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Fire_BreatheOut", "Right_FireKirby.Bmp", 68, 69, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Fire_Drop", "Right_FireKirby.Bmp", 70, 71, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Fire_FlyToLand", "Right_FireKirby.Bmp", 83, 85, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Fire_FlyToTurnUp", "Right_FireKirby.Bmp", 72, 78, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Fire_FlyToTurnLand", "Right_FireKirby.Bmp", 79, 82, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Fire_LevelMove", "Right_FireKirby.Bmp", 86, 89, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Fire_Damage", "Right_FireKirby.Bmp", 90, 92, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Fire_DamageLand", "Right_FireKirby.Bmp", 93, 94, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Fire_AttackReady", "Right_FireKirby.Bmp", 95, 101, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Fire_AttackLoop", "Right_FireKirby.Bmp", 101, 116, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Fire_Attack", "Right_FireKirby.Bmp", 117, 119, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Fire_Idle", "Left_FireKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Fire_Down", "Left_FireKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Fire_Slide", "Left_FireKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Left_Fire_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Left_Fire_Jump", "Left_FireKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Fire_JumpToDown", "Left_FireKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Fire_JumpToLand", "Left_FireKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Fire_Walk", "Left_FireKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Fire_Run", "Left_FireKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Fire_Stop", "Left_FireKirby.Bmp", 42, 42, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Fire_StopToIdle", "Left_FireKirby.Bmp", 43, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Fire_Breathe", "Left_FireKirby.Bmp", 45, 49, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Fire_Fly", "Left_FireKirby.Bmp", 50, 67, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Fire_BreatheOutLand", "Left_FireKirby.Bmp", 68, 69, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Fire_BreatheOut", "Left_FireKirby.Bmp", 68, 69, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Fire_Drop", "Left_FireKirby.Bmp", 70, 71, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Fire_FlyToLand", "Left_FireKirby.Bmp", 83, 85, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Fire_FlyToTurnUp", "Left_FireKirby.Bmp", 72, 78, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Fire_FlyToTurnLand", "Left_FireKirby.Bmp", 79, 82, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Fire_LevelMove", "Left_FireKirby.Bmp", 86, 89, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Fire_Damage", "Left_FireKirby.Bmp", 90, 92, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Fire_DamageLand", "Left_FireKirby.Bmp", 93, 94, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Fire_AttackReady", "Left_FireKirby.Bmp", 95, 101, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Fire_AttackLoop", "Left_FireKirby.Bmp", 101, 116, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Fire_Attack", "Left_FireKirby.Bmp", 117, 119, 0.1f, false);

		MainRenderer->ChangeAnimation("Right_Fire_Idle");
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
			AttackCollision->SetCollisionPos(LEFTATTACKCOLLISIONPOS);
		}
		else
		{
			AttackCollision->SetCollisionPos(RIGHTTATTACKCOLLISIONPOS);
		}
		AttackCollision->SetCollisionScale(FIREATTACKCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}

	AttackCollision->Off();
	ChangeState(KirbyState::Idle);
}

void FireKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Fire_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Fire_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}