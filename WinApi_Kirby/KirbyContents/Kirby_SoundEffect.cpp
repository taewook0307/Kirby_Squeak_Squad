#include "Kirby.h"

void Kirby::SoundEffectLoad()
{
	GameEnginePath SoundPath;
	SoundPath.SetCurrentPath();
	SoundPath.MoveParentToExistsChild("Resources");
	SoundPath.MoveChild("Resources\\SoundEffects\\");

	if (nullptr == GameEngineSound::FindSound("Attack.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Attack.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Breathe.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Breathe.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("BreatheOut.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("BreatheOut.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Change.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Change.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Damage.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Damage.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Drop.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Drop.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Fly.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Fly.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Inhale.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Inhale.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Jump.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Jump.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Keep.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Keep.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Move.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Move.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Run.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Run.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Slide.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Slide.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("Stop.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("Stop.wav"));
	}
	if (nullptr == GameEngineSound::FindSound("NormalChange.wav"))
	{
		GameEngineSound::SoundLoad(SoundPath.PlusFilePath("NormalChange.wav"));
	}
}