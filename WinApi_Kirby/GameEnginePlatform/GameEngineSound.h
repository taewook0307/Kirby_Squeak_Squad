#pragma once
#include <string>

// 설명 :
class GameEngineSound
{
	// Management
public:
	// static void Init();

	static void SoundLoad(std::string& _Name, std::string& _Path);

	// 1번의 재생을 하고 끝나면 그냥 종료하고 나는 컨트롤할수 없다.
	static void SoundPlay(std::string& _Name);

	// 1번의 재생을 하고 조금 특별 관리 된다.
	static void PlayBgm(std::string& _Name);

	// 특별 관리되는 사운드 재생을 멈춘다.
	static void StopBgm();


public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:

	// GameEngineSound::SoundLoad("C:\\AAAA\\AAAA\\A\\AAA.Mp3");
	// GameEngineSound::SoundPlay("AAA.Mp3");
	// GameEngineSound::PlayBgm("AAA.Mp3");
	// GameEngineSound::StopBgm("AAA.Mp3");
private:

};

