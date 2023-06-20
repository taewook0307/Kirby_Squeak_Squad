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

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_IceKirby.Bmp"), 10, 16);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_IceKirby.Bmp"), 10, 16);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Ice_Idle", "Right_IceKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Ice_Down", "Right_IceKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Ice_Slide", "Right_IceKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Right_Ice_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Right_Ice_Jump", "Right_IceKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_JumpToDrop", "Right_IceKirby.Bmp", 15, 22, 0.01f, false);
		MainRenderer->CreateAnimation("Right_Ice_JumpToLand", "Right_IceKirby.Bmp", 23, 23, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Ice_Walk", "Right_IceKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Ice_Run", "Right_IceKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Ice_Stop", "Right_IceKirby.Bmp", 42, 45, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Ice_Breathe", "Right_IceKirby.Bmp", 48, 53, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Ice_Fly", "Right_IceKirby.Bmp", 54, 71, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Ice_BreatheOut", "Right_IceKirby.Bmp", 72, 73, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Ice_Drop", "Right_IceKirby.Bmp", 74, 75, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Ice_FlyToLand", "Right_IceKirby.Bmp", 89, 89, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Ice_FlyToTurnUp", "Right_IceKirby.Bmp", 76, 86, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Ice_FlyToTurnLand", "Right_IceKirby.Bmp", 87, 88, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Ice_LevelMove", "Right_IceKirby.Bmp", 90, 93, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_Damage", "Right_IceKirby.Bmp", 94, 96, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_DamageLand", "Right_IceKirby.Bmp", 97, 98, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_AttackReady", "Right_IceKirby.Bmp", 99, 104, 0.01f, false);
		MainRenderer->CreateAnimation("Right_Ice_Attack", "Right_IceKirby.Bmp", 105, 120, 0.01f, true);
		MainRenderer->CreateAnimation("Right_Ice_AttackToIdle", "Right_IceKirby.Bmp", 121, 123, 0.01f, false);
		MainRenderer->CreateAnimation("Right_Ice_Change", "Right_IceKirby.Bmp", 124, 136, 0.05f, false);
		MainRenderer->FindAnimation("Right_Ice_Change")->Inters[7] = 0.3f;
		MainRenderer->CreateAnimation("Right_Ice_Death", "Right_IceKirby.Bmp", 137, 151, 0.1f, true);

		MainRenderer->CreateAnimation("Left_Ice_Idle", "Left_IceKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Ice_Down", "Left_IceKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Ice_Slide", "Left_IceKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Left_Ice_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Left_Ice_Jump", "Left_IceKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_JumpToDrop", "Left_IceKirby.Bmp", 15, 22, 0.01f, false);
		MainRenderer->CreateAnimation("Left_Ice_JumpToLand", "Left_IceKirby.Bmp", 23, 23, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Ice_Walk", "Left_IceKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Ice_Run", "Left_IceKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Ice_Stop", "Left_IceKirby.Bmp", 42, 45, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_Breathe", "Left_IceKirby.Bmp", 48, 53, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Ice_Fly", "Left_IceKirby.Bmp", 54, 71, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_BreatheOut", "Left_IceKirby.Bmp", 72, 73, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Ice_Drop", "Left_IceKirby.Bmp", 74, 75, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_FlyToLand", "Left_IceKirby.Bmp", 89, 89, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_FlyToTurnUp", "Left_IceKirby.Bmp", 76, 86, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Ice_FlyToTurnLand", "Left_IceKirby.Bmp", 87, 88, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Ice_LevelMove", "Left_IceKirby.Bmp", 90, 93, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_Damage", "Left_IceKirby.Bmp", 94, 96, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_DamageLand", "Left_IceKirby.Bmp", 97, 98, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_AttackReady", "Left_IceKirby.Bmp", 99, 104, 0.01f, false);
		MainRenderer->CreateAnimation("Left_Ice_Attack", "Left_IceKirby.Bmp", 105, 120, 0.01f, true);
		MainRenderer->CreateAnimation("Left_Ice_AttackToIdle", "Left_IceKirby.Bmp", 121, 123, 0.01f, false);
		MainRenderer->CreateAnimation("Left_Ice_Change", "Left_IceKirby.Bmp", 124, 136, 0.05f, false);
		MainRenderer->FindAnimation("Left_Ice_Change")->Inters[7] = 0.3f;
		MainRenderer->CreateAnimation("Left_Ice_Death", "Left_IceKirby.Bmp", 137, 151, 0.1f, true);

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
	ChangeState(KirbyState::Change);
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