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
	if (nullptr == GameEngineSound::FindSound("BossRun.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("BossRun.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("BossShout.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("BossShout.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("BossWalk.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("BossWalk.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Damage.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Damage.wav"));
	}
}