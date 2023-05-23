#pragma once

// Ό³Έν :
class GameEngineRandom
{
public:
	static GameEngineRandom MainRandom;

	// constrcuter destructer
	GameEngineRandom();
	GameEngineRandom(int _Seed);
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max);

protected:

private:
	int Seed = 0;
};

