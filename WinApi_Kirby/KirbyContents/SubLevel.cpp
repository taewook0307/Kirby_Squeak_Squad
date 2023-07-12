#include "SubLevel.h"
#include "KirbyUI.h"
#include "Kirby.h"
#include "IceKirby.h"
#include "FireKirby.h"
#include "TornadoKirby.h"
#include "SparkKirby.h"
#include "Monster.h"
#include "TranslucentBlock.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineActor.h>

MonsterType SubLevel::LevelPlayerForm = MonsterType::Normal;
KirbyUI* SubLevel::LevelPlayerUI;
GameEngineSoundPlayer SubLevel::BGM;

int SubLevel::PlayerLifeCount = 3;

SubLevel::SubLevel()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	LevelPlayerUI = CreateActor<KirbyUI>(UpdateOrder::PlayUI);
	LevelPlayerUI->SetPos({ 0.0f, WinScale.Y });
}

SubLevel::~SubLevel()
{
}

void SubLevel::SetLevelPlayerForm(const MonsterType& _Value)
{
	LevelPlayerForm = _Value;
}

MonsterType& SubLevel::GetLevelPlayerForm()
{
	return LevelPlayerForm;
}

int SubLevel::GetPlayerLife()
{
	return PlayerLifeCount;
}

void SubLevel::MinusPlayerLife()
{
	--PlayerLifeCount;
}

void SubLevel::PlusPlayerLife()
{
	++PlayerLifeCount;
}

void SubLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (GetLevelPlayerForm() == MonsterType::Normal)
	{
		LevelPlayer = CreateActor<Kirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}
	else if (GetLevelPlayerForm() == MonsterType::Fire)
	{
		LevelPlayer = CreateActor<FireKirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
		if (nullptr != LevelPlayer->GetChangeBackGroundEffect())
		{
			LevelPlayer->GetChangeBackGroundEffect()->Death();
		}
	}
	else if (GetLevelPlayerForm() == MonsterType::Ice)
	{
		LevelPlayer = CreateActor<IceKirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
		if (nullptr != LevelPlayer->GetChangeBackGroundEffect())
		{
			LevelPlayer->GetChangeBackGroundEffect()->Death();
		}
	}
	else if (GetLevelPlayerForm() == MonsterType::Spark)
	{
		LevelPlayer = CreateActor<SparkKirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
		if (nullptr != LevelPlayer->GetChangeBackGroundEffect())
		{
			LevelPlayer->GetChangeBackGroundEffect()->Death();
		}
	}
	else if (GetLevelPlayerForm() == MonsterType::Tornado)
	{
		LevelPlayer = CreateActor<TornadoKirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
		if (nullptr != LevelPlayer->GetChangeBackGroundEffect())
		{
			LevelPlayer->GetChangeBackGroundEffect()->Death();
		}
	}

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅하지 못했습니다.");
		return;
	}
}

void SubLevel::FormChange(const std::string& _BitMapFileName)
{
	if (nullptr == LevelPlayer)
	{
		return;
	}

	if (true == GameEngineInput::IsDown('C')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Ice
		|| true == GameEngineInput::IsDown(VK_F5))
	{
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		SetLevelPlayerForm(MonsterType::Ice);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<IceKirby>(UpdateOrder::Player);
		LevelPlayer->ChangeForm();
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap(_BitMapFileName);
	}

	if (true == GameEngineInput::IsDown('C')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Spark
		|| true == GameEngineInput::IsDown(VK_F6))
	{
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		SetLevelPlayerForm(MonsterType::Spark);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<SparkKirby>(UpdateOrder::Player);
		LevelPlayer->ChangeForm();
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap(_BitMapFileName);
	}

	if (true == GameEngineInput::IsDown('C')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Fire
		|| true == GameEngineInput::IsDown(VK_F7))
	{
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		SetLevelPlayerForm(MonsterType::Fire);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<FireKirby>(UpdateOrder::Player);
		LevelPlayer->ChangeForm();
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap(_BitMapFileName);
	}

	if (true == GameEngineInput::IsDown('C')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Tornado
		|| true == GameEngineInput::IsDown(VK_F8))
	{
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		SetLevelPlayerForm(MonsterType::Tornado);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<TornadoKirby>(UpdateOrder::Player);
		LevelPlayer->ChangeForm();
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap(_BitMapFileName);
	}

	if (GetLevelPlayerForm() != MonsterType::Normal && true == GameEngineInput::IsDown('Z'))
	{
		SetLevelPlayerForm(MonsterType::Normal);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<Kirby>(UpdateOrder::Player);
		LevelPlayer->ChangeSoundOff();
		LevelPlayer->ChangeForm();
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap(_BitMapFileName);
		LevelPlayer->ClearForm();
	}
}

void SubLevel::AllMonsterDeath()
{
	std::list<Monster*>::iterator FirstIter = AllMonster.begin();
	std::list<Monster*>::iterator LastIter = AllMonster.end();

	for (; FirstIter != LastIter;)
	{
		Monster* CurMonster = *FirstIter;

		CurMonster->Death();

		FirstIter = AllMonster.erase(FirstIter);
	}

	return;
}