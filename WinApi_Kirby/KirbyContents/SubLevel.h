#pragma once

#include "ActorEnum.h"
#include "KirbyGameEnum.h"

#include <list>

#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>

class Ground;
class Kirby;
class Monster;
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

	template<typename MonsterType>
	void CreateMonster(const float4& _Pos, const std::string& _BitMapName)
	{
		MonsterType* MonsterPtr = CreateActor<MonsterType>(UpdateOrder::Monster);
		

		if (MonsterPtr != nullptr)
		{
			MonsterPtr->SetPos(_Pos);
			MonsterPtr->SetGroundBitMap(_BitMapName);

			AllMonster.push_back(MonsterPtr);
		}
		else
		{
			MsgBoxAssert("몬스터 생성에 실패했습니다.");
		}
	}

	void AllMonsterDeath();

	std::list<Monster*> AllMonster;
private:
	static MonsterType LevelPlayerForm;

	static KirbyUI* LevelPlayerUI;
};