#include "SubLevel.h"
#include "KirbyUI.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineActor.h>

MonsterType SubLevel::LevelPlayerForm = MonsterType::Normal;
KirbyUI* SubLevel::LevelPlayerUI;

int SubLevel::PlayerLifeCount = 3;

SubLevel::SubLevel()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	LevelPlayerUI = CreateActor<KirbyUI>(RenderOrder::PlayUI);
	LevelPlayerUI->SetPos({ 100.0f, WinScale.Y - 100.0f });
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