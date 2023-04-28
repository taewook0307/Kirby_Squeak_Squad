#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <Windows.h>
#include <string>
#include <map>

// 설명 :
class GameEngineLevel;
class GameEngineCore
{
public:
	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	static void EngineStart(const std::string& _Title, HINSTANCE _Inst);

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

		AllLevel.insert(std::make_pair(Upper, NewLevel));

		/*
		std::pair<std::map<std::string, class GameEngineLevel*>::iterator, bool> Pair 
			= AllLevel.insert(std::make_pair(_Title, nullptr));

		if (false == Pair.second)
		{
			MsgBoxAssert("이미 존재하는 이름의 레벨을 또 만들려고 했습니다" + _Title);
			return;
		}
		*/
	}


protected:

private:
	static std::string WindowTitle;

	static void CoreStart(HINSTANCE _Inst);
	static void CoreUpdate();
	static void CoreEnd();

	static std::map<std::string, GameEngineLevel*> AllLevel;
};
