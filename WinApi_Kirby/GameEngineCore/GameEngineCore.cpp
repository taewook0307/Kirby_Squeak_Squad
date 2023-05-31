#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

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
	// 엔진쪽에 준비를 다 해고
	GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);
	GameEngineInput::InputInit();
	// GameEngineSound::Init();

	// 유저의 준비를 해준다.
	Process->Start();
}

void GameEngineCore::CoreUpdate() 
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelEnd(NextLevel);
			CurLevel->ActorLevelEnd();
		}

		NextLevel->OverCheck(CurLevel);

		NextLevel->LevelStart(CurLevel);
		NextLevel->ActorLevelStart();

		CurLevel = NextLevel;

		NextLevel = nullptr;
		GameEngineTime::MainTimer.Reset();
	}

	// 업데이트를 
	GameEngineSound::Update();
	GameEngineTime::MainTimer.Update();
	float Delta = GameEngineTime::MainTimer.GetDeltaTime();

	if (true == GameEngineWindow::IsFocus())
	{
		GameEngineInput::Update(Delta);
	}
	else 
	{
		GameEngineInput::Reset();
	}

	// 한프레임 동안은 절대로 기본적인 세팅의 
	// 변화가 없게 하려고 하는 설계의도가 있는것.
	// 이걸 호출한 애는 PlayLevel
	CurLevel->AddLiveTime(Delta);
	CurLevel->Update(Delta);

	// TitleLevel
	CurLevel->ActorUpdate(Delta);
	GameEngineWindow::MainWindow.ClearBackBuffer();
	CurLevel->ActorRender(Delta);
	CurLevel->Render(Delta);
	GameEngineWindow::MainWindow.DoubleBuffering();

	// 프레임의 가장 마지막에 Release가 될겁니다.
	CurLevel->ActorRelease();

}

void GameEngineCore::CoreEnd() 
{
	GameEngineSound::Release();

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