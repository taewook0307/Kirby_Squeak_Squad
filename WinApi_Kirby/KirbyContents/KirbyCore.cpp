#include "KirbyCore.h"
#include "TitleLevel.h"
#include "FirstStageLevel.h"
#include "SecondStageLevel.h"
#include "ThirdStageLevel.h"
#include "BossEntranceLevel.h"
#include "BossStageLevel.h"
#include "EndingLevel.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>

KirbyCore::KirbyCore()
{
}

KirbyCore::~KirbyCore()
{
}

void KirbyCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1024, 768 });
	
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<FirstStageLevel>("FirstStageLevel");
	GameEngineCore::CreateLevel<SecondStageLevel>("SecondStageLevel");
	GameEngineCore::CreateLevel<ThirdStageLevel>("ThirdStageLevel");
	GameEngineCore::CreateLevel<BossEntranceLevel>("BossEntranceLevel");
	GameEngineCore::CreateLevel<BossStageLevel>("BossStageLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");

	GameEngineCore::ChangeLevel("BossEntranceLevel");
}

void KirbyCore::Update(float _Delta)
{

}