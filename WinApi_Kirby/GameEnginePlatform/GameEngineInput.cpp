#include "GameEngineInput.h"

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{
		PressTime += _DeltaTime;

		if (true == Free)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else if (true == Down)
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}
	}
	else
	{
		PressTime = 0.0f;

		if (true == Press)
		{
			Down = false;
			Press = false;
			Up = true;
			Free = true;
		}
		else if (true == Up)
		{
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}
}