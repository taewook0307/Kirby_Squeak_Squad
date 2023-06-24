#include "FormKirby.h"
#include "TranslucentBlock.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>

FormKirby::FormKirby()
{
}

FormKirby::~FormKirby()
{
}

void FormKirby::StateUpdate(float _Delta)
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
	case KirbyState::Breathe:
		return BreatheUpdate(_Delta);
	case KirbyState::Fly:
		return FlyUpdate(_Delta);
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
	case KirbyState::Change:
		return ChangeUpdate(_Delta);
	case KirbyState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void FormKirby::ChangeState(KirbyState _State)
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
		case KirbyState::Breathe:
			BreatheStart();
			break;
		case KirbyState::Fly:
			FlyStart();
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
		case KirbyState::Change:
			ChangeStart();
			break;
		case KirbyState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}


void FormKirby::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}

void FormKirby::AttackToIdleStart()
{
	ChangeAnimationState("AttackToIdle");
}

void FormKirby::ChangeStart()
{
	ChangeAnimationState("Change");
	if (true == ChangeSound)
	{
		GameEngineSound::SoundPlay("Change.wav");
	}
	ChangeBackGroundEffect = GetLevel()->CreateActor<TranslucentBlock>(UpdateOrder::PlayUI);
}

void FormKirby::ChangeUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
		{
			ChangeBackGroundEffect->Death();
			ChangeState(KirbyState::Walk);
			return;
		}

		ChangeBackGroundEffect->Death();
		ChangeState(KirbyState::Idle);
		return;
	}
}