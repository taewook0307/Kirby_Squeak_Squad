#include "EndingLevel.h"
#include "BackGround.h"
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
	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->BackGroundInit("EndingLevel.bmp");
}

void EndingLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN) || true == GameEngineInput::IsDown(VK_SPACE))
	{
		GameEngineWindow::MainWindow.WindowLoopOff();
	}
}