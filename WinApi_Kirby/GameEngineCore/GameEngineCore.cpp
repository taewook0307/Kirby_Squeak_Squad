#include "GameEngineCore.h"
#include "GameEngineLevel.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>

std::string GameEngineCore::WindowTitle = "";
std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevel;
CoreProcess* GameEngineCore::Process = nullptr;
GameEngineLevel* GameEngineCore::CurLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
	GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);

	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (nullptr != NextLevel)
	{
		CurLevel = NextLevel;
		NextLevel = nullptr;
		GameEngineTime::MainTimer.Reset();
	}

	GameEngineTime::MainTimer.Update();
	float Delta = GameEngineTime::MainTimer.GetDeltaTime();
	// 한 프레임이 도는 동안에는 기본적인 세팅의 변화가 없게하기 위한 설계의도
	// 한 프레임 동안 CurLevel의 값을 바꾸지 않도록 하기 위한 구조
	CurLevel->Update(Delta);
	CurLevel->ActorUpdate(Delta);
	GameEngineWindow::MainWindow.ClearBackBuffer();
	CurLevel->ActorRender();
	CurLevel->Render();
	GameEngineWindow::MainWindow.DoubleBuffering();
}

void GameEngineCore::CoreEnd()
{
	Process->Release();

	if (nullptr != Process)
	{
		delete Process;
		Process = nullptr;
	}

	for (std::pair<std::string, GameEngineLevel*> _Pair : AllLevel)
	{
		if (nullptr != _Pair.second)
		{
			delete _Pair.second;
			_Pair.second = nullptr;
		}
	}
}


void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr)
{
	GameEngineDebug::LeckCheck();

	Process = _Ptr;
	WindowTitle = _Title;
	GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}

void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}