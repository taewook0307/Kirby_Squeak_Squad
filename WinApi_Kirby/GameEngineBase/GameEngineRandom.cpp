#include "GameEngineRandom.h"
#include <iostream>

GameEngineRandom GameEngineRandom::MainRandom;

GameEngineRandom::GameEngineRandom() 
{
	Seed = (int)time(nullptr);
	srand(Seed);
}

GameEngineRandom::GameEngineRandom(int _Seed)
{
	Seed = _Seed;
	srand(Seed);
}

int GameEngineRandom::RandomInt(int _Min, int _Max)
{
	return (rand() % (_Max + 1 - _Min)) + _Min;
}

GameEngineRandom::~GameEngineRandom() 
{
}

