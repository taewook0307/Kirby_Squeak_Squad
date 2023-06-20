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

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_TornadoKirby.Bmp"), 10, 20);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_TornadoKirby.Bmp"), 10, 20);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Tornado_Idle", "Right_TornadoKirby.Bmp", 0, 7, 0.125f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Down", "Right_TornadoKirby.Bmp", 8, 15, 0.125f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Slide", "Right_TornadoKirby.Bmp", 16, 25, 0.1f, false);
		MainRenderer->FindAnimation("Right_Tornado_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Right_Tornado_Jump", "Right_TornadoKirby.Bmp", 26, 27, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Tornado_JumpToDrop", "Right_TornadoKirby.Bmp", 28, 35, 0.01f, false);
		MainRenderer->CreateAnimation("Right_Tornado_JumpToLand", "Right_TornadoKirby.Bmp", 36, 36, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Walk", "Right_TornadoKirby.Bmp", 37, 56, 0.025f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Run", "Right_TornadoKirby.Bmp", 57, 64, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Stop", "Right_TornadoKirby.Bmp", 65, 68, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Breathe", "Right_TornadoKirby.Bmp", 71, 76, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Fly", "Right_TornadoKirby.Bmp", 77, 105, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Tornado_BreatheOut", "Right_TornadoKirby.Bmp", 106, 107, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Drop", "Right_TornadoKirby.Bmp", 108, 109, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Tornado_FlyToLand", "Right_TornadoKirby.Bmp", 124, 124, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Tornado_FlyToTurnUp", "Right_TornadoKirby.Bmp", 110, 121, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Tornado_FlyToTurnLand", "Right_TornadoKirby.Bmp", 122, 123, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Tornado_LevelMove", "Right_TornadoKirby.Bmp", 125, 128, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Damage", "Right_TornadoKirby.Bmp", 129, 131, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Tornado_DamageLand", "Right_TornadoKirby.Bmp", 132, 135, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Tornado_AttackReady", "Right_TornadoKirby.Bmp", 136, 147, 0.01f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Attack", "Right_TornadoKirby.Bmp", 148, 155, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Tornado_AttackToIdle", "Right_TornadoKirby.Bmp", 156, 168, 0.01f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Change", "Right_TornadoKirby.Bmp", 169, 183, 0.05f, false);
		MainRenderer->FindAnimation("Right_Tornado_Change")->Inters[7] = 0.3f;
		MainRenderer->CreateAnimation("Right_Tornado_Death", "Right_TornadoKirby.Bmp", 184, 199, 0.1f, true);

		MainRenderer->CreateAnimation("Left_Tornado_Idle", "Left_TornadoKirby.Bmp", 0, 7, 0.125f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Down", "Left_TornadoKirby.Bmp", 8, 15, 0.125f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Slide", "Left_TornadoKirby.Bmp", 16, 25, 0.1f, false);
		MainRenderer->FindAnimation("Left_Tornado_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Left_Tornado_Jump", "Left_TornadoKirby.Bmp", 26, 27, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Tornado_JumpToDrop", "Left_TornadoKirby.Bmp", 28, 35, 0.01f, false);
		MainRenderer->CreateAnimation("Left_Tornado_JumpToLand", "Left_TornadoKirby.Bmp", 36, 36, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Walk", "Left_TornadoKirby.Bmp", 37, 56, 0.025f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Run", "Left_TornadoKirby.Bmp", 57, 64, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Stop", "Left_TornadoKirby.Bmp", 65, 68, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Breathe", "Left_TornadoKirby.Bmp", 71, 76, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Fly", "Left_TornadoKirby.Bmp", 77, 105, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Tornado_BreatheOut", "Left_TornadoKirby.Bmp", 106, 107, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Drop", "Left_TornadoKirby.Bmp", 108, 109, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Tornado_FlyToLand", "Left_TornadoKirby.Bmp", 124, 124, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Tornado_FlyToTurnUp", "Left_TornadoKirby.Bmp", 110, 121, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Tornado_FlyToTurnLand", "Left_TornadoKirby.Bmp", 122, 123, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Tornado_LevelMove", "Left_TornadoKirby.Bmp", 125, 128, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Damage", "Left_TornadoKirby.Bmp", 129, 131, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Tornado_DamageLand", "Left_TornadoKirby.Bmp", 132, 135, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Tornado_AttackReady", "Left_TornadoKirby.Bmp", 136, 147, 0.01f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Attack", "Left_TornadoKirby.Bmp", 148, 155, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Tornado_AttackToIdle", "Left_TornadoKirby.Bmp", 156, 168, 0.01f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Change", "Left_TornadoKirby.Bmp", 169, 183, 0.05f, false);
		MainRenderer->FindAnimation("Left_Tornado_Change")->Inters[7] = 0.3f;
		MainRenderer->CreateAnimation("Left_Tornado_Death", "Left_TornadoKirby.Bmp", 184, 199, 0.1f, true);

		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::Body);
		BodyCollision->SetCollisionPos(BODYCOLLISIONPOS);
		BodyCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);

		AttackCollision = CreateCollision(CollisionOrder::Attack);
		AttackCollision->SetCollisionPos(BODYCOLLISIONPOS);
		AttackCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}

	AttackCollision->Off();
	ChangeState(KirbyState::Change);
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