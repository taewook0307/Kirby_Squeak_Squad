#include "EndingLevel.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Start()
{
	
}

void EndingLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN) || true == GameEngineInput::IsDown(VK_SPACE))
	{
		GameEngineWindow::MainWindow.WindowLoopOff();
	}
}