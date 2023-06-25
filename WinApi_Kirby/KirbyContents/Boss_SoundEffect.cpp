#include "BossMonster.h"

#include <GameEnginePlatform/GameEngineSound.h>

void BossMonster::SoundEffectLoad()
{
	GameEnginePath SoundPath;
	SoundPath.SetCurrentPath();
	SoundPath.MoveParentToExistsChild("Resources");
	SoundPath.MoveChild("Resources\\SoundEffects\\");

	if (nullptr == GameEngineSound::FindSound("BossAttack.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("BossAttack.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("BossShout.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("BossShout.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("BossWalk.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("BossWalk.wav"));
	}
}