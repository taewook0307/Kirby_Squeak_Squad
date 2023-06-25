#include "TornadoMonster.h"

#include <GameEnginePlatform/GameEngineSound.h>

void TornadoMonster::SoundEffectLoad()
{
	GameEnginePath SoundPath;
	SoundPath.SetCurrentPath();
	SoundPath.MoveParentToExistsChild("Resources");
	SoundPath.MoveChild("Resources\\SoundEffects\\");

	if (nullptr == GameEngineSound::FindSound("Damage.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Damage.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("MonsterDeath.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("MonsterDeath.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Tornado.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Tornado.wav"));
	}
}