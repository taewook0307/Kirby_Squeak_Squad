#include "BossMonster.h"
#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

BossMonster* BossMonster::MainBoss;

BossMonster::BossMonster()
{
	MainBoss = this;
}

BossMonster::~BossMonster()
{
}

void BossMonster::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Right_Boss.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_Boss.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Boss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Boss.Bmp"), 5, 10);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Boss.Bmp"), 5, 10);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Boss);

		MainRenderer->CreateAnimation("Right_Boss_Idle", "Right_Boss.Bmp", 0, 3, 0.4f, true);
		MainRenderer->CreateAnimation("Right_Boss_Walk", "Right_Boss.Bmp", 4, 7, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Boss_JumpReady", "Right_Boss.Bmp", 8, 8, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Boss_Jump", "Right_Boss.Bmp", 9, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Boss_Drop", "Right_Boss.Bmp", 10, 10, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Boss_AttackReady", "Right_Boss.Bmp", 11, 14, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Boss_AttackRun", "Right_Boss.Bmp", 15, 18, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Boss_Attack", "Right_Boss.Bmp", 19, 23, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Boss_AttackToIdle", "Right_Boss.Bmp", 24, 24, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Boss_FlyReady", "Right_Boss.Bmp", 25, 26, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Boss_FlyUp", "Right_Boss.Bmp", 27, 27, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Boss_Fly", "Right_Boss.Bmp", 28, 29, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Boss_FlyDrop", "Right_Boss.Bmp", 30, 30, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Boss_MonsterSummonReady", "Right_Boss.Bmp", 31, 33, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Boss_MonsterSummonJump", "Right_Boss.Bmp", 34, 34, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Boss_MonsterSummonDrop", "Right_Boss.Bmp", 35, 35, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Boss_MonsterSummon", "Right_Boss.Bmp", 36, 43, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Boss_Damage", "Right_Boss.Bmp", 44, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Boss_DeathJump", "Right_Boss.Bmp", 44, 45, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Boss_Death", "Right_Boss.Bmp", 46, 47, 0.2f, true);

		MainRenderer->CreateAnimation("Left_Boss_Idle", "Left_Boss.Bmp", 0, 3, 0.4f, true);
		MainRenderer->CreateAnimation("Left_Boss_Walk", "Left_Boss.Bmp", 4, 7, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Boss_JumpReady", "Left_Boss.Bmp", 8, 8, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Boss_Jump", "Left_Boss.Bmp", 9, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Boss_Drop", "Left_Boss.Bmp", 10, 10, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Boss_AttackReady", "Left_Boss.Bmp", 11, 14, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Boss_AttackRun", "Left_Boss.Bmp", 15, 18, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Boss_Attack", "Left_Boss.Bmp", 19, 23, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Boss_AttackToIdle", "Left_Boss.Bmp", 24, 24, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Boss_FlyReady", "Left_Boss.Bmp", 25, 26, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Boss_FlyUp", "Left_Boss.Bmp", 27, 27, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Boss_Fly", "Left_Boss.Bmp", 28, 29, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Boss_FlyDrop", "Left_Boss.Bmp", 30, 30, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Boss_MonsterSummonReady", "Left_Boss.Bmp", 31, 33, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Boss_MonsterSummonJump", "Left_Boss.Bmp", 34, 34, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Boss_MonsterSummonDrop", "Left_Boss.Bmp", 35, 35, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Boss_MonsterSummon", "Left_Boss.Bmp", 36, 43, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Boss_Damage", "Left_Boss.Bmp", 44, 44, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Boss_DeathJump", "Left_Boss.Bmp", 44, 45, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Boss_Death", "Left_Boss.Bmp", 46, 47, 0.2f, true);
	
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::BossBody);
		BodyCollision->SetCollisionPos(BOSSBODYCOLLISIONPOS);
		BodyCollision->SetCollisionScale(BOSSBODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}

	ChangeState(BossState::Idle);
}

