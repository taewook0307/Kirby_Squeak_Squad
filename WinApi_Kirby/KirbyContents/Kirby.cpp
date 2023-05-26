#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>

Kirby::Kirby()
{
}

Kirby::~Kirby()
{
}

void Kirby::Start()
{
	IsCheckPosPoint = false;
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\Normal\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Kirby.Bmp"), 10, 21);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Kirby.Bmp"), 10, 21);
	}
	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		
		// Right Animaition
		MainRenderer->CreateAnimation("Right_Idle", "Right_Kirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Down", "Right_Kirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Slide", "Right_Kirby.Bmp", 4, 5, 1.0f, false);
		MainRenderer->FindAnimation("Right_Slide")->Inters[1] = 0.2f;
		MainRenderer->CreateAnimation("Right_Jump", "Right_Kirby.Bmp", 6, 6, 0.1f, true);
		MainRenderer->CreateAnimation("Right_JumpToDown", "Right_Kirby.Bmp", 7, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Right_JumpToLand", "Right_Kirby.Bmp", 15, 15, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Walk", "Right_Kirby.Bmp", 16, 25, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Run", "Right_Kirby.Bmp", 26, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Stop", "Right_Kirby.Bmp", 34, 34, 0.1f, true);
		MainRenderer->CreateAnimation("Right_StopToIdle", "Right_Kirby.Bmp", 35, 36, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Breathe", "Right_Kirby.Bmp", 37, 41, 0.2f, false);
		MainRenderer->FindAnimation("Right_Breathe")->Inters[4] = 0.4f;
		MainRenderer->CreateAnimation("Right_Fly", "Right_Kirby.Bmp", 42, 59, 0.2f, true);
		MainRenderer->CreateAnimation("Right_BreatheOutLand", "Right_Kirby.Bmp", 101, 103, 0.1f, false);
		MainRenderer->CreateAnimation("Right_BreatheOut", "Right_Kirby.Bmp", 60, 61, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Drop", "Right_Kirby.Bmp", 62, 63, 0.2f, false);
		MainRenderer->CreateAnimation("Right_FlyToLand", "Right_Kirby.Bmp", 77, 77, 0.3f, true);
		MainRenderer->CreateAnimation("Right_FlyToTurnUp", "Right_Kirby.Bmp", 64, 70, 0.2f, false);
		MainRenderer->CreateAnimation("Right_FlyToTurnLand", "Right_Kirby.Bmp", 70, 76, 0.2f, false);
		MainRenderer->CreateAnimation("Right_LevelMove", "Right_Kirby.Bmp", 78, 81, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Damage", "Right_Kirby.Bmp", 82, 84, 0.2f, false);
		MainRenderer->CreateAnimation("Right_DamageLand", "Right_Kirby.Bmp", 85, 86, 0.3f, false);
		MainRenderer->CreateAnimation("Right_AttackReady", "Right_Kirby.Bmp", 87, 91, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Keep", "Right_Kirby.Bmp", 92, 98, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Attack", "Right_Kirby.Bmp", 99, 103, 0.1f, false);

		// Left Animaition
		MainRenderer->CreateAnimation("Left_Idle", "Left_Kirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Down", "Left_Kirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Slide", "Left_Kirby.Bmp", 4, 5, 1.0f, false);
		MainRenderer->FindAnimation("Left_Slide")->Inters[1] = 0.2f;
		MainRenderer->CreateAnimation("Left_Jump", "Left_Kirby.Bmp", 6, 6, 0.1f, true);
		MainRenderer->CreateAnimation("Left_JumpToDown", "Left_Kirby.Bmp", 7, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Left_JumpToLand", "Left_Kirby.Bmp", 15, 15, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Walk", "Left_Kirby.Bmp", 16, 25, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Run", "Left_Kirby.Bmp", 26, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Stop", "Left_Kirby.Bmp", 34, 34, 0.1f, true);
		MainRenderer->CreateAnimation("Left_StopToIdle", "Left_Kirby.Bmp", 35, 36, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Breathe", "Left_Kirby.Bmp", 37, 41, 0.2f, false);
		MainRenderer->FindAnimation("Left_Breathe")->Inters[4] = 0.4f;
		MainRenderer->CreateAnimation("Left_Fly", "Left_Kirby.Bmp", 42, 59, 0.2f, true);
		MainRenderer->CreateAnimation("Left_BreatheOutLand", "Left_Kirby.Bmp", 101, 103, 0.1f, false);
		MainRenderer->CreateAnimation("Left_BreatheOut", "Left_Kirby.Bmp", 60, 61, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Drop", "Left_Kirby.Bmp", 62, 63, 0.2f, false);
		MainRenderer->CreateAnimation("Left_FlyToLand", "Left_Kirby.Bmp", 77, 77, 0.3f, true);
		MainRenderer->CreateAnimation("Left_FlyToTurnUp", "Left_Kirby.Bmp", 64, 70, 0.2f, false);
		MainRenderer->CreateAnimation("Left_FlyToTurnLand", "Left_Kirby.Bmp", 70, 76, 0.2f, false);
		MainRenderer->CreateAnimation("Left_LevelMove", "Left_Kirby.Bmp", 78, 81, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Damage", "Left_Kirby.Bmp", 82, 84, 0.2f, false);
		MainRenderer->CreateAnimation("Left_DamageLand", "Left_Kirby.Bmp", 85, 86, 0.3f, false);
		MainRenderer->CreateAnimation("Left_AttackReady", "Left_Kirby.Bmp", 87, 91, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Keep", "Left_Kirby.Bmp", 92, 98, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Attack", "Left_Kirby.Bmp", 99, 103, 0.1f, false);

		// Setting
		MainRenderer->ChangeAnimation("Right_Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(4.0f);
	}
	{
		BodyCollision = CreateCollision(CollisionOrder::Body);
		BodyCollision->SetCollisionPos(BODYCOLLISIONPOS);
		BodyCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}

	ChangeState(KirbyState::Idle);
}

void Kirby::Update(float _Delta)
{
	StateUpdate(_Delta);

	std::vector<GameEngineCollision*> Col;
	if (true == BodyCollision->Collision(CollisionOrder::MonsterBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		BodyCollision->Off();
		ChangeState(KirbyState::Damage);
		return;
	}
}

void Kirby::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	if (true == IsCheckPosPoint)
	{
		Data.Pos = ActorCameraPos();
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 LEFTMOVECHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 RIGHTMOVECHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 LEFTDROPCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 RIGHTDROPCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 UPCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
}

void Kirby::StateUpdate(float _Delta)
{
	switch (State)
	{
	case KirbyState::Idle:
		return IdleUpdate(_Delta);
	case KirbyState::Down:
		return DownUpdate(_Delta);
	case KirbyState::Slide:
		return SlideUpdate(_Delta);
	case KirbyState::Jump:
		return JumpUpdate(_Delta);
	case KirbyState::JumpToDown:
		return JumpToDownUpdate(_Delta);
	case KirbyState::JumpToLand:
		return JumpToLandUpdate(_Delta);
	case KirbyState::Walk:
		return WalkUpdate(_Delta);
	case KirbyState::Run:
		return RunUpdate(_Delta);
	case KirbyState::Stop:
		return StopUpdate(_Delta);
	case KirbyState::StopToIdle:
		return StopToIdleUpdate(_Delta);
	case KirbyState::Breathe:
		return BreatheUpdate(_Delta);
	case KirbyState::Fly:
		return FlyUpdate(_Delta);
	case KirbyState::BreatheOutLand:
		return BreatheOutLandUpdate(_Delta);
	case KirbyState::BreatheOut:
		return BreatheOutUpdate(_Delta);
	case KirbyState::Drop:
		return DropUpdate(_Delta);
	case KirbyState::FlyToLand:
		return FlyToLandUpdate(_Delta);
	case KirbyState::FlyToTurnUp:
		return FlyToTurnUpUpdate(_Delta);
	case KirbyState::FlyToTurnLand:
		return FlyToTurnLandUpdate(_Delta);
	case KirbyState::LevelMove:
		return LevelMoveUpdate(_Delta);
	case KirbyState::Damage:
		return DamageUpdate(_Delta);
	case KirbyState::DamageLand:
		return DamageLandUpdate(_Delta);
	case KirbyState::AttackReady:
		return AttackReadyUpdate(_Delta);
	case KirbyState::Keep:
		return KeepUpdate(_Delta);
	case KirbyState::Attack:
		return AttackUpdate(_Delta);
	default:
		break;
	}
}

void Kirby::ChangeState(KirbyState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case KirbyState::Idle:
			IdleStart();
			break;
		case KirbyState::Down:
			DownStart();
			break;
		case KirbyState::Slide:
			SlideStart();
			break;
		case KirbyState::Jump:
			JumpStart();
			break;
		case KirbyState::JumpToDown:
			JumpToDownStart();
			break;
		case KirbyState::JumpToLand:
			JumpToLandStart();
			break;
		case KirbyState::Walk:
			WalkStart();
			break;
		case KirbyState::Run:
			RunStart();
			break;
		case KirbyState::Stop:
			StopStart();
			break;
		case KirbyState::StopToIdle:
			StopToIdleStart();
			break;
		case KirbyState::Breathe:
			BreatheStart();
			break;
		case KirbyState::Fly:
			FlyStart();
			break;
		case KirbyState::BreatheOutLand:
			BreatheOutLandStart();
			break;
		case KirbyState::BreatheOut:
			BreatheOutStart();
			break;
		case KirbyState::Drop:
			DropStart();
			break;
		case KirbyState::FlyToLand:
			FlyToLandStart();
			break;
		case KirbyState::FlyToTurnUp:
			FlyToTurnUpStart();
			break;
		case KirbyState::FlyToTurnLand:
			FlyToTurnLandStart();
			break;
		case KirbyState::LevelMove:
			LevelMoveStart();
			break;
		case KirbyState::Damage:
			DamageStart();
			break;
		case KirbyState::DamageLand:
			DamageLandStart();
			break;
		case KirbyState::AttackReady:
			AttackReadyStart();
			break;
		case KirbyState::Keep:
			KeepStart();
			break;
		case KirbyState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void Kirby::DirCheck()
{
	ActorDir CheckDir = Dir;

	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsDown('Q'))
	{
		CheckDir = ActorDir::Left;
	}
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsDown('E'))
	{
		CheckDir = ActorDir::Right;
	}

	if (CheckDir != Dir)
	{
		Dir = CheckDir;
		ChangeAnimationState(CurState);
	}
}

void Kirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

void Kirby::CameraMove(float4 _MovePos)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 BitMapScale = GetGroundBitMap()->GetScale();
	float4 MovePos = _MovePos;

	CameraPos += MovePos;

	// 카메라가 맵 왼쪽 밖으로 이동할 경우
	if (CameraPos.X <= 0)
	{
		return;
	}

	// 커비의 위치가 비트맵의 왼쪽 끝부분일 경우
	if (GetPos().X <= WinScale.Half().Half().X)
	{
		return;
	}

	// 카메라가 맵 오른쪽 밖으로 이동할 경우
	if (CameraPos.X + WinScale.X >= BitMapScale.X)
	{
		return;
	}

	// 커비의 위치가 비트맵의 끝부분일 경우
	if (GetPos().X <= BitMapScale.X && GetPos().X >= BitMapScale.X - WinScale.Half().Half().X - WinScale.Half().X)
	{
		return;
	}

	GetLevel()->GetMainCamera()->AddPos(_MovePos);
}