#include "TornadoMonster.h"
#include "ActorEnum.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

TornadoMonster::TornadoMonster()
{
}

TornadoMonster::~TornadoMonster()
{
}

void TornadoMonster::Start()
{
	SoundEffectLoad();

	if (ResourcesManager::GetInst().FindSprite("Right_TornadoEnermy.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_TornadoEnermy.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Enermy\\TornadoEnermy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_TornadoEnermy.Bmp"), 5, 5);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_TornadoEnermy.Bmp"), 5, 5);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Monster);

		MainRenderer->CreateAnimation("Right_Tornado_Monster_Idle", "Right_TornadoEnermy.Bmp", 0, 7, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Monster_Walk", "Right_TornadoEnermy.Bmp", 8, 9, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Monster_Attack", "Right_TornadoEnermy.Bmp", 10, 12, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Tornado_Monster_Inhale", "Right_TornadoEnermy.Bmp", 13, 13, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Monster_Damage", "Right_TornadoEnermy.Bmp", 13, 13, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Tornado_Monster_Death", "Right_TornadoEnermy.Bmp", 14, 21, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Tornado_Monster_Idle", "Left_TornadoEnermy.Bmp", 0, 7, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Monster_Walk", "Left_TornadoEnermy.Bmp", 8, 9, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Monster_Attack", "Left_TornadoEnermy.Bmp", 10, 12, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Tornado_Monster_Inhale", "Left_TornadoEnermy.Bmp", 13, 14, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Monster_Damage", "Left_TornadoEnermy.Bmp", 13, 14, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Tornado_Monster_Death", "Left_TornadoEnermy.Bmp", 14, 21, 0.1f, false);

		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionPos(MONSTERBODYCOLLISONPOS);
		BodyCollision->SetCollisionScale(MONSTERBODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);

		SearchCollision = CreateCollision(CollisionOrder::MonsterSearch);
		SearchCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		SearchCollision->SetCollisionScale(SEARCHCOLLISONSCALE);
		SearchCollision->SetCollisionType(CollisionType::Rect);

		AttackCollision = CreateCollision(CollisionOrder::MonsterAttack);
		AttackCollision->SetCollisionPos(MONSTERBODYCOLLISONPOS);
		AttackCollision->SetCollisionScale(TORNADOATTACKCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}

	AttackCollision->Off();
	ChangeState(MonsterState::Idle);
}

void TornadoMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Tornado_Monster_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Tornado_Monster_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}