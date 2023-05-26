#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>

// lib를 가져다 사용하겠다는 전처리문입니다.
// lib는 구현이다.
#ifdef _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

// FMOD를 사용하기 위한 핸들 및 객체
FMOD::System* SoundSystem = nullptr;

class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		// 이런 외부 함수는 내부에서 new를 하고 있습니다.
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("사운드 시스템 이니셜라이즈에 실패했습니다.");
		}
	}

	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();


GameEngineSound::GameEngineSound() 
{
}

GameEngineSound::~GameEngineSound() 
{
}


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

void GameEngineSound::SoundLoad(const std::string& _Name, const  std::string& _Path)
{

}

void GameEngineSound::SoundPlay(const std::string& _Name)
{

}

// 1번의 재생을 하고 조금 특별 관리 된다.
void GameEngineSound::PlayBgm(const std::string& _Name)
{

}

// 특별 관리되는 사운드 재생을 멈춘다.
void GameEngineSound::StopBgm() 
{

}