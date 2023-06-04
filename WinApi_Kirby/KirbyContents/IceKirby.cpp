#include "IceKirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

IceKirby::IceKirby()
{
}

IceKirby::~IceKirby()
{
}

void IceKirby::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Right_IceKirby.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_IceKirby.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\IceKirby\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_IceKirby.Bmp"), 10, 14);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_IceKirby.Bmp"), 10, 14);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Ice_Idle", "Right_IceKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Ice_Down", "Right_IceKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Ice_Slide", "Right_IceKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Right_Ice_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Right_Ice_Jump", "Right_IceKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_JumpToDown", "Right_IceKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_JumpToLand", "Right_IceKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Ice_Walk", "Right_IceKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Ice_Run", "Right_IceKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Ice_Stop", "Right_IceKirby.Bmp", 42, 42, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Ice_StopToIdle", "Right_IceKirby.Bmp", 43, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Ice_Breathe", "Right_IceKirby.Bmp", 45, 49, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Ice_Fly", "Right_IceKirby.Bmp", 50, 67, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Ice_BreatheOutLand", "Right_IceKirby.Bmp", 68, 69, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_BreatheOut", "Right_IceKirby.Bmp", 68, 69, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Ice_Drop", "Right_IceKirby.Bmp", 70, 71, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Ice_FlyToLand", "Right_IceKirby.Bmp", 83, 85, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Ice_FlyToTurnUp", "Right_IceKirby.Bmp", 72, 78, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Ice_FlyToTurnLand", "Right_IceKirby.Bmp", 79, 82, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Ice_LevelMove", "Right_IceKirby.Bmp", 86, 89, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_Damage", "Right_IceKirby.Bmp", 90, 92, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Ice_DamageLand", "Right_IceKirby.Bmp", 93, 94, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Ice_AttackReady", "Right_IceKirby.Bmp", 95, 101, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_AttackLoop", "Right_IceKirby.Bmp", 101, 116, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Ice_Attack", "Right_IceKirby.Bmp", 117, 119, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Ice_Idle", "Left_IceKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Ice_Down", "Left_IceKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Ice_Slide", "Left_IceKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Left_Ice_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Left_Ice_Jump", "Left_IceKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_JumpToDown", "Left_IceKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_JumpToLand", "Left_IceKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Ice_Walk", "Left_IceKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Ice_Run", "Left_IceKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Ice_Stop", "Left_IceKirby.Bmp", 42, 42, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_StopToIdle", "Left_IceKirby.Bmp", 43, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Ice_Breathe", "Left_IceKirby.Bmp", 45, 49, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Ice_Fly", "Left_IceKirby.Bmp", 50, 67, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Ice_BreatheOutLand", "Left_IceKirby.Bmp", 68, 69, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_BreatheOut", "Left_IceKirby.Bmp", 68, 69, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Ice_Drop", "Left_IceKirby.Bmp", 70, 71, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Ice_FlyToLand", "Left_IceKirby.Bmp", 83, 85, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Ice_FlyToTurnUp", "Left_IceKirby.Bmp", 72, 78, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Ice_FlyToTurnLand", "Left_IceKirby.Bmp", 79, 82, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Ice_LevelMove", "Left_IceKirby.Bmp", 86, 89, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_Damage", "Left_IceKirby.Bmp", 90, 92, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Ice_DamageLand", "Left_IceKirby.Bmp", 93, 94, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Ice_AttackReady", "Left_IceKirby.Bmp", 95, 101, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_AttackLoop", "Left_IceKirby.Bmp", 101, 116, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_Attack", "Left_IceKirby.Bmp", 117, 119, 0.1f, false);

		MainRenderer->ChangeAnimation("Right_Ice_Idle");
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
		AttackCollision->SetCollisionScale(ICEATTACKCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}

	AttackCollision->Off();
	ChangeState(KirbyState::Idle);
}

void IceKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Ice_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Ice_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}