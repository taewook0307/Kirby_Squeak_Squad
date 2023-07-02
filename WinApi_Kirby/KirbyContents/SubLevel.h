#pragma once

#include "ActorEnum.h"

#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>

class Ground;
class Kirby;
class GameEngineRenderer;
class KirbyUI;
class SubLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SubLevel();
	~SubLevel();

	// delete Function
	SubLevel(const SubLevel& _Other) = delete;
	SubLevel(SubLevel&& _Other) noexcept = delete;
	SubLevel& operator=(const SubLevel& _Other) = delete;
	SubLevel& operator=(SubLevel&& _Other) noexcept = delete;

	static int GetPlayerLife();

	static MonsterType& GetLevelPlayerForm();

	static void PlusPlayerLife();

	static GameEngineSoundPlayer& GetBGM()
	{
		return BGM;
	}

protected:
	static void SetLevelPlayerForm(const MonsterType& _Value);

	static int PlayerLifeCount;

	static void MinusPlayerLife();

	void LevelStart(GameEngineLevel* _PrevLevel) override;

	void FormChange(const std::string& _BitMapFileName);

	Kirby* LevelPlayer = nullptr;
	float4 SavePos = float4::ZERO;
	Ground* Stage = nullptr;
	static GameEngineSoundPlayer BGM;

	virtual void AllMonsterDeath();
private:
	static MonsterType LevelPlayerForm;

	static KirbyUI* LevelPlayerUI;
};