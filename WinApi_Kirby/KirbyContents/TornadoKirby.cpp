#include "TornadoKirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

TornadoKirby::TornadoKirby()
{
}

TornadoKirby::~TornadoKirby()
{
}

void TornadoKirby::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Right_TornadoKirby.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_TornadoKirby.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\TornadoKirby\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_TornadoKirby.Bmp"), 10, 14);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_TornadoKirby.Bmp"), 10, 14);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Tornado_Idle", "Right_TornadoKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Down", "Right_TornadoKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Slide", "Right_TornadoKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Right_Tornado_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Right_Tornado_Jump", "Right_TornadoKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Tornado_JumpToDown", "Right_TornadoKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Tornado_JumpToLand", "Right_TornadoKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Walk", "Right_TornadoKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Run", "Right_TornadoKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Stop", "Right_TornadoKirby.Bmp", 42, 42, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Tornado_StopToIdle", "Right_TornadoKirby.Bmp", 43, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Breathe", "Right_TornadoKirby.Bmp", 45, 49, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Fly", "Right_TornadoKirby.Bmp", 50, 67, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Tornado_BreatheOutLand", "Right_TornadoKirby.Bmp", 68, 69, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Tornado_BreatheOut", "Right_TornadoKirby.Bmp", 68, 69, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Drop", "Right_TornadoKirby.Bmp", 70, 71, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Tornado_FlyToLand", "Right_TornadoKirby.Bmp", 83, 85, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Tornado_FlyToTurnUp", "Right_TornadoKirby.Bmp", 72, 78, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Tornado_FlyToTurnLand", "Right_TornadoKirby.Bmp", 79, 82, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Tornado_LevelMove", "Right_TornadoKirby.Bmp", 86, 89, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Damage", "Right_TornadoKirby.Bmp", 90, 92, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Tornado_DamageLand", "Right_TornadoKirby.Bmp", 93, 94, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Tornado_AttackReady", "Right_TornadoKirby.Bmp", 95, 101, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Tornado_AttackLoop", "Right_TornadoKirby.Bmp", 101, 116, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Attack", "Right_TornadoKirby.Bmp", 117, 119, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Tornado_Idle", "Left_TornadoKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Down", "Left_TornadoKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Slide", "Left_TornadoKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Left_Tornado_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Left_Tornado_Jump", "Left_TornadoKirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Tornado_JumpToDown", "Left_TornadoKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Tornado_JumpToLand", "Left_TornadoKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Walk", "Left_TornadoKirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Run", "Left_TornadoKirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Stop", "Left_TornadoKirby.Bmp", 42, 42, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Tornado_StopToIdle", "Left_TornadoKirby.Bmp", 43, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Breathe", "Left_TornadoKirby.Bmp", 45, 49, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Fly", "Left_TornadoKirby.Bmp", 50, 67, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Tornado_BreatheOutLand", "Left_TornadoKirby.Bmp", 68, 69, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Tornado_BreatheOut", "Left_TornadoKirby.Bmp", 68, 69, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Drop", "Left_TornadoKirby.Bmp", 70, 71, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Tornado_FlyToLand", "Left_TornadoKirby.Bmp", 83, 85, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Tornado_FlyToTurnUp", "Left_TornadoKirby.Bmp", 72, 78, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Tornado_FlyToTurnLand", "Left_TornadoKirby.Bmp", 79, 82, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Tornado_LevelMove", "Left_TornadoKirby.Bmp", 86, 89, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Damage", "Left_TornadoKirby.Bmp", 90, 92, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Tornado_DamageLand", "Left_TornadoKirby.Bmp", 93, 94, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Tornado_AttackReady", "Left_TornadoKirby.Bmp", 95, 101, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Tornado_AttackLoop", "Left_TornadoKirby.Bmp", 101, 116, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Attack", "Left_TornadoKirby.Bmp", 117, 119, 0.1f, false);

		MainRenderer->ChangeAnimation("Right_Tornado_Idle");
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
		AttackCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}

	AttackCollision->Off();
	ChangeState(KirbyState::Idle);
}

void TornadoKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Tornado_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Tornado_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}