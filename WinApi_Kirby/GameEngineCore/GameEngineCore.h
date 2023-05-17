#pragma once
#include "GameEngineObject.h"

#include <Windows.h>
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

class CoreProcess : public GameEngineObject
{

};

// 설명 :
class GameEngineLevel;
class GameEngineCore
{
public:
	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	template<typename CoreProcessType>
	static void EngineStart(const std::string& _Title, HINSTANCE _Inst)
	{
		EngineStart(_Title, _Inst, new CoreProcessType());
	}

	template<typename LevelType>
	static void CreateLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		if (AllLevel.end() != AllLevel.find(Upper))
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 이미 존재합니다.");
			return;
		}

		GameEngineLevel* NewLevel = new LevelType();

		LevelInit(NewLevel);

		AllLevel.insert(std::make_pair(Upper, NewLevel));
	}

	static void ChangeLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		std::map<std::string, GameEngineLevel*>::iterator Finditer = AllLevel.find(Upper);

		if (AllLevel.end() == Finditer)
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 존재하지 않습니다.");
			return;
		}

		NextLevel = Finditer->second;
	}

protected:

private:
	static std::string WindowTitle;
	static CoreProcess* Process;

	static void LevelInit(GameEngineLevel* _Level);

	static void CoreStart(HINSTANCE _Inst);
	static void CoreUpdate();
	static void CoreEnd();
	static void EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr);

	static GameEngineLevel* CurLevel;
	static GameEngineLevel* NextLevel;
	static std::map<std::string, GameEngineLevel*> AllLevel;

	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();
};