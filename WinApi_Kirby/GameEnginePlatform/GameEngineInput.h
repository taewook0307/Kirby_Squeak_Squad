#pragma once
#include <Windows.h>
#include <map>
#include <string>

class GameEngineInput
{
private:
	class GameEngineKey
	{
		bool Down = false;
		bool Press = false;
		bool Up = false;
		bool Free = true;

		float PressTime = 0.0f;

		int Key = -1;

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Update(float _DeltaTime);
	};

public:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

protected:

private:
	static std::map<std::string, GameEngineKey> AllKeys;
};