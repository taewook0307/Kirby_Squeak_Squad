#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <Windows.h>
#include <string>
#include <map>
#include "GameEngineObject.h"

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

		// 이미 내부에 TitleLevel이 존재한다.
		if (AllLevel.end() != AllLevel.find(Upper))
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 이미 존재합니다.");
			return;
		}

		GameEngineLevel* NewLevel = new LevelType();

		LevelInit(NewLevel);

		AllLevel.insert(std::make_pair(Upper, NewLevel));

		//std::pair<std::map<std::string, class GameEngineLevel*>::iterator, bool> Pair 
		//	= AllLevel.insert(std::make_pair(_Title, nullptr));

		//if (false == Pair.second)
		//{
		//	MsgBoxAssert("이미 존재하는 이름의 레벨을 또 만들려고 했습니다" + _Title);
		//	return;
		//}
	}

	static void ChangeLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		std::map<std::string, GameEngineLevel*>::iterator Finditer = AllLevel.find(Upper);

		// 이미 내부에 TitleLevel이 존재한다.
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
