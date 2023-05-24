#include "GameEngineSound.h"

GameEngineSound::GameEngineSound()
{
}

GameEngineSound::~GameEngineSound()
{
}


class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
	}

	~SoundSystemCreator()
	{
	}
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();

//
//void GameEngineSound::Init()
//{
//	static bool IsOnce = false;
//
//	if (true == IsOnce)
//	{
//		return;
//	}
//
//
//
//
//	// Fmod를 사용하기 위한 준비를 하는 함수
//	IsOnce = true;
//}

void GameEngineSound::SoundLoad(std::string& _Name, std::string& _Path)
{

}

void GameEngineSound::SoundPlay(std::string& _Name)
{

}

// 1번의 재생을 하고 조금 특별 관리 된다.
void GameEngineSound::PlayBgm(std::string& _Name)
{

}

// 특별 관리되는 사운드 재생을 멈춘다.
void GameEngineSound::StopBgm()
{

}