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

	if(ResourcesManager::GetInst().FindSprite("Right_Kirby.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_Kirby.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\Normal\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Kirby.Bmp"), 10, 16);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Kirby.Bmp"), 10, 16);
	}
	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		
		// Right Animaition
		MainRenderer->CreateAnimation("Right_Idle", "Right_Kirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Down", "Right_Kirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Slide", "Right_Kirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Right_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Right_Jump", "Right_Kirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Right_JumpToDrop", "Right_Kirby.Bmp", 15, 22, 0.03f, false);
		MainRenderer->CreateAnimation("Right_JumpToLand", "Right_Kirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Walk", "Right_Kirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Run", "Right_Kirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Stop", "Right_Kirby.Bmp", 42, 45, 0.1f, true);
		MainRenderer->CreateAnimation("Right_StopToIdle", "Right_Kirby.Bmp", 46, 47, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Breathe", "Right_Kirby.Bmp", 48, 54, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Fly", "Right_Kirby.Bmp", 55, 72, 0.2f, true);
		MainRenderer->CreateAnimation("Right_BreatheOutLand", "Right_Kirby.Bmp", 73, 74, 0.1f, false);
		MainRenderer->CreateAnimation("Right_BreatheOut", "Right_Kirby.Bmp", 73, 74, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Drop", "Right_Kirby.Bmp", 75, 76, 0.2f, false);
		MainRenderer->CreateAnimation("Right_FlyToLand", "Right_Kirby.Bmp", 88, 90, 0.3f, true);
		MainRenderer->CreateAnimation("Right_FlyToTurnUp", "Right_Kirby.Bmp", 77, 83, 0.2f, false);
		MainRenderer->CreateAnimation("Right_FlyToTurnLand", "Right_Kirby.Bmp", 84, 87, 0.2f, false);
		MainRenderer->CreateAnimation("Right_LevelMove", "Right_Kirby.Bmp", 91, 94, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Damage", "Right_Kirby.Bmp", 95, 97, 0.2f, false);
		MainRenderer->CreateAnimation("Right_DamageLand", "Right_Kirby.Bmp", 98, 99, 0.3f, false);
		MainRenderer->CreateAnimation("Right_AttackReady", "Right_Kirby.Bmp", 100, 103, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Attack", "Right_Kirby.Bmp", 104, 105, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Keep", "Right_Kirby.Bmp", 106, 112, 0.1f, false);
		MainRenderer->CreateAnimation("Right_AttackToIdle", "Right_Kirby.Bmp", 113, 117, 0.1f, false);
		MainRenderer->CreateAnimation("Right_KeepIdle", "Right_Kirby.Bmp", 127, 128, 0.5f, true);
		MainRenderer->CreateAnimation("Right_KeepJumpUp", "Right_Kirby.Bmp", 129, 133, 0.1f, false);
		MainRenderer->CreateAnimation("Right_KeepJumpDrop", "Right_Kirby.Bmp", 134, 135, 0.1f, false);
		MainRenderer->CreateAnimation("Right_KeepJumpLand", "Right_Kirby.Bmp", 136, 136, 0.3f, false);
		MainRenderer->CreateAnimation("Right_KeepWalk", "Right_Kirby.Bmp", 137, 152, 0.05f, true);
		MainRenderer->CreateAnimation("Right_KeepDamage", "Right_Kirby.Bmp", 153, 156, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Change", "Right_Kirby.Bmp", 118, 126, 0.1f, false);

		// Left Animaition
		MainRenderer->CreateAnimation("Left_Idle", "Left_Kirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Down", "Left_Kirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Slide", "Left_Kirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->FindAnimation("Left_Slide")->Inters[9] = 0.2f;
		MainRenderer->CreateAnimation("Left_Jump", "Left_Kirby.Bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("Left_JumpToDrop", "Left_Kirby.Bmp", 15, 22, 0.03f, false);
		MainRenderer->CreateAnimation("Left_JumpToLand", "Left_Kirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Walk", "Left_Kirby.Bmp", 24, 33, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Run", "Left_Kirby.Bmp", 34, 41, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Stop", "Left_Kirby.Bmp", 42, 45, 0.1f, true);
		MainRenderer->CreateAnimation("Left_StopToIdle", "Left_Kirby.Bmp", 46, 47, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Breathe", "Left_Kirby.Bmp", 48, 54, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Fly", "Left_Kirby.Bmp", 55, 72, 0.2f, true);
		MainRenderer->CreateAnimation("Left_BreatheOutLand", "Left_Kirby.Bmp", 73, 74, 0.1f, false);
		MainRenderer->CreateAnimation("Left_BreatheOut", "Left_Kirby.Bmp", 73, 74, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Drop", "Left_Kirby.Bmp", 75, 76, 0.2f, false);
		MainRenderer->CreateAnimation("Left_FlyToLand", "Left_Kirby.Bmp", 88, 90, 0.3f, true);
		MainRenderer->CreateAnimation("Left_FlyToTurnUp", "Left_Kirby.Bmp", 77, 83, 0.2f, false);
		MainRenderer->CreateAnimation("Left_FlyToTurnLand", "Left_Kirby.Bmp", 84, 87, 0.2f, false);
		MainRenderer->CreateAnimation("Left_LevelMove", "Left_Kirby.Bmp", 91, 94, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Damage", "Left_Kirby.Bmp", 95, 97, 0.2f, false);
		MainRenderer->CreateAnimation("Left_DamageLand", "Left_Kirby.Bmp", 98, 99, 0.3f, false);
		MainRenderer->CreateAnimation("Left_AttackReady", "Left_Kirby.Bmp", 100, 103, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Attack", "Left_Kirby.Bmp", 104, 105, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Keep", "Left_Kirby.Bmp", 106, 112, 0.1f, false);
		MainRenderer->CreateAnimation("Left_AttackToIdle", "Left_Kirby.Bmp", 113, 117, 0.1f, false);
		MainRenderer->CreateAnimation("Left_KeepIdle", "Left_Kirby.Bmp", 127, 128, 0.5f, true);
		MainRenderer->CreateAnimation("Left_KeepJump", "Left_Kirby.Bmp", 129, 133, 0.1f, false);
		MainRenderer->CreateAnimation("Left_KeepJumpDrop", "Left_Kirby.Bmp", 134, 135, 0.1f, false);
		MainRenderer->CreateAnimation("Left_KeepJumpLand", "Left_Kirby.Bmp", 136, 136, 0.3f, false);
		MainRenderer->CreateAnimation("Left_KeepWalk", "Left_Kirby.Bmp", 137, 152, 0.05f, true);
		MainRenderer->CreateAnimation("Left_KeepDamage", "Left_Kirby.Bmp", 153, 156, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Change", "Left_Kirby.Bmp", 118, 126, 0.1f, false);

		// Setting
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}
	{
		BodyCollision = CreateCollision(CollisionOrder::Body);
		BodyCollision->SetCollisionPos(BODYCOLLISIONPOS);
		BodyCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);

		InhaleCollision = CreateCollision(CollisionOrder::Inhale);
		InhaleCollision->SetCollisionScale(INHALECOLLSIONSCALE);
		InhaleCollision->SetCollisionType(CollisionType::Rect);
	}

	InhaleCollision->Off();
	ChangeState(KirbyState::Idle);
}

void Kirby::Update(float _Delta)
{
	StateUpdate(_Delta);

	Col.reserve(Col.size() + 1);
	if (true == BodyCollision->Collision(CollisionOrder::MonsterBody, Col, CollisionType::Rect, CollisionType::Rect)
		|| true == BodyCollision->Collision(CollisionOrder::MonsterAttack, Col, CollisionType::Rect, CollisionType::Rect))
	{
		float4 Pos = Col[Col.size() - 1]->GetActorPivotPos();
		ChangeState(KirbyState::Damage);
		return;
	}

	// Debug 용
	if (true == GameEngineInput::IsDown('J'))
	{
		IsCheckPosPointChange();
	}
}

void Kirby::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	std::string XText = "";
	XText += "플레이어 위치 X 값 : ";
	XText += std::to_string(GetPos().X);
	TextOutA(dc, 2, 3, XText.c_str(), static_cast<int>(XText.size()));

	std::string YText = "";
	YText += "플레이어 위치 Y 값 : ";
	YText += std::to_string(GetPos().Y);
	TextOutA(dc, 2, 30, YText.c_str(), static_cast<int>(YText.size()));

	std::string FrameText = "";
	FrameText += "Frame : ";
	FrameText += std::to_string(1.0f / _Delta);
	TextOutA(dc, 2, 60, FrameText.c_str(), static_cast<int>(FrameText.size()));

	CollisionData Data;

	if (true == IsCheckPosPoint)
	{
		Data.Pos = ActorCameraPos();
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 TOPCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 LEFTTOPCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 RIGHTTOPCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 LEFTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 RIGHTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 LEFTBOTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 RIGHTBOTCHECKPOS;
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
	case KirbyState::JumpToDrop:
		return JumpToDropUpdate(_Delta);
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
	case KirbyState::Attack:
		return AttackUpdate(_Delta);
	case KirbyState::AttackToIdle:
		return AttackToIdleUpdate(_Delta);
	case KirbyState::Keep:
		return KeepUpdate(_Delta);
	case KirbyState::KeepIdle:
		return KeepIdleUpdate(_Delta);
	case KirbyState::KeepWalk:
		return KeepWalkUpdate(_Delta);
	case KirbyState::Change:
		return ChangeUpdate(_Delta);
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
		case KirbyState::JumpToDrop:
			JumpToDropStart();
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
		case KirbyState::Attack:
			AttackStart();
			break;
		case KirbyState::AttackToIdle:
			AttackToIdleStart();
			break;
		case KirbyState::Keep:
			KeepStart();
			break;
		case KirbyState::KeepIdle:
			KeepIdleStart();
			break;
		case KirbyState::KeepWalk:
			KeepWalkStart();
			break;
		case KirbyState::Change:
			ChangeStart();
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

	GetLevel()->GetMainCamera()->AddPos({ _MovePos.X, 0.0f });
}