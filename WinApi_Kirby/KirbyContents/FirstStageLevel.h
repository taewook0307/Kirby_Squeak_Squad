
#include "SubLevel.h"

#include <list>

class Monster;
class LifeCountPlusItem;
class HealItem;
class GameEngineRenderer;
class FirstStageLevel : public SubLevel
{
public:
	// constrcuter destructer
	FirstStageLevel();
	~FirstStageLevel();

	// delete Function
	FirstStageLevel(const FirstStageLevel& _Other) = delete;
	FirstStageLevel(FirstStageLevel&& _Other) noexcept = delete;
	FirstStageLevel& operator=(const FirstStageLevel& _Other) = delete;
	FirstStageLevel& operator=(FirstStageLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void AllMonsterDeath() override;

	class BackGround* Back = nullptr;

	Monster* LevelMonster1 = nullptr;
	Monster* LevelMonster2 = nullptr;
	Monster* LevelMonster3 = nullptr;

	LifeCountPlusItem* LevelLifeItem = nullptr;
};