void BossMonster::Update(float _Delta)
{
	if (true == NoDamage)
	{
		NoDamageTimer -= _Delta;
	}

	if (NoDamageTimer < 0.0f)
	{
		NoDamage = false;
		NoDamageTimer = BOSSNODAMAGETIMERVALUE;
	}

	if (true == NoDamage && false == BossDeath)
	{
		BodyCollision->Off();
	}
	else if (false == NoDamage && false == BossDeath)
	{
		BodyCollision->On();
	}
	else
	{
		BodyCollision->Off();
	}

	StateUpdate(_Delta);

	if (true == BodyCollision->Collision(CollisionOrder::Attack, BossCol, CollisionType::Rect, CollisionType::Rect)
		|| true == BodyCollision->Collision(CollisionOrder::SpecialAttack, BossCol, CollisionType::Rect, CollisionType::Rect))
	{
		Damage();
		ChangeState(BossState::Damage);
		return;
	}

	if (true == BodyCollision->Collision(CollisionOrder::Body, BossCol, CollisionType::Rect, CollisionType::Rect)
		&& true == MainRenderer->IsAnimation("Left_Boss_Idle")
		&& true == MainRenderer->IsAnimation("Righdt_Boss_Idle")
		&& true == MainRenderer->IsAnimation("Left_Boss_Walk")
		&& true == MainRenderer->IsAnimation("Right_Boss_Walk"))
	{
		ChangeState(BossState::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		IsCheckPosPointChange();
	}
}

void BossMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BossState::Idle:
		return IdleUpdate(_Delta);
	case BossState::Walk:
		return WalkUpdate(_Delta);
	case BossState::JumpReady:
		return JumpReadyUpdate(_Delta);
	case BossState::Jump:
		return JumpUpdate(_Delta);
	case BossState::Drop:
		return DropUpdate(_Delta);
	case BossState::AttackReady:
		return AttackReadyUpdate(_Delta);
	case BossState::AttackRun:
		return AttackRunUpdate(_Delta);
	case BossState::Attack:
		return AttackUpdate(_Delta);
	case BossState::AttackToIdle:
		return AttackToIdleUpdate(_Delta);
	case BossState::FlyReady:
		return FlyReadyUpdate(_Delta);
	case BossState::FlyUp:
		return FlyUpUpdate(_Delta);
	case BossState::Fly:
		return FlyUpdate(_Delta);
	case BossState::FlyDrop:
		return FlyDropUpdate(_Delta);
	case BossState::MonsterSummonReady:
		return MonsterSummonReadyUpdate(_Delta);
	case BossState::MonsterSummonJump:
		return MonsterSummonJumpUpdate(_Delta);
	case BossState::MonsterSummonDrop:
		return MonsterSummonDropUpdate(_Delta);
	case BossState::MonsterSummon:
		return MonsterSummonUpdate(_Delta);
	case BossState::Damage:
		return DamageUpdate(_Delta);
	case BossState::DeathJump:
		return DeathJumpUpdate(_Delta);
	case BossState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void BossMonster::ChangeState(BossState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BossState::Idle:
			IdleStart();
			break;
		case BossState::Walk:
			WalkStart();
			break;
		case BossState::JumpReady:
			JumpReadyStart();
			break;
		case BossState::Jump:
			JumpStart();
			break;
		case BossState::Drop:
			DropStart();
			break;
		case BossState::AttackReady:
			AttackReadyStart();
			break;
		case BossState::AttackRun:
			AttackRunStart();
			break;
		case BossState::Attack:
			AttackStart();
			break;
		case BossState::AttackToIdle:
			AttackToIdleStart();
			break;
		case BossState::FlyReady:
			FlyReadyStart();
			break;
		case BossState::FlyUp:
			FlyUpStart();
			break;
		case BossState::Fly:
			FlyStart();
			break;
		case BossState::FlyDrop:
			FlyDropStart();
			break;
		case BossState::MonsterSummonReady:
			MonsterSummonReadyStart();
			break;
		case BossState::MonsterSummonJump:
			MonsterSummonJumpStart();
			break;
		case BossState::MonsterSummonDrop:
			MonsterSummonDropStart();
			break;
		case BossState::MonsterSummon:
			MonsterSummonStart();
			break;
		case BossState::Damage:
			DamageStart();
			break;
		case BossState::DeathJump:
			DeathJumpStart();
			break;
		case BossState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void BossMonster::DirChange()
{
	float4 KirbyPos = Kirby::GetMainKirby()->GetPos();
	float4 BossPos = GetPos();

	if (KirbyPos.X < BossPos.X)
	{
		Dir = ActorDir::Left;
		ChangeAnimationState(CurState);
	}
	else
	{
		Dir = ActorDir::Right;
		ChangeAnimationState(CurState);
	}
}

void BossMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Boss_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Boss_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

void BossMonster::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	if (true == IsCheckPosPoint)
	{
		Data.Pos = GetPos();
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}

	std::string HpText = "";
	HpText += "Hp : ";
	HpText += std::to_string(BossHp);
	TextOutA(dc, 2, 120, HpText.c_str(), static_cast<int>(HpText.size()));
